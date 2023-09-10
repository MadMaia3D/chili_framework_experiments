#pragma once
#include "Graphics.h"
#include "SpriteEffects.h"
#include <string>

class Text {
public:
	Text(std::string pathName, const Color& fillColor = Colors::White, const Color& chroma = Colors::White);
	void DrawText(const std::string text, const Vei2& position, const Color& fillColor, Graphics& gfx) const;
private:
	RectI MapGlyphRect(char c) const;
private:
	const Surface image;
	SpriteEffects::Substitution spriteEffect;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	int glyphWidth;
	int glyphHeight;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};