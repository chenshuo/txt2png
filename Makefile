CXX      = g++
CXXFLAGS = -std=c++17 -O2 $(shell pkg-config --cflags harfbuzz cairo freetype2)
LIBS     = $(shell pkg-config --libs harfbuzz cairo freetype2)

TR_CXXFLAGS = $(CXXFLAGS) $(shell pkg-config --cflags icu-uc icu-i18n)
TR_LIBS     = $(LIBS) $(shell pkg-config --libs icu-uc icu-i18n)

.PHONY: all clean

all: linebreak_cpp textrender

linebreak: linebreak.cpp linebreak.h
	$(CXX) $(CXXFLAGS) linebreak.cpp $(LIBS) -o linebreak

textrender: textrender.cpp linebreak.h
	$(CXX) $(TR_CXXFLAGS) textrender.cpp $(TR_LIBS) -o textrender

clean:
	rm -f linebreak_cpp textrender
