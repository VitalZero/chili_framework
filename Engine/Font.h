#pragma once
#include "Surface.h"
#include "Graphics.h"

class Font
{
public:
	Font(const std::string& fileName, Color chroma = Colors::White);
	void DrawText(const std::string& text, const Vei2& pos, Graphics& gfx);
private:
	RectI MapGlyphRect(char c) const;
private:
	Surface font;
	int glyphWidth;
	int glyphHeight;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	Color chroma;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};