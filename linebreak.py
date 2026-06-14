#!/usr/bin/env python3
"""
Knuth-Plass optimal line-breaking algorithm.

Extracted and reimplemented from tex.p (TeX by D.E. Knuth).
Mirrors the structure of trybreak / postlinebreak / the active-list scan
as described in:
  Knuth & Plass, "Breaking Paragraphs into Lines",
  Software—Practice and Experience, 11(11):1119-1184, 1981.

Usage:
    python3 linebreak.py                      # run built-in demo
    python3 linebreak.py "your text" WIDTH    # break custom text
"""

from __future__ import annotations
import sys
from dataclasses import dataclass, field
from typing import List, Optional, Tuple

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------
INF_PENALTY = 10_000        # forbidden / forced break threshold (TeX: 10000)
INF_BAD     = 10_000        # maximum badness
AWFUL_BAD   = 10_000_000    # demerits sentinel (effectively infinite)

VERY_LOOSE = 0
LOOSE      = 1
DECENT     = 2
TIGHT      = 3


# ---------------------------------------------------------------------------
# Paragraph item types
# ---------------------------------------------------------------------------

@dataclass
class Box:
    """Rigid item (character, word fragment, rule). Cannot stretch or shrink."""
    width: float
    text: str = ""


@dataclass
class Glue:
    """Flexible space: natural width w, max stretch +y, max shrink -z."""
    width: float
    stretch: float
    shrink: float


@dataclass
class Penalty:
    """Break desirability hint.
      >= +INF_PENALTY → no break allowed
      <= -INF_PENALTY → forced break
      0               → neutral
    """
    value: float
    flagged: bool = False    # True = hyphen-like (affects double-hyphen demerits)


# ---------------------------------------------------------------------------
# Parameters
# ---------------------------------------------------------------------------

@dataclass
class Params:
    line_penalty:          float = 10      # added to badness each line
    hyphen_penalty:        float = 50      # extra demerits at hyphen break
    ex_hyphen_penalty:     float = 50      # extra at explicit hyphen
    double_hyphen_demerits: float = 10000  # consecutive hyphen breaks
    adj_demerits:          float = 10000   # adjacent incompatible fit classes
    tolerance:             float = 200     # max badness before pass 2
    pre_tolerance:         float = 100     # max badness in first pass
    emergency_stretch:     float = 0       # extra stretch on final pass


# ---------------------------------------------------------------------------
# Line-width specification
# ---------------------------------------------------------------------------

@dataclass
class LineSpec:
    """Width for each line of the paragraph."""
    widths: List[float]    # widths[i] is the width of line i+1
    last: float = 0.0      # width for all lines beyond widths list

    @classmethod
    def uniform(cls, w: float) -> "LineSpec":
        return cls(widths=[], last=w)

    def width(self, line: int) -> float:
        """Return target width for the given 1-based line number."""
        if 1 <= line <= len(self.widths):
            return self.widths[line - 1]
        return self.last


# ---------------------------------------------------------------------------
# Active node (one feasible break point under consideration)
# Mirrors TeX's active node (3 halfwords of mem[]).
# ---------------------------------------------------------------------------

@dataclass
class _Active:
    pos:       int    # index into items[] of this break (-1 = start of para)
    line:      int    # line number that ends at this break (0 = before para)
    fit:       int    # fit class (VERY_LOOSE..TIGHT) of this break's line
    flagged:   bool   # was this break flagged (hyphen)?
    demerits:  float  # total accumulated demerits
    # cumulative widths *at* this break point (sum of everything on this line
    # and all previous lines up to, but not including, the break glue)
    tw: float = 0.0   # total natural width
    ts: float = 0.0   # total stretch
    tk: float = 0.0   # total shrink


# ---------------------------------------------------------------------------
# badness(shortfall, total_stretch_or_shrink) — direct from TeX §108
# ---------------------------------------------------------------------------

def _badness(t: float, s: float) -> float:
    if t == 0:
        return 0.0
    if s <= 0:
        return float(INF_BAD)
    r = t / s
    b = round(100.0 * r ** 3)
    return min(float(INF_BAD), float(b))


# ---------------------------------------------------------------------------
# The main algorithm
# ---------------------------------------------------------------------------

