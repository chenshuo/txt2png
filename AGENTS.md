# Agent Guidelines

## Repository layout

| Path | Contents |
|------|----------|
| `tex/` | Knuth-Plass line-breaking algorithm and text-to-PNG renderer |
| `tex/linebreak.h` | C++ Knuth-Plass algorithm (header-only) |
| `tex/linebreak.py` | Python port of the same algorithm |
| `tex/textrender.cpp` | C++ CLI renderer (HarfBuzz + Cairo + ICU + libhyphen) |
| `tex/textrender.py` | Python CLI renderer (uharfbuzz + pycairo + freetype-py + pyphen) |
| `tex/sample_cjk.txt` | Sample input with CJK, English, and mixed paragraphs |

## Build

```bash
sudo apt-get install -y \
    build-essential libcairo2-dev libfreetype-dev \
    libharfbuzz-dev libicu-dev libhyphen-dev \
    fonts-noto-cjk hyphen-en-us

cd tex && make        # builds linebreak_cpp and textrender
```

## Python dependencies

```bash
pip install uharfbuzz pycairo freetype-py pyphen
```

## Running

```bash
# C++
cd tex && ./textrender --size 14 --width 800 --height 1000 sample_cjk.txt out.png

# Python
cd tex && python3 textrender.py --size 14 --width 800 --height 1000 sample_cjk.txt out.png
```

## Branch

Active development branch: `claude/modest-wright-ioer1p`

## Notes for agents

- Do not commit compiled binaries (`tex/linebreak_cpp`, `tex/textrender`).
- The Python and C++ renderers produce visually equivalent output but are not pixel-perfect due to different advance hinting (HarfBuzz unhinted vs FreeType hinted) and different hyphenation backends (pyphen vs libhyphen).
- `linebreak.py` and `linebreak.h` implement the same Knuth-Plass algorithm; keep them in sync when making algorithmic changes.
