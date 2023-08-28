#include "Surface.h"
#include <cassert>

Surface::Surface(unsigned int width, unsigned int height)
	:
	width(width),
	height(height)
{
	const int totalPixelsCount = width * height;
	pixels = new Color[totalPixelsCount];
}

Surface::Surface(const Surface& source)
	:
	Surface(source.width, source.height)
{
	const int totalPixelsCount = width * height;
	for (int i = 0; i < totalPixelsCount; i++) {
		pixels[i] = source.pixels[i];
	}
}

Surface& Surface::operator=(const Surface& source) {
	if (this == &source) {
		return *this;
	}
	delete [] pixels;
	pixels = nullptr;
	
	width = source.width;
	height = source.height;

	const int totalPixelsCount = width * height;
	pixels = new Color[totalPixelsCount];

	for (int i = 0; i < totalPixelsCount; i++) {
		pixels[i] = source.pixels[i];
	}
	return *this;
}

Surface::~Surface() {
	delete[] pixels;
	pixels = nullptr;
}

void Surface::SetPixel(unsigned int x, unsigned int y, Color c) {
	assert(0 <= x && x < width);
	assert(0 <= y && y < height);
	pixels[y * width + x] = c;
}

Color Surface::GetPixel(unsigned int x, unsigned int y) const {
	assert(0 <= x && x < width);
	assert(0 <= y && y < height);
	return pixels[y * width + x];
}

void Surface::FillSurface(const Color& c) {
	const int totalPixelsCount = width * height;

	for (int i = 0; i < totalPixelsCount; i++) {
		pixels[i] = c;
	}
}

int Surface::GetWidth() const {
	return width;
}

int Surface::GetHeight() const {
	return height;
}