def _linebreak(
    items: list,
    spec: LineSpec,
    params: Params,
    tolerance: float,
    extra_stretch: float = 0.0,
) -> Optional[List[_Active]]:
    """
    Single pass of the Knuth-Plass algorithm with given tolerance.

    Returns the final active list (non-empty = success) or None.
    Each active node that survives until the forced end-break is a
    candidate for the optimal solution.

    The passive chain is encoded directly in the _Active objects:
    we store a `prev` pointer to enable traceback.
    """
    # We augment _Active with a prev pointer for traceback.
    # Using a parallel list instead of modifying the frozen dataclass.
    prev_of: dict[int, Optional[_Active]] = {}   # id(node) -> predecessor node

    # Seed the active list: one node representing the start of the paragraph.
    seed = _Active(pos=-1, line=0, fit=DECENT, flagged=False, demerits=0)
    active: List[_Active] = [seed]
    prev_of[id(seed)] = None

    # Running sums of natural width / stretch / shrink from start of paragraph
    # to the position just *before* the current item (updated as we scan).
    cum_w = cum_s = cum_k = 0.0

    for i, item in enumerate(items):
        # -----------------------------------------------------------------
        # Determine if this position is a legal break point, and if so
        # what penalty applies.
        # Legal breaks (mirroring TeX §813):
        #   - Glue node, if preceded by a Box
        #   - Penalty node with value < INF_PENALTY
        # -----------------------------------------------------------------
        is_break = False
        pi       = 0.0
        is_flag  = False

        if isinstance(item, Glue):
            # Legal only after a box (TeX rule)
            if i > 0 and isinstance(items[i - 1], Box):
                is_break = True
                pi       = 0.0
                is_flag  = False
        elif isinstance(item, Penalty):
            if item.value < INF_PENALTY:
                is_break = True
                pi       = item.value
                is_flag  = item.flagged

        # -----------------------------------------------------------------
        # Compute break_width: cumulative totals for a line ending HERE.
        # If we break at a glue, that glue is discarded (not on either line).
        # The glue has NOT been added to cum_w yet at this point, so
        # break_width = cum_w (the glue simply won't be counted).
        # For a penalty break, the penalty itself has no width.
        # -----------------------------------------------------------------
        if is_break:
            if isinstance(item, Glue):
                bw, bs, bk = cum_w, cum_s, cum_k
                # glue is discarded; cum_* will be updated below after try_break
            else:
                bw, bs, bk = cum_w, cum_s, cum_k

            # -------------------------------------------------------------
            # try_break: for each active node, consider breaking here.
            # Mirrors procedure trybreak in tex.p §829.
            # -------------------------------------------------------------
            if pi <= -INF_PENALTY:
                pi = float(-INF_PENALTY)    # clamp forced break

            new_active: List[_Active] = []
            survivors:  List[_Active] = []

            min_dem    = [AWFUL_BAD] * 4
            best_prev  = [None]      * 4
            best_line  = [0]         * 4
            global_min = AWFUL_BAD

            for a in active:
                # Width of candidate line from a.pos to here
                line_w = bw - a.tw + extra_stretch
                line_s = bs - a.ts + extra_stretch
                line_k = bk - a.tk

                line_num = a.line + 1
                target   = spec.width(line_num)
                shortfall = target - line_w

                # Classify and compute badness (§851-853)
                if shortfall > 0:
                    b = _badness(shortfall, line_s)
                    if   b > 99: fc = VERY_LOOSE
                    elif b > 12: fc = LOOSE
                    else:        fc = DECENT
                elif shortfall < 0:
                    b  = _badness(-shortfall, line_k)
                    fc = TIGHT if b > 12 else DECENT
                else:
                    b  = 0.0
                    fc = DECENT

                # Deactivation rule (§854 in tex.p):
                # - Overfull lines (shortfall < 0, line already too long):
                #   deactivate if b > tolerance — future items only add width.
                # - Underfull lines (shortfall >= 0): KEEP the node active
                #   even if b > tolerance — future items may fill the line.
                # - Forced break (pi = -INF_PENALTY): never deactivate.
                overfull = (shortfall < 0)
                if overfull and b > tolerance and pi != -INF_PENALTY:
                    continue   # line already too long; discard this node
                survivors.append(a)

                # Skip recording this as a break if underfull and too bad
                if b > tolerance and not overfull and pi != -INF_PENALTY:
                    continue

                # Demerits (§855, §859)
                if pi == -INF_PENALTY or b >= INF_BAD:
                    d = 0.0    # artificial: forced or desperate break
                else:
                    d = (params.line_penalty + b) ** 2
                    if pi > 0:
                        d += pi * pi
                    elif pi > -INF_PENALTY:
                        d -= pi * pi
                    if is_flag and a.flagged:
                        d += params.double_hyphen_demerits
                    if abs(fc - a.fit) > 1:
                        d += params.adj_demerits

                d += a.demerits

                if d <= min_dem[fc]:
                    min_dem[fc]   = d
                    best_prev[fc] = a
                    best_line[fc] = line_num
                    if d < global_min:
                        global_min = d

            # Create new active nodes for the best break in each fit class (§845)
            if global_min < AWFUL_BAD:
                for fc in range(4):
                    if min_dem[fc] <= global_min + params.adj_demerits:
                        node = _Active(
                            pos      = i,
                            line     = best_line[fc],
                            fit      = fc,
                            flagged  = is_flag,
                            demerits = min_dem[fc],
                            tw = bw,
                            ts = bs,
                            tk = bk,
                        )
                        new_active.append(node)
                        prev_of[id(node)] = best_prev[fc]

            active = survivors + new_active

        # -----------------------------------------------------------------
        # Update running sums (AFTER try_break, matching TeX's scan order)
        # -----------------------------------------------------------------
        if isinstance(item, Box):
            cum_w += item.width
        elif isinstance(item, Glue):
            cum_w += item.width
            cum_s += item.stretch
            cum_k += item.shrink
        # Penalty has no width

    # ---------------------------------------------------------------------
    # Collect complete-paragraph nodes.
    # text_to_items() terminates with Glue(INF stretch) + Penalty(-INF).
    # The try_break for Penalty(-INF) creates active nodes whose position
    # is that final penalty index — these represent complete paragraphs.
    # We also accept nodes created during earlier forced-break processing.
    # All nodes in `active` whose `pos` equals the final item index are
    # end-of-paragraph nodes; pick the one with minimum total demerits.
    # For safety also run one more forced-break scan over the whole list.
    # ---------------------------------------------------------------------
    final_penalty_pos = len(items) - 1   # index of the Penalty(-INF) item

    # Nodes created at the final penalty position are complete paragraphs.
    final_nodes = [a for a in active if a.pos == final_penalty_pos]

    # Fallback: if none were created at that exact position (e.g. items list
    # doesn't end with our terminator), pick any active node — last resort.
    if not final_nodes:
        final_nodes = active

    if not final_nodes:
        return None

    # Attach the shared prev_of dict for traceback
    for n in final_nodes:
        n._prev_of = prev_of   # type: ignore[attr-defined]

    return final_nodes


