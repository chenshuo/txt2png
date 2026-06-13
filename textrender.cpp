// textrender — render a plain-text file to PNG using
//   HarfBuzz (shaping) + Knuth-Plass (line-breaking) + Cairo (rasterisation).
//
// Build:  see tex/Makefile
// Usage:  ./textrender [OPTIONS] INPUT.txt OUTPUT.png
//
// Options:
//   --font PATH   TTF/OTF font  (default: DejaVuSerif.ttf)
//   --size N      font size in points  (default: 12)
//   --width N     page width in pixels  (default: 800)
//   --height N    page height in pixels (default: 1000)
//   --margin N    margin in pixels on all sides (default: 72)
//   --leading N   line-height multiplier (default: 1.4)
//   --tolerance N Knuth-Plass tolerance (default: 200)

#include "linebreak.h"

#include <cairo/cairo-ft.h>
#include <cairo/cairo.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <harfbuzz/hb-ft.h>
#include <harfbuzz/hb.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static double hb_advance_px(hb_font_t* font, const std::string& word) {
    hb_buffer_t* buf = hb_buffer_create();
    hb_buffer_add_utf8(buf, word.c_str(), -1, 0, -1);
    hb_buffer_guess_segment_properties(buf);
    hb_shape(font, buf, nullptr, 0);

    unsigned int      n    = 0;
    hb_glyph_position_t* pos = hb_buffer_get_glyph_positions(buf, &n);
    double advance = 0.0;
    for (unsigned int i = 0; i < n; ++i)
        advance += pos[i].x_advance / 64.0;

    hb_buffer_destroy(buf);
    return advance;
}

// Shape a word and produce Cairo glyphs starting at (pen_x, pen_y).
// Appends to `out`.
static void shape_to_glyphs(
    hb_font_t*                    font,
    const std::string&            word,
    double                        pen_x,
    double                        pen_y,
    std::vector<cairo_glyph_t>&   out)
{
    hb_buffer_t* buf = hb_buffer_create();
    hb_buffer_add_utf8(buf, word.c_str(), -1, 0, -1);
    hb_buffer_guess_segment_properties(buf);
    hb_shape(font, buf, nullptr, 0);

    unsigned int          ng  = 0;
    unsigned int          np  = 0;
    hb_glyph_info_t*     info = hb_buffer_get_glyph_infos(buf, &ng);
    hb_glyph_position_t* gpos = hb_buffer_get_glyph_positions(buf, &np);

    double x = pen_x, y = pen_y;
    for (unsigned int i = 0; i < ng; ++i) {
        cairo_glyph_t cg;
        cg.index = info[i].codepoint;
        cg.x     = x + gpos[i].x_offset / 64.0;
        cg.y     = y - gpos[i].y_offset / 64.0;
        out.push_back(cg);
        x += gpos[i].x_advance / 64.0;
        y -= gpos[i].y_advance / 64.0;
    }

    hb_buffer_destroy(buf);
}

