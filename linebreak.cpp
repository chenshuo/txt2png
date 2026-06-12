// Knuth-Plass optimal line-breaking algorithm.
//
// Extracted and reimplemented from tex.p (TeX by D.E. Knuth).
// Mirrors the structure of trybreak / postlinebreak / the active-list scan
// as described in:
//   Knuth & Plass, "Breaking Paragraphs into Lines",
//   Software--Practice and Experience, 11(11):1119-1184, 1981.
//
// Build:  c++ -std=c++17 -O2 -o linebreak linebreak.cpp
// Usage:  ./linebreak
//         ./linebreak "your text here" 72

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

// ---------------------------------------------------------------------------
// Constants (mirror TeX named values)
// ---------------------------------------------------------------------------

static constexpr double INF_PENALTY = 10'000.0;
static constexpr double INF_BAD     = 10'000.0;
static constexpr double AWFUL_BAD   = 10'000'000.0;

enum FitClass { VERY_LOOSE = 0, LOOSE = 1, DECENT = 2, TIGHT = 3 };

// ---------------------------------------------------------------------------
// Paragraph item types
// ---------------------------------------------------------------------------

struct Box {
    double      width;
    std::string text;
};

struct Glue {
    double width;
    double stretch;
    double shrink;
};

struct Penalty {
    double value;
    bool   flagged = false;
};

using Item = std::variant<Box, Glue, Penalty>;

// ---------------------------------------------------------------------------
// Parameters
// ---------------------------------------------------------------------------

struct Params {
    double line_penalty           = 10.0;
    double double_hyphen_demerits = 10'000.0;
    double adj_demerits           = 10'000.0;
    double tolerance              = 200.0;
    double pre_tolerance          = 100.0;
    double emergency_stretch      = 0.0;
};

// ---------------------------------------------------------------------------
// Line-width specification
// ---------------------------------------------------------------------------

struct LineSpec {
    std::vector<double> widths;  // widths[i] = width of line i+1
    double              last;    // fallback for lines beyond widths[]

    static LineSpec uniform(double w) { return {{}, w}; }

    double width(int line) const {
        if (line >= 1 && line <= static_cast<int>(widths.size()))
            return widths[static_cast<size_t>(line - 1)];
        return last;
    }
};

// ---------------------------------------------------------------------------
// Active node — one candidate break point under consideration.
// Mirrors TeX's active node (3 halfwords of mem[]).
// Uses shared_ptr for intrusive prev-chain traceback.
// ---------------------------------------------------------------------------

struct Active {
    int    pos;      // index into items[] of this break (-1 = para start)
    int    line;     // line number ending at this break (0 = before para)
    int    fit;      // FitClass of this break's line
    bool   flagged;  // was this a hyphen-like break?
    double demerits; // accumulated total demerits

    // Cumulative width/stretch/shrink up to (not through) this break
    double tw;
    double ts;
    double tk;

    std::shared_ptr<Active> prev; // back-pointer for traceback (null = seed)
};

using ActivePtr = std::shared_ptr<Active>;

// ---------------------------------------------------------------------------
// badness(shortfall, total_stretch_or_shrink) — TeX §108
// ---------------------------------------------------------------------------

static double badness(double t, double s) {
    if (t == 0.0) return 0.0;
    if (s <= 0.0) return INF_BAD;
    double r = t / s;
    return std::min(INF_BAD, std::round(100.0 * r * r * r));
}

// ---------------------------------------------------------------------------
// Single pass of the Knuth-Plass algorithm.
//
// Returns final-paragraph active nodes (non-empty = success).
// Caller picks the minimum-demerits node and traces back via ->prev.
// ---------------------------------------------------------------------------

