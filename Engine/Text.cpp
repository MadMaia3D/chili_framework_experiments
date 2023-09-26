#include "Text.h"
#include <assert.h>

Text::Text(std::string pathName, const Color& fillColor, const Color& chroma)
	:
	image(pathName),
	spriteEffect(fillColor, chroma),
	glyphWidth(image.GetWidth() / nColumns),
	glyphHeight(image.GetHeight() /nRows)
{
	assert(glyphWidth * nColumns == image.GetWidth());
	assert(glyphHeight * nRows == image.GetHeight());
}

void Text::DrawText(const std::string text, const Vei2& position, Graphics& gfx) const {
	Vei2 currentPosition = position;

	for (char c : text) {
		if (c == '\n') {
			currentPosition.x = position.x;
			currentPosition.y += glyphHeight;
			continue;
		}

		if ( c >= firstChar + 1 && c <= lastChar) {
			RectI charRect = MapGlyphRect(c);
			gfx.DrawSprite(currentPosition.x, currentPosition.y, charRect, image, spriteEffect);
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