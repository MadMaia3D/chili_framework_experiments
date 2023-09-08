#pragma once
#include "Graphics.h"
#include <string>

class Text {
public:
	Text(std::string pathName, Color chroma = Colors::White);
	void DrawText(const std::string text, const Vei2& position, const Color& fillColor, Graphics& gfx) const;
private:
	RectI MapGlyphRect(char c) const;
private:
	const Surface image;
	const Color chroma;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	int glyphWidth;
	int glyphHeight;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};