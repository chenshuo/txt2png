# playground

## tex — Knuth-Plass line-breaking & text-to-PNG renderer

Tools in the `tex/` directory implement the Knuth-Plass optimal line-breaking
algorithm and a CLI renderer that produces PNG images from plain-text files.

### Dependencies

Install build tools and runtime libraries (Ubuntu/Debian):

```bash
sudo apt-get install -y \
    build-essential \
    libcairo2-dev \
    libfreetype-dev \
    libharfbuzz-dev \
    libicu-dev \
    libhyphen-dev \
    fonts-noto-cjk \
    hyphen-en-us
```

### Build

```bash
cd tex
make
```

This produces two binaries:

| Binary | Description |
|--------|-------------|
| `linebreak_cpp` | CLI demo of the Knuth-Plass algorithm (monospaced, ASCII) |
| `textrender` | Renders a text file to PNG using HarfBuzz + Knuth-Plass + Cairo |

### Usage

#### linebreak_cpp

```
./linebreak_cpp ["text to break"] [line-width]
```

```bash
./linebreak_cpp "In olden times when wishing still helped one..." 72
```

#### textrender

```
./textrender [OPTIONS] INPUT.txt OUTPUT.png

Options:
  --font PATH        TTF/OTF/TTC font file
                     (default: /usr/share/fonts/opentype/noto/NotoSerifCJK-Regular.ttc)
  --size N           font size in points  (default: 12)
  --width N          page width in pixels  (default: 800)
  --height N         page height in pixels (default: 1000)
  --margin N         margin in pixels on all sides (default: 72)
  --leading N        line-height multiplier (default: 1.4)
  --tolerance N      Knuth-Plass badness tolerance (default: 200)
  --hyphen           enable English hyphenation (uses hyph_en_US.dic)
  --hyphen-dict PATH use a custom libhyphen dictionary file
```

```bash
# Render Chinese + English text with hyphenation enabled
./textrender --hyphen --size 14 --width 800 --height 1000 sample_cjk.txt out.png
```

### Features

- **Knuth-Plass optimal line breaking** — same algorithm as TeX, minimising
  total demerits across the whole paragraph rather than breaking greedily.
- **HarfBuzz text shaping** — correct glyph advances and kerning for Latin,
  CJK, and mixed scripts.
- **ICU Unicode Line Breaking (UAX #14)** — determines legal break
  opportunities; CJK characters can break between any two characters.
- **libhyphen word hyphenation** — TeX-pattern hyphenation for English
  (enabled with `--hyphen`); consecutive hyphenated lines are penalised via
  Knuth-Plass `double_hyphen_demerits`.
- **Cairo PNG rendering** — anti-aliased vector rasterisation via FreeType.
