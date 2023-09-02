#include "Surface.h"

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