#include "Surface.h"
#include <cassert>

Surface::Surface(int width, int height)
	:
	width(width),
	height(height)
{
	const int totalPixels = width * height;
	pPixels = new Color[totalPixels];
}

Surface::Surface(const Surface& source)
	:
	Surface(source.width, source.height)
{
	const int totalPixels = width * height;
	for (int i = 0; i < totalPixels; i++) {
		pPixels[i] = source.pPixels[i];
	}
}

Surface& Surface::operator=(const Surface& source) {
	delete[] pPixels;
	pPixels = nullptr;

	width = source.width;
	height = source.height;
	const int totalPixels = width * height;

	pPixels = new Color[totalPixels];

	for (int i = 0; i < totalPixels; i++) {
		pPixels[i] = source.pPixels[i];
	}
	return *this;
}

Surface::~Surface() {
	delete[] pPixels;
	pPixels = nullptr;
}

int Surface::GetWidth() const {
	return width;
}

int Surface::GetHeight() const {
	return height;
}

void Surface::SetPixel(int x, int y, const Color& color) {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	pPixels[y * width + x] = color;
}

Color Surface::GetPixel(int x, int y) const {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	return pPixels[y * width + x];
}