def _traceback(final_node: _Active) -> List[int]:
    """Follow prev pointers from final_node back to the seed, collect break positions."""
    prev_of = final_node._prev_of   # type: ignore[attr-defined]
    breaks  = []
    cur     = final_node
    while cur is not None:
        if cur.pos >= 0:
            breaks.append(cur.pos)
        cur = prev_of.get(id(cur))
    breaks.reverse()
    return breaks


# ---------------------------------------------------------------------------
# Public API
# ---------------------------------------------------------------------------

def break_paragraph(
    items: list,
    spec: LineSpec,
    params: Optional[Params] = None,
) -> List[int]:
    """
    Find optimal line breaks for a paragraph represented as Box/Glue/Penalty items.

    Returns a list of item indices where breaks occur.  Each index points to
    the Glue or Penalty item at which the break is taken (glue is discarded;
    a flagged Penalty represents a hyphen).

    Tries up to three passes (pre_tolerance → tolerance → emergency_stretch),
    mirroring TeX §828.

    Raises ValueError if no feasible break sequence exists.
    """
    if params is None:
        params = Params()

    passes = [
        (params.pre_tolerance, 0.0),
        (params.tolerance,     0.0),
        (params.tolerance,     params.emergency_stretch),
    ]

    for tolerance, extra in passes:
        result = _linebreak(items, spec, params, tolerance, extra)
        if result:
            # Pick the node with lowest total demerits
            best = min(result, key=lambda n: n.demerits)
            return _traceback(best)

    raise ValueError(
        "Cannot break paragraph into lines within the given constraints. "
        "Try increasing tolerance or emergency_stretch."
    )


# ---------------------------------------------------------------------------
# post_line_break: turn break indices into rendered lines
# Mirrors procedure postlinebreak in tex.p §877.
# ---------------------------------------------------------------------------

