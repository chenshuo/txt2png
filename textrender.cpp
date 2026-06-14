// textrender — render a plain-text file to PNG using
//   HarfBuzz (shaping) + Knuth-Plass (line-breaking) + Cairo (rasterisation).
//   Unicode Line Breaking Algorithm (ICU UAX #14) determines break opportunities,
//   enabling correct handling of CJK text (no spaces between characters).
//
// Build:  see tex/Makefile
// Usage:  ./textrender [OPTIONS] INPUT.txt OUTPUT.png
//
// Options:
//   --font PATH        TTF/OTF font  (default: NotoSerifCJK-Regular.ttc)
//   --size N           font size in points  (default: 12)
//   --width N          page width in pixels  (default: 800)
//   --height N         page height in pixels (default: 1000)
//   --margin N         margin in pixels on all sides (default: 72)
//   --leading N        line-height multiplier (default: 1.4)
//   --tolerance N      Knuth-Plass tolerance (default: 200)
//   --nohyphen         disable English hyphenation (enabled by default if dict found)
//   --hyphen-dict PATH use a custom hyphenation dictionary file

#include "linebreak.h"

#include <cairo/cairo-ft.h>
#include <cairo/cairo.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <harfbuzz/hb-ft.h>
#include <harfbuzz/hb.h>
#include <unicode/brkiter.h>
#include <unicode/unistr.h>
#include <hyphen.h>

#include <algorithm>
#include <cctype>
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

// ---------------------------------------------------------------------------
// CSS text-autospace helpers
// ---------------------------------------------------------------------------

// Returns true if cp is in a CJK ideographic block (simplified ranges).
static bool is_cjk(char32_t cp) {
    return (cp >= 0x3000  && cp <= 0x9FFF)   // CJK punctuation, kana, CJK unified
        || (cp >= 0xF900  && cp <= 0xFAFF)   // CJK compatibility ideographs
        || (cp >= 0x20000 && cp <= 0x2FA1F); // CJK extension B–F, compat supplement
}

// Returns true if cp is an ASCII letter or digit (Latin/digit script).
static bool is_latin_or_digit(char32_t cp) {
    return (cp >= 'A' && cp <= 'Z')
        || (cp >= 'a' && cp <= 'z')
        || (cp >= '0' && cp <= '9')
        || (cp >= 0x00C0 && cp <= 0x024F);  // extended Latin
}

// Decode first Unicode codepoint from a UTF-8 string. Returns 0 on error.
static char32_t first_codepoint(const std::string& s) {
    if (s.empty()) return 0;
    unsigned char c = static_cast<unsigned char>(s[0]);
    if (c < 0x80) return c;
    if (c < 0xE0 && s.size() >= 2)
        return ((c & 0x1F) << 6) | (static_cast<unsigned char>(s[1]) & 0x3F);
    if (c < 0xF0 && s.size() >= 3)
        return ((c & 0x0F) << 12)
             | ((static_cast<unsigned char>(s[1]) & 0x3F) << 6)
             |  (static_cast<unsigned char>(s[2]) & 0x3F);
    if (s.size() >= 4)
        return ((c & 0x07) << 18)
             | ((static_cast<unsigned char>(s[1]) & 0x3F) << 12)
             | ((static_cast<unsigned char>(s[2]) & 0x3F) << 6)
             |  (static_cast<unsigned char>(s[3]) & 0x3F);
    return 0;
}

// Returns 0-based byte indices after which a hyphen may be inserted.
// Requires word to be pure ASCII letters (libhyphen operates on lowercase).
static std::vector<int> hyphen_breaks(HyphenDict* dict, const std::string& word) {
    if (!dict || word.size() < 4) return {};
    std::string lower = word;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    int n = static_cast<int>(lower.size());
    std::vector<char> hbuf(static_cast<size_t>(n) + 5, 0);
    char** rep = nullptr; int* pos = nullptr; int* cut = nullptr;
    int rc = hnj_hyphen_hyphenate2(dict, lower.c_str(), n,
                                   hbuf.data(), nullptr, &rep, &pos, &cut);
    if (rep) { for (int i = 0; i < n; ++i) if (rep[i]) free(rep[i]); free(rep); }
    if (pos) free(pos);
    if (cut) free(cut);
    if (rc != 0) return {};
    std::vector<int> breaks;
    for (int i = 1; i < n - 2; ++i)   // min 2 chars on each side
        if (hbuf[i] & 1) breaks.push_back(i);
    return breaks;
}