static std::vector<ActivePtr> linebreak_pass(
    const std::vector<Item>& items,
    const LineSpec&           spec,
    const Params&             params,
    double                    tolerance,
    double                    extra_stretch)
{
    // Seed: represents the start of the paragraph (no break taken yet).
    auto seed = std::make_shared<Active>(Active{
        -1, 0, DECENT, false, 0.0, 0.0, 0.0, 0.0, nullptr
    });
    std::vector<ActivePtr> active{seed};

    // Cumulative natural width / stretch / shrink scanned so far.
    // Updated AFTER try_break for each item (matching TeX's scan order).
    double cum_w = 0.0, cum_s = 0.0, cum_k = 0.0;

    const int n = static_cast<int>(items.size());

    for (int i = 0; i < n; ++i) {
        const Item& item = items[static_cast<size_t>(i)];

        // -----------------------------------------------------------------
        // Is this a legal break point?  (TeX §813)
        //   Glue   — only after a Box
        //   Penalty — only if value < INF_PENALTY
        // -----------------------------------------------------------------
        bool   is_break = false;
        double pi       = 0.0;
        bool   is_flag  = false;

        if (auto* g = std::get_if<Glue>(&item)) {
            (void)g;
            if (i > 0 && std::holds_alternative<Box>(items[static_cast<size_t>(i - 1)]))
                is_break = true;
        } else if (auto* pen = std::get_if<Penalty>(&item)) {
            if (pen->value < INF_PENALTY) {
                is_break = true;
                pi       = pen->value;
                is_flag  = pen->flagged;
            }
        }

        // -----------------------------------------------------------------
        // try_break — mirrors procedure trybreak in tex.p §829.
        //
        // Break width = cumulative sums at this position.
        // The break glue has NOT been added to cum_* yet (try_break is called
        // before the glue is accumulated), so it is correctly excluded.
        // -----------------------------------------------------------------
        if (is_break) {
            const double bw = cum_w, bs = cum_s, bk = cum_k;
            if (pi <= -INF_PENALTY) pi = -INF_PENALTY;  // clamp forced break

            std::vector<ActivePtr> survivors;
            std::vector<ActivePtr> new_nodes;

            double    min_dem[4]   = {AWFUL_BAD, AWFUL_BAD, AWFUL_BAD, AWFUL_BAD};
            ActivePtr best_prev[4] = {};
            int       best_line[4] = {};
            double    global_min   = AWFUL_BAD;

            for (const ActivePtr& a : active) {
                // Line dimensions from a's break to the current position
                const double line_w = bw - a->tw + extra_stretch;
                const double line_s = bs - a->ts + extra_stretch;
                const double line_k = bk - a->tk;
                const int    lnum   = a->line + 1;
                const double target = spec.width(lnum);
                const double sfall  = target - line_w;

                // Classify and compute badness (§851-853)
                double b  = 0.0;
                int    fc = DECENT;
                if (sfall > 0.0) {
                    b  = badness(sfall, line_s);
                    fc = (b > 99.0) ? VERY_LOOSE : (b > 12.0) ? LOOSE : DECENT;
                } else if (sfall < 0.0) {
                    b  = badness(-sfall, line_k);
                    fc = (b > 12.0) ? TIGHT : DECENT;
                }

                // Deactivation rule (§854):
                // Overfull lines only get longer as we add items → deactivate.
                // Underfull lines may still improve → keep active, skip this break.
                const bool overfull = (sfall < 0.0);
                if (overfull && b > tolerance && pi != -INF_PENALTY)
                    continue;  // deactivate permanently

                survivors.push_back(a);

                if (b > tolerance && !overfull && pi != -INF_PENALTY)
                    continue;  // too underfull for this break; try later positions

                // Demerits (§855, §859)
                double d = 0.0;
                if (pi != -INF_PENALTY && b < INF_BAD) {
                    d = (params.line_penalty + b) * (params.line_penalty + b);
                    if (pi > 0.0)             d += pi * pi;
                    else if (pi > -INF_PENALTY) d -= pi * pi;
                    if (is_flag && a->flagged)  d += params.double_hyphen_demerits;
                    if (std::abs(fc - a->fit) > 1) d += params.adj_demerits;
                }
                d += a->demerits;

                if (d <= min_dem[fc]) {
                    min_dem[fc]   = d;
                    best_prev[fc] = a;
                    best_line[fc] = lnum;
                    if (d < global_min) global_min = d;
                }
            }

            // Create new active nodes for the best break in each fit class (§845)
            if (global_min < AWFUL_BAD) {
                for (int fc = 0; fc < 4; ++fc) {
                    if (min_dem[fc] <= global_min + params.adj_demerits) {
                        new_nodes.push_back(std::make_shared<Active>(Active{
                            i, best_line[fc], fc, is_flag,
                            min_dem[fc], bw, bs, bk,
                            best_prev[fc]
                        }));
                    }
                }
            }

            // active = survivors + new_nodes
            survivors.insert(survivors.end(),
                std::make_move_iterator(new_nodes.begin()),
                std::make_move_iterator(new_nodes.end()));
            active = std::move(survivors);
        }

        // -----------------------------------------------------------------
        // Update cumulative sums (AFTER try_break — TeX scan order)
        // -----------------------------------------------------------------
        if (auto* b = std::get_if<Box>(&item)) {
            cum_w += b->width;
        } else if (auto* g = std::get_if<Glue>(&item)) {
            cum_w += g->width;
            cum_s += g->stretch;
            cum_k += g->shrink;
        }
        // Penalty has no width contribution
    }

    // Collect complete-paragraph nodes: those created at the final Penalty(-INF).
    const int final_pos = n - 1;
    std::vector<ActivePtr> finals;
    for (const ActivePtr& a : active)
        if (a->pos == final_pos) finals.push_back(a);
    if (finals.empty()) finals = active;   // fallback
    return finals;
}