// Split text on blank lines into paragraphs.
static std::vector<std::string> split_paragraphs(const std::string& text) {
    std::vector<std::string> paras;
    std::istringstream       ss(text);
    std::string              line, cur;

    while (std::getline(ss, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r") == std::string::npos) {
            if (!cur.empty()) { paras.push_back(cur); cur.clear(); }
        } else {
            if (!cur.empty()) cur += ' ';
            cur += line;
        }
    }
    if (!cur.empty()) paras.push_back(cur);
    return paras;
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    // Defaults
    std::string font_path =
        "/usr/share/fonts/opentype/noto/NotoSerifCJK-Regular.ttc";
    double pt_size   = 12.0;
    int    page_w    = 800;
    int    page_h    = 1000;
    int    margin    = 72;
    double leading   = 1.4;
    double tolerance = 200.0;
    std::string input_path, output_path;

    // Parse arguments
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        auto need = [&](const char* name) -> std::string {
            if (i + 1 >= argc) throw std::runtime_error(
                std::string("missing value for ") + name);
            return argv[++i];
        };
        if      (a == "--font")      font_path = need("--font");
        else if (a == "--size")      pt_size   = std::stod(need("--size"));
        else if (a == "--width")     page_w    = std::stoi(need("--width"));
        else if (a == "--height")    page_h    = std::stoi(need("--height"));
        else if (a == "--margin")    margin    = std::stoi(need("--margin"));
        else if (a == "--leading")   leading   = std::stod(need("--leading"));
        else if (a == "--tolerance") tolerance = std::stod(need("--tolerance"));
        else if (input_path.empty()) input_path  = a;
        else if (output_path.empty()) output_path = a;
        else { std::cerr << "Unknown argument: " << a << '\n'; return 1; }
    }

    if (input_path.empty() || output_path.empty()) {
        std::cerr <<
            "Usage: textrender [OPTIONS] INPUT.txt OUTPUT.png\n"
            "Options:\n"
            "  --font PATH      font file (default: DejaVuSerif.ttf)\n"
            "  --size N         font size in points (default: 12)\n"
            "  --width N        page width in pixels (default: 800)\n"
            "  --height N       page height in pixels (default: 1000)\n"
            "  --margin N       margin in pixels (default: 72)\n"
            "  --leading N      line-height multiplier (default: 1.4)\n"
            "  --tolerance N    Knuth-Plass tolerance (default: 200)\n";
        return 1;
    }

    // Read input
    std::ifstream ifs(input_path);
    if (!ifs) { std::cerr << "Cannot open: " << input_path << '\n'; return 1; }
    std::string text((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());

    // FreeType
    FT_Library ft_lib;
    if (FT_Init_FreeType(&ft_lib))
        throw std::runtime_error("FT_Init_FreeType failed");

    FT_Face ft_face;
    if (FT_New_Face(ft_lib, font_path.c_str(), 0, &ft_face))
        throw std::runtime_error("FT_New_Face failed: " + font_path);

    // 72 dpi — 1 point = 1 pixel at this dpi setting
    if (FT_Set_Char_Size(ft_face, 0, static_cast<FT_F26Dot6>(pt_size * 64), 72, 72))
        throw std::runtime_error("FT_Set_Char_Size failed");

    // HarfBuzz font (borrows ft_face, reference-counted)
    hb_font_t* hb_font = hb_ft_font_create(ft_face, nullptr);

    // Measure space
    const double space_w  = hb_advance_px(hb_font, " ");
    const double space_s  = space_w * 0.5;
    const double space_k  = space_w * 0.333;

    const double text_w   = page_w - 2.0 * margin;
    const double line_h   = pt_size * leading;

    // Knuth-Plass params
    Params kp_params;
    kp_params.tolerance = tolerance;

    // Cairo surface
    cairo_surface_t* surface =
        cairo_image_surface_create(CAIRO_FORMAT_RGB24, page_w, page_h);
    cairo_t* cr = cairo_create(surface);

    // White background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Cairo font face from FreeType face
    cairo_font_face_t* cf =
        cairo_ft_font_face_create_for_ft_face(ft_face, FT_LOAD_DEFAULT);
    cairo_set_font_face(cr, cf);
    cairo_set_font_size(cr, pt_size);
    cairo_set_source_rgb(cr, 0, 0, 0);

    // Baseline y starts at top margin + ascender
    double baseline_y = margin + pt_size;  // rough first baseline

    auto paras = split_paragraphs(text);

    for (size_t pi = 0; pi < paras.size(); ++pi) {
        const std::string& para = paras[pi];

        // Build items: Box per word (HarfBuzz advance), Glue per space
        std::vector<Item> items;
        std::istringstream ss(para);
        std::string word;
        bool first = true;

        while (ss >> word) {
            if (!first)
                items.push_back(Glue{space_w, space_s, space_k});
            double w = hb_advance_px(hb_font, word);
            items.push_back(Box{w, word});
            first = false;
        }
        if (items.empty()) continue;

        // parfillskip + forced-break sentinel
        items.push_back(Glue{0.0, INF_PENALTY, 0.0});
        items.push_back(Penalty{-INF_PENALTY, false});

        LineSpec spec = LineSpec::uniform(text_w);
        std::vector<int> breaks;
        try {
            breaks = break_paragraph(items, spec, kp_params);
        } catch (const std::exception& e) {
            std::cerr << "Warning: " << e.what() << " — using greedy fallback\n";
            // Greedy fallback: just collect all break-eligible positions
            double acc = 0.0;
            for (int idx = 0; idx < static_cast<int>(items.size()); ++idx) {
                if (auto* b = std::get_if<Box>(&items[idx]))      acc += b->width;
                else if (auto* g = std::get_if<Glue>(&items[idx])) {
                    if (acc + g->width > text_w && idx > 0) {
                        breaks.push_back(idx);
                        acc = 0.0;
                    }
                    acc += g->width;
                }
            }
            breaks.push_back(static_cast<int>(items.size()) - 1);
        }

        // Lay out lines from break indices
        std::vector<int> starts{-1};
        for (int b : breaks) starts.push_back(b);
        std::vector<int> ends(breaks);
        ends.push_back(static_cast<int>(items.size()));

        for (size_t li = 0; li < starts.size(); ++li) {
            int seg_start = starts[li] + 1;
            int seg_end   = ends[li];

            // Skip leading glue
            while (seg_start < seg_end &&
                   std::holds_alternative<Glue>(items[seg_start]))
                ++seg_start;

            if (seg_start >= seg_end) continue;
            if (baseline_y > page_h - margin) break;  // out of page

            // Measure natural width + stretch + shrink for this line
            double nat = 0.0, stretch = 0.0, shrink = 0.0;
            for (int idx = seg_start; idx < seg_end; ++idx) {
                const Item& it = items[idx];
                if (auto* b = std::get_if<Box>(&it))       nat += b->width;
                else if (auto* g = std::get_if<Glue>(&it)) {
                    nat += g->width; stretch += g->stretch; shrink += g->shrink;
                }
            }

            // Compute adjustment ratio
            double ratio = 0.0;
            double sfall = text_w - nat;
            if (sfall > 0.0 && stretch > 0.0)        ratio =  sfall / stretch;
            else if (sfall < 0.0 && shrink  > 0.0)   ratio =  sfall / shrink;

            // Emit glyphs
            double pen_x = margin;
            std::vector<cairo_glyph_t> glyphs;

            for (int idx = seg_start; idx < seg_end; ++idx) {
                const Item& it = items[idx];
                if (auto* b = std::get_if<Box>(&it)) {
                    shape_to_glyphs(hb_font, b->text, pen_x, baseline_y, glyphs);
                    pen_x += b->width;
                } else if (auto* g = std::get_if<Glue>(&it)) {
                    double w = (ratio >= 0.0)
                        ? g->width + ratio * g->stretch
                        : g->width + ratio * g->shrink;
                    pen_x += w;
                }
                // Penalty glyphs (hyphen) omitted for now
            }

            if (!glyphs.empty())
                cairo_show_glyphs(cr, glyphs.data(),
                                  static_cast<int>(glyphs.size()));

            baseline_y += line_h;
        }

        // Extra gap between paragraphs
        baseline_y += line_h * 0.5;
    }

    cairo_font_face_destroy(cf);
    cairo_destroy(cr);

    if (cairo_surface_write_to_png(surface, output_path.c_str()) != CAIRO_STATUS_SUCCESS) {
        std::cerr << "Failed to write PNG: " << output_path << '\n';
        cairo_surface_destroy(surface);
        return 1;
    }
    cairo_surface_destroy(surface);

    hb_font_destroy(hb_font);
    FT_Done_Face(ft_face);
    FT_Done_FreeType(ft_lib);

    std::cout << "Wrote " << output_path
              << "  (" << page_w << 'x' << page_h << ")\n";
    return 0;
}
