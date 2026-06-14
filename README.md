# txt2png

## txt2png — Knuth-Plass line-breaking & text-to-PNG renderer

Tools implement the Knuth-Plass optimal line-breaking algorithm and a CLI
renderer that produces PNG images from plain-text files, in both C++ and Python.

### Dependencies

#### C++

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

#### Python

```bash
pip install uharfbuzz pycairo freetype-py pyphen
```

### Build (C++)

```bash
make
```

This produces two binaries:

| Binary | Description |
|--------|-------------|
| `linebreak` | CLI demo of the Knuth-Plass algorithm (monospaced, ASCII) |
| `textrender` | Renders a text file to PNG using HarfBuzz + Knuth-Plass + Cairo |

### Usage

#### linebreak

```
./linebreak ["text to break"] [line-width]
```

```bash
./linebreak "In olden times when wishing still helped one..." 72
```

#### textrender (C++)

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
  --nohyphen            disable English hyphenation (on by default when hyph_en_US.dic is found)
  --hyphen-dict PATH    use a custom libhyphen dictionary file
  --tracingparagraphs   print Knuth-Plass diagnostics to stderr (like TeX \tracingparagraphs=1)
```

```bash
# Render Chinese + English text (hyphenation on by default)
./textrender --size 14 --width 800 --height 1000 sample_cjk.txt out.png
```

#### textrender (Python)

```bash
python3 textrender.py --size 14 --width 800 --height 1000 sample_cjk.txt out.png
```

The Python renderer accepts the same options as the C++ version.

### Features

- **Knuth-Plass optimal line breaking** — same algorithm as TeX, minimising
  total demerits across the whole paragraph rather than breaking greedily.
- **HarfBuzz text shaping** — correct glyph advances and kerning for Latin,
  CJK, and mixed scripts.
- **ICU Unicode Line Breaking (UAX #14)** — determines legal break
  opportunities; CJK characters can break between any two characters.
- **libhyphen word hyphenation** — TeX-pattern hyphenation for English,
  enabled by default when `hyph_en_US.dic` is found (disable with `--nohyphen`);
  consecutive hyphenated lines are penalised via Knuth-Plass `double_hyphen_demerits`.
- **`--tracingparagraphs` diagnostics** — mirrors TeX's `\tracingparagraphs=1`,
  printing to stderr: pass header (`@firstpass`/`@secondpass`/`@thirdpass`),
  per-candidate lines (`@\glue via @@N b=B p=P d=D`), per-registered-node
  lines (`@@N: line L.F[−] t=T -> @@M`), and total demerits per paragraph.
- **Cairo PNG rendering** — anti-aliased vector rasterisation via FreeType.