// ---------------------------------------------------------------------------
// Traceback: follow ->prev pointers and collect break positions.
// ---------------------------------------------------------------------------

static std::vector<int> traceback(const ActivePtr& node) {
    std::vector<int> breaks;
    for (const Active* cur = node.get(); cur; cur = cur->prev.get())
        if (cur->pos >= 0) breaks.push_back(cur->pos);
    std::reverse(breaks.begin(), breaks.end());
    return breaks;
}

// ---------------------------------------------------------------------------
// Public API: break_paragraph
//
// Tries up to three passes (pre_tolerance → tolerance → emergency_stretch),
// mirroring TeX §828.  Returns item indices of break points.
// ---------------------------------------------------------------------------

std::vector<int> break_paragraph(
    const std::vector<Item>& items,
    const LineSpec&           spec,
    const Params&             params = {})
{
    const double tols[3]   = {params.pre_tolerance, params.tolerance, params.tolerance};
    const double extras[3] = {0.0, 0.0, params.emergency_stretch};

    for (int pass = 0; pass < 3; ++pass) {
        auto finals = linebreak_pass(items, spec, params, tols[pass], extras[pass]);
        if (!finals.empty()) {
            auto best = *std::min_element(finals.begin(), finals.end(),
                [](const ActivePtr& a, const ActivePtr& b) {
                    return a->demerits < b->demerits;
                });
            return traceback(best);
        }
    }

    throw std::runtime_error(
        "Cannot break paragraph: no feasible solution. "
        "Try increasing tolerance or emergency_stretch.");
}

// ---------------------------------------------------------------------------
// post_line_break: render lines from break positions.
// Mirrors procedure postlinebreak in tex.p §877.
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
    // Pad to target width for aligned display
    if (static_cast<int>(out.size()) < target_w)
        out.append(static_cast<size_t>(target_w - static_cast<int>(out.size())), ' ');
    return out;
}

std::vector<RenderedLine> post_line_break(
    const std::vector<Item>& items,
    const std::vector<int>&  breaks,
    const LineSpec&           spec)
{
    std::vector<RenderedLine> lines;
    const int n = static_cast<int>(items.size());

    // starts[i] / ends[i] bracket the items on line i+1
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

        // Strip leading glue (§879)
        while (!seg.empty() && std::holds_alternative<Glue>(seg.front()))
            seg.erase(seg.begin());

        if (seg.empty()) continue;  // paragraph terminator artefact

        // Measure
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

        // Check for hyphen break
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
// Convenience: build items from plain text (word-level, monospaced)
// ---------------------------------------------------------------------------

std::vector<Item> text_to_items(
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
