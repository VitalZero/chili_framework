#include "Font.h"
#include <cassert>

Font::Font(const std::string & fileName, Color chroma)
	:
	font(fileName),
	glyphWidth(font.GetWidth() / nColumns),
	glyphHeight(font.GetHeight() / nRows),
	chroma(chroma)
{
	assert(glyphWidth * nColumns == font.GetWidth());
	assert(glyphHeight * nRows == font.GetHeight());
}

void Font::DrawText(const std::string & text, const Vei2 & pos, Graphics & gfx)
{
	auto curPos = pos;
	for (auto& c : text)
	{
		if (c == '\n')
		{
			curPos.x = pos.x;
			curPos.y += glyphHeight;
			continue;
		}
		else if (c >= firstChar && c <= lastChar)
		{
			gfx.DrawSpriteSubstitute(curPos.x, curPos.y, Colors::White, MapGlyphRect(c), font, chroma);
		}
		curPos.x += glyphWidth;
	}
}

RectI Font::MapGlyphRect(char c) const
{
	assert(c >= firstChar && c <= lastChar);
	// get the index, removing the number of the first visible char
	const int glyphIndex = c - firstChar;
	// map the glyph according to cols and rows
	const int yGlyph = glyphIndex / nColumns;
	const int xGlyph = glyphIndex % nColumns;

	return RectI(
		{ xGlyph * glyphWidth, yGlyph * glyphHeight }, 
		glyphWidth, glyphHeight
	);
}