def post_line_break(
    items: list,
    breaks: List[int],
    spec: LineSpec,
) -> List[str]:
    """
    Render paragraph into lines given break positions.

    Returns a list of (line_string, badness, fit_description) tuples
    as formatted strings.
    """
    lines   = []
    starts  = [-1] + breaks        # break position before each line
    ends    = breaks + [len(items)]

    for line_num, (start, end) in enumerate(zip(starts, ends), start=1):
        # Collect items for this line
        # Start after the break item; end before/at the break item.
        seg_start = start + 1
        seg_end   = end   # break item itself is not on the line (glue discarded)

        segment = items[seg_start:seg_end]

        # Strip leading glue (§879 in tex.p)
        while segment and isinstance(segment[0], Glue):
            segment = segment[1:]
        # Strip trailing Penalty only; keep trailing Glue (parfillskip absorbs shortfall)

        # Measure
        nat     = sum(i.width   if isinstance(i, (Box, Glue)) else 0 for i in segment)
        stretch = sum(i.stretch if isinstance(i, Glue)        else 0 for i in segment)
        shrink  = sum(i.shrink  if isinstance(i, Glue)        else 0 for i in segment)

        target    = spec.width(line_num)
        shortfall = target - nat

        if shortfall > 0 and stretch > 0:
            ratio   = shortfall / stretch
            badness = _badness(shortfall, stretch)
            fit     = "very loose" if badness > 99 else ("loose" if badness > 12 else "decent")
        elif shortfall < 0 and shrink > 0:
            ratio   = shortfall / shrink   # negative
            badness = _badness(-shortfall, shrink)
            fit     = "tight"
        else:
            ratio   = 0.0
            badness = 0.0
            fit     = "perfect"

        # Render
        is_last = (end == len(items))
        hyphen  = ""
        if not is_last and end < len(items) and isinstance(items[end], Penalty):
            if items[end].flagged:
                hyphen = "-"

        if not segment:
            continue   # skip empty trailing "lines" from the paragraph terminator
        rendered = _render(segment, ratio) + hyphen
        lines.append(f"{rendered:<{int(target)}}  [bad={badness:5.0f}  {fit}]")

    return lines


def _render(segment: list, ratio: float) -> str:
    parts = []
    for item in segment:
        if isinstance(item, Box):
            parts.append(item.text)
        elif isinstance(item, Glue):
            if ratio >= 0:
                w = item.width + ratio * item.stretch
            else:
                w = item.width + ratio * item.shrink
            parts.append(" " * max(1, round(w)))
        elif isinstance(item, Penalty) and item.flagged:
            parts.append("-")
    return "".join(parts)


# ---------------------------------------------------------------------------
# Convenience: build items from plain text (word-level, monospaced)
# ---------------------------------------------------------------------------

def text_to_items(
    text: str,
    space_width:   float = 1.0,
    space_stretch: float = 0.5,
    space_shrink:  float = 0.333,
) -> list:
    """
    Convert a plain string into Box/Glue/Penalty items.
    Words are single Boxes; spaces become Glue.
    A final infinite-stretch Glue + forced Penalty terminates the paragraph.
    """
    items: list = []
    words = text.split()
    for wi, word in enumerate(words):
        items.append(Box(width=float(len(word)), text=word))
        if wi < len(words) - 1:
            items.append(Glue(space_width, space_stretch, space_shrink))
    # paragraph terminator
    items.append(Glue(0, float(INF_PENALTY), 0))
    items.append(Penalty(float(-INF_PENALTY)))
    return items


# ---------------------------------------------------------------------------
# Demo / CLI
# ---------------------------------------------------------------------------

_DEMO_TEXT = (
    "In olden times when wishing still helped one there lived a king "
    "whose daughters were all beautiful but the youngest was so beautiful "
    "that the sun itself which has seen so much was astonished whenever it "
    "shone in her face. Close by the kings castle lay a great dark forest "
    "and under an old lime tree in the forest was a well and when the day "
    "was very warm the kings child went out into the forest and sat down "
    "by the side of the cool fountain and when she was bored she took a "
    "golden ball and threw it up on high and caught it and this ball was "
    "her greatest delight."
)


def demo(text: str = _DEMO_TEXT, width: int = 72):
    items  = text_to_items(text)
    spec   = LineSpec.uniform(float(width))
    params = Params(tolerance=200, pre_tolerance=100, line_penalty=10)

    breaks = break_paragraph(items, spec, params)
    lines  = post_line_break(items, breaks, spec)

    print(f"Paragraph broken into {len(lines)} lines  (target width = {width})")
    print("─" * (width + 22))
    for ln, line in enumerate(lines, 1):
        print(f"  {ln:2d}: {line}")
    print("─" * (width + 22))
    words_used = len([i for i in items if isinstance(i, Box)])
    print(f"  {words_used} words, {len(breaks)} break points: {breaks}")


if __name__ == "__main__":
    if len(sys.argv) >= 2:
        t = sys.argv[1]
        w = int(sys.argv[2]) if len(sys.argv) >= 3 else 72
        demo(t, w)
    else:
        demo()
