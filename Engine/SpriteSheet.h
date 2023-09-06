#pragma once
#include "Graphics.h"

struct SpriteSheet {
	SpriteSheet(int nColumns, int nRows, const Surface& image, const Color& chroma = Colors::Magenta)
		:
		image(image),
		width(image.GetWidth()),
		height(image.GetHeight()),
		nColumns(nColumns),
		nRows(nRows),
		chroma(chroma)
	{}
	const Surface& image;
	const int width;
	const int height;
	const int nColumns;
	const int nRows;
	const Color chroma;
};