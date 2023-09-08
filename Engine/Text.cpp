#include "Text.h"
#include <assert.h>

Text::Text(std::string pathName, Color chroma) 
	:
	image(pathName),
	chroma(chroma),
	glyphWidth(image.GetWidth() / nColumns),
	glyphHeight(image.GetHeight() /nRows)
{
	assert(glyphWidth * nColumns == image.GetWidth());
	assert(glyphHeight * nRows == image.GetHeight());
}

void Text::DrawText(const std::string text, const Vei2& position, const Color& fillColor, Graphics& gfx) const {
	for (int i = 0; i < text.length(); i++) {
		const char c = text[i];
		RectI charRect = MapGlyphRect(c);
		gfx.DrawSpriteSubstituteColor(position.x + i * glyphWidth, position.y, charRect, image, fillColor, chroma);
	}
}

RectI Text::MapGlyphRect(char c) const {
	assert(firstChar <= c && c <= lastChar);
	const int glyphIndex = c - firstChar;
	const int glyphY = glyphIndex / nColumns;
	const int glyphX = glyphIndex % nColumns;
	return{ glyphX * glyphWidth, glyphY * glyphHeight, glyphWidth, glyphHeight };
}