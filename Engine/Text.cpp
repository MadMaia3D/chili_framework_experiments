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
	Vei2 currentPosition = position;

	for (char c : text) {
		if (c == '\n') {
			currentPosition.x = position.x;
			currentPosition.y += glyphHeight;
			continue;
		}

		if ( c >= firstChar + 1 && c <= lastChar) {
			RectI charRect = MapGlyphRect(c);
			gfx.DrawSpriteSubstituteColor(currentPosition.x, currentPosition.y, charRect, image, fillColor, chroma);
		}
		currentPosition.x += glyphWidth;
	}
}

RectI Text::MapGlyphRect(char c) const {
	assert(firstChar <= c && c <= lastChar);
	const int glyphIndex = c - firstChar;
	const int glyphY = glyphIndex / nColumns;
	const int glyphX = glyphIndex % nColumns;
	return{ glyphX * glyphWidth, glyphY * glyphHeight, glyphWidth, glyphHeight };
}