// Build Knuth-Plass items from a paragraph using ICU UAX #14 line break iterator.
//
// Each ICU break segment becomes a Box (measured via HarfBuzz).
// Segments with trailing ASCII space get a Glue after them (inter-word).
// Segments without trailing space (CJK and last word) get a micro-Glue after
// them so the line can still be stretched for justification; mandatory breaks
// (hard line-break class) emit a forced Penalty instead.
static std::vector<Item> build_para_items(
    hb_font_t*         hb_font,
    const std::string& para,
    double             space_w,
    double             space_s,
    double             space_k,
    double             pt_size,
    HyphenDict*        hyph_dict = nullptr)
{
    icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(para);

    UErrorCode status = U_ZERO_ERROR;
    std::unique_ptr<icu::BreakIterator> bi(
        icu::BreakIterator::createLineInstance(icu::Locale::getDefault(), status));
    if (U_FAILURE(status))
        throw std::runtime_error("ICU BreakIterator creation failed");
    bi->setText(ustr);

    // Inter-CJK micro-glue: zero natural width, some stretch so Knuth-Plass
    // can distribute whitespace across CJK characters for full justification.
    const double cjk_stretch = space_w * 0.5;

    // CSS text-autospace: 0.25em gap at CJK<->Latin/digit boundaries.
    const double autospace   = pt_size * 0.25;
    const double autospace_s = pt_size * 0.05;   // small stretch for autospace

    // Script tracker for autospace detection (unknown / CJK / Latin-digit).
    enum Script { UNKNOWN, CJK, LATIN_DIGIT };
    Script last_script = UNKNOWN;

    std::vector<Item> items;
    int32_t prev = 0;

    bi->first();
    for (int32_t pos = bi->next();
         pos != icu::BreakIterator::DONE;
         pos = bi->next())
    {
        // Split segment into word (non-space) + trailing space
        int32_t trail = pos;
        while (trail > prev && ustr.charAt(trail - 1) == 0x0020) --trail;
        bool has_space = (trail < pos);

        // Decode word part to UTF-8
        std::string word_utf8;
        ustr.tempSubStringBetween(prev, trail).toUTF8String(word_utf8);

        if (!word_utf8.empty()) {
            // Detect script of this segment's first codepoint.
            char32_t cp = first_codepoint(word_utf8);
            Script cur_script = is_cjk(cp) ? CJK
                              : is_latin_or_digit(cp) ? LATIN_DIGIT
                              : UNKNOWN;

            // Insert autospace at script boundary by widening the preceding Glue.
            if (last_script != UNKNOWN && cur_script != UNKNOWN
                    && last_script != cur_script
                    && !items.empty()) {
                // Find the last Glue in items and add autospace to it.
                for (int k = static_cast<int>(items.size()) - 1; k >= 0; --k) {
                    if (auto* g = std::get_if<Glue>(&items[k])) {
                        g->width   += autospace;
                        g->stretch += autospace_s;
                        break;
                    }
                    // Stop if we hit a Box (no Glue between last Box and this one)
                    if (std::holds_alternative<Box>(items[k])) {
                        // Insert a new autospace Glue before this Box was emitted —
                        // that case shouldn't happen with ICU segmentation, but
                        // guard it by inserting one after the last item anyway.
                        items.push_back(Glue{autospace, autospace_s, 0.0});
                        break;
                    }
                }
            }

            if (cur_script != UNKNOWN) last_script = cur_script;

            if (has_space && hyph_dict) {
                // Latin word: try to hyphenate
                auto hbreaks = hyphen_breaks(hyph_dict, word_utf8);
                if (!hbreaks.empty()) {
                    int prev_pos = 0;
                    for (int bp : hbreaks) {
                        std::string syl = word_utf8.substr(
                            static_cast<size_t>(prev_pos),
                            static_cast<size_t>(bp + 1 - prev_pos));
                        items.push_back(Box{hb_advance_px(hb_font, syl), syl});
                        items.push_back(Penalty{50.0, true});  // flagged = hyphen point
                        prev_pos = bp + 1;
                    }
                    std::string last = word_utf8.substr(static_cast<size_t>(prev_pos));
                    items.push_back(Box{hb_advance_px(hb_font, last), last});
                } else {
                    items.push_back(Box{hb_advance_px(hb_font, word_utf8), word_utf8});
                }
                items.push_back(Glue{space_w, space_s, space_k});
            } else if (has_space) {
                // Latin inter-word space (no hyphenation)
                items.push_back(Box{hb_advance_px(hb_font, word_utf8), word_utf8});
                items.push_back(Glue{space_w, space_s, space_k});
            } else {
                // No trailing space: CJK inter-char or end of paragraph
                double w = hb_advance_px(hb_font, word_utf8);
                items.push_back(Box{w, word_utf8});
                int rule = bi->getRuleStatus();
                if (rule >= UBRK_LINE_HARD) {
                    items.push_back(Penalty{-INF_PENALTY, false});
                } else {
                    // Optional break: micro-glue so Knuth-Plass can justify CJK
                    items.push_back(Glue{0.0, cjk_stretch, 0.0});
                }
            }
        }

        prev = pos;
    }

    // Remove trailing Glue left by last segment (will be replaced by parfillskip)
    while (!items.empty() && std::holds_alternative<Glue>(items.back()))
        items.pop_back();

    items.push_back(Glue{0.0, INF_PENALTY, 0.0});   // parfillskip
    items.push_back(Penalty{-INF_PENALTY, false});   // forced end
    return items;
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
    bool        hyphen_off       = false;
    std::string hyphen_dict_path;
    bool        tracing_paras   = false;
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
        else if (a == "--tolerance")  tolerance = std::stod(need("--tolerance"));
        else if (a == "--nohyphen")          hyphen_off = true;
        else if (a == "--hyphen-dict")       hyphen_dict_path = need("--hyphen-dict");
        else if (a == "--tracingparagraphs") tracing_paras = true;
        else if (input_path.empty()) input_path  = a;
        else if (output_path.empty()) output_path = a;
        else { std::cerr << "Unknown argument: " << a << '\n'; return 1; }
    }

    if (input_path.empty() || output_path.empty()) {
        std::cerr <<
            "Usage: textrender [OPTIONS] INPUT.txt OUTPUT.png\n"
            "Options:\n"
            "  --font PATH        font file (default: NotoSerifCJK-Regular.ttc)\n"
            "  --size N           font size in points (default: 12)\n"
            "  --width N          page width in pixels (default: 800)\n"
            "  --height N         page height in pixels (default: 1000)\n"
            "  --margin N         margin in pixels (default: 72)\n"
            "  --leading N        line-height multiplier (default: 1.4)\n"
            "  --tolerance N      Knuth-Plass tolerance (default: 200)\n"
            "  --nohyphen            disable English hyphenation (on by default if dict found)\n"
            "  --hyphen-dict PATH    use a custom hyphenation dictionary\n"
            "  --tracingparagraphs   print Knuth-Plass diagnostics to stderr\n";
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

    // Inter-word spacing.  Use em-based stretch/shrink (TeX §1086 style) rather
    // than the space glyph advance, because CJK fonts often have very narrow
    // space glyphs that produce absurdly high badness on Latin text.
    const double space_w  = hb_advance_px(hb_font, " ");
    const double space_s  = pt_size / 3.0;   // 1/3 em stretch
    const double space_k  = pt_size / 9.0;   // 1/9 em shrink

    const double text_w   = page_w - 2.0 * margin;
    const double line_h   = pt_size * leading;

    // Hyphenation dictionary — on by default, disabled by --nohyphen.
    static const char* default_dict = "/usr/share/hyphen/hyph_en_US.dic";
    HyphenDict* hyph_dict = nullptr;
    if (!hyphen_off) {
        if (hyphen_dict_path.empty()) hyphen_dict_path = default_dict;
        hyph_dict = hnj_hyphen_load(hyphen_dict_path.c_str());
        if (!hyph_dict)
            std::cerr << "Warning: cannot load hyphen dict: "
                      << hyphen_dict_path << '\n';
    }

    // Knuth-Plass params
    Params kp_params;
    kp_params.tolerance        = tolerance;
    kp_params.emergency_stretch = space_s;   // last-resort stretch = 1/3 em

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

    std::ostream* trace_out = tracing_paras ? &std::cerr : nullptr;
    auto paras = split_paragraphs(text);

    for (size_t pi = 0; pi < paras.size(); ++pi) {
        const std::string& para = paras[pi];

        // Build items using ICU Unicode Line Breaking Algorithm (UAX #14)
        auto items = build_para_items(hb_font, para, space_w, space_s, space_k, pt_size, hyph_dict);
        if (items.size() <= 2) continue;  // empty paragraph (only sentinel items)

        if (trace_out)
            *trace_out << "\n[paragraph " << (pi + 1) << "]\n";

        LineSpec spec = LineSpec::uniform(text_w);
        std::vector<int> breaks;
        try {
            breaks = break_paragraph(items, spec, kp_params, trace_out);
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

            // Check if this line ends at a hyphen break
            bool   line_ends_hyphen = false;
            double hyphen_w         = 0.0;
            if (seg_end < static_cast<int>(items.size()))
                if (auto* pen = std::get_if<Penalty>(&items[seg_end]))
                    if (pen->flagged) {
                        line_ends_hyphen = true;
                        hyphen_w = hb_advance_px(hb_font, "-");
                    }

            // Measure natural width + stretch + shrink for this line
            double nat = hyphen_w, stretch = 0.0, shrink = 0.0;
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
            }
            if (line_ends_hyphen)
                shape_to_glyphs(hb_font, "-", pen_x, baseline_y, glyphs);

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

    if (hyph_dict) hnj_hyphen_free(hyph_dict);
    hb_font_destroy(hb_font);
    FT_Done_Face(ft_face);
    FT_Done_FreeType(ft_lib);

    std::cout << "Wrote " << output_path
              << "  (" << page_w << 'x' << page_h << ")\n";
    return 0;
}
