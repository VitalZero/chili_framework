#include "Font.h"
#include <cassert>
#include "SpriteEffect.h"

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

void Font::DrawText(const std::string & text, const Vei2 & pos, Color color, Graphics & gfx)
{
	// effect functor
	SpriteEffect::Substitution e{ chroma, color };

	// curPos is the pos where we are drawing on the screen
	auto curPos = pos;
	for (auto& c : text)
	{
		// if newline, move down 1 y pos and reset x pos
		if (c == '\n')
		{
			// reset x pos (carriage return)
			curPos.x = pos.x;
			// move down 1 pos
			curPos.y += glyphHeight;
			continue;
		}
		else if (c >= firstChar && c <= lastChar)
		{
			gfx.DrawSprite(curPos.x, curPos.y, MapGlyphRect(c), font, e);
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
