// Knuth-Plass optimal line-breaking algorithm.
//
// Extracted and reimplemented from tex.p (TeX by D.E. Knuth).
// Mirrors the structure of trybreak / postlinebreak / the active-list scan
// as described in:
//   Knuth & Plass, "Breaking Paragraphs into Lines",
//   Software--Practice and Experience, 11(11):1119-1184, 1981.
//
// Build:  make linebreak_cpp   (or: c++ -std=c++17 -O2 -o linebreak_cpp linebreak.cpp)
// Usage:  ./linebreak_cpp
//         ./linebreak_cpp "your text here" 72

#include "linebreak.h"

#include <iostream>
#include <sstream>
#include <string>

// ---------------------------------------------------------------------------
// Convenience: build items from plain text (word-level, monospaced)
// ---------------------------------------------------------------------------

static std::vector<Item> text_to_items(
    const std::string& text,
    double space_width   = 1.0,
    double space_stretch = 0.5,
    double space_shrink  = 0.333)
{
    std::vector<Item> items;
    std::istringstream ss(text);
    std::string word;
    bool first = true;

    while (ss >> word) {
        if (!first)
            items.push_back(Glue{space_width, space_stretch, space_shrink});
        items.push_back(Box{static_cast<double>(word.size()), word});
        first = false;
    }

    items.push_back(Glue{0.0, INF_PENALTY, 0.0});   // parfillskip
    items.push_back(Penalty{-INF_PENALTY, false});   // forced end
    return items;
}

// ---------------------------------------------------------------------------
// post_line_break: render lines from break positions.
// ---------------------------------------------------------------------------

struct RenderedLine {
    std::string text;
    double      bad;
    std::string fit;
};

static std::string render_segment(
    const std::vector<Item>& seg,
    double ratio,
    int target_w)
{
    std::string out;
    for (const Item& it : seg) {
        if (auto* b = std::get_if<Box>(&it)) {
            out += b->text;
        } else if (auto* g = std::get_if<Glue>(&it)) {
            double w = (ratio >= 0.0)
                ? g->width + ratio * g->stretch
                : g->width + ratio * g->shrink;
            int sp = std::max(1, static_cast<int>(std::round(w)));
            out.append(static_cast<size_t>(sp), ' ');
        } else if (auto* pen = std::get_if<Penalty>(&it)) {
            if (pen->flagged) out += '-';
        }
    }
    if (static_cast<int>(out.size()) < target_w)
        out.append(static_cast<size_t>(target_w - static_cast<int>(out.size())), ' ');
    return out;
}

static std::vector<RenderedLine> post_line_break(
    const std::vector<Item>& items,
    const std::vector<int>&  breaks,
    const LineSpec&           spec)
{
    std::vector<RenderedLine> lines;
    const int n = static_cast<int>(items.size());

    std::vector<int> starts{-1};
    for (int b : breaks) starts.push_back(b);
    std::vector<int> ends(breaks);
    ends.push_back(n);

    for (size_t li = 0; li < starts.size(); ++li) {
        const int line_num  = static_cast<int>(li) + 1;
        const int seg_start = starts[li] + 1;
        const int seg_end   = ends[li];

        std::vector<Item> seg(
            items.begin() + seg_start,
            items.begin() + seg_end);

        while (!seg.empty() && std::holds_alternative<Glue>(seg.front()))
            seg.erase(seg.begin());

        if (seg.empty()) continue;

        double nat = 0.0, stretch = 0.0, shrink = 0.0;
        for (const Item& it : seg) {
            if (auto* b = std::get_if<Box>(&it))       nat += b->width;
            else if (auto* g = std::get_if<Glue>(&it)) {
                nat += g->width; stretch += g->stretch; shrink += g->shrink;
            }
        }

        const double target = spec.width(line_num);
        const double sfall  = target - nat;
        double ratio = 0.0, bad = 0.0;
        std::string fit;

        if (sfall > 0.0 && stretch > 0.0) {
            ratio = sfall / stretch;
            bad   = badness(sfall, stretch);
            fit   = (bad > 99.0) ? "very loose" : (bad > 12.0) ? "loose" : "decent";
        } else if (sfall < 0.0 && shrink > 0.0) {
            ratio = sfall / shrink;
            bad   = badness(-sfall, shrink);
            fit   = "tight";
        } else {
            fit = "perfect";
        }

        bool hyphen = false;
        if (ends[li] < n)
            if (auto* pen = std::get_if<Penalty>(&items[static_cast<size_t>(ends[li])]))
                hyphen = pen->flagged;

        std::string rendered = render_segment(seg, ratio, static_cast<int>(target));
        if (hyphen) rendered += '-';
        lines.push_back({rendered, bad, fit});
    }

    return lines;
}

// ---------------------------------------------------------------------------
// Demo / main
// ---------------------------------------------------------------------------

static const char* DEMO_TEXT =
    "In olden times when wishing still helped one there lived a king "
    "whose daughters were all beautiful but the youngest was so beautiful "
    "that the sun itself which has seen so much was astonished whenever it "
    "shone in her face. Close by the kings castle lay a great dark forest "
    "and under an old lime tree in the forest was a well and when the day "
    "was very warm the kings child went out into the forest and sat down "
    "by the side of the cool fountain and when she was bored she took a "
    "golden ball and threw it up on high and caught it and this ball was "
    "her greatest delight.";

static void demo(const std::string& text, int width) {
    const auto   items  = text_to_items(text);
    const auto   spec   = LineSpec::uniform(static_cast<double>(width));
    const Params params = {10.0, 10000.0, 10000.0, 200.0, 100.0, 0.0};

    const auto breaks = break_paragraph(items, spec, params);
    const auto lines  = post_line_break(items, breaks, spec);

    const std::string rule(static_cast<size_t>(width + 22), '-');
    std::cout << "Paragraph broken into " << lines.size()
              << " lines  (target width = " << width << ")\n"
              << rule << '\n';

    for (size_t i = 0; i < lines.size(); ++i) {
        const auto& l = lines[i];
        std::printf("  %2zu: %s  [bad=%5.0f  %s]\n",
            i + 1, l.text.c_str(), l.bad, l.fit.c_str());
    }
    std::cout << rule << '\n';

    int nwords = 0;
    for (const auto& it : items)
        if (std::holds_alternative<Box>(it)) ++nwords;

    std::cout << "  " << nwords << " words, " << breaks.size() << " break points: [";
    for (size_t i = 0; i < breaks.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << breaks[i];
    }
    std::cout << "]\n";
}

int main(int argc, char* argv[]) {
    std::string text  = DEMO_TEXT;
    int         width = 72;
    if (argc >= 2) text  = argv[1];
    if (argc >= 3) width = std::stoi(argv[2]);
    try {
        demo(text, width);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
