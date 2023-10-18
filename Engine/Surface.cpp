#include "ChiliWin.h"
#include <cassert>
#include "Surface.h"
#include <fstream>

Surface::Surface(int width, int height)
	:
	width(width),
	height(height) {
	assert(width > 0);
	assert(height > 0);
	const int totalPixelsCount = width * height;
	pPixels = new Color[totalPixelsCount];
}

Surface::Surface(std::string file) {
	std::ifstream input(file, std::ios::binary);

	assert(input);

	BITMAPFILEHEADER bitmapFileHeader;
	input.read(reinterpret_cast<char*>(&bitmapFileHeader), sizeof(bitmapFileHeader));

	BITMAPINFOHEADER bitmapInfoHeader;
	input.read(reinterpret_cast<char*>(&bitmapInfoHeader), sizeof(bitmapInfoHeader));

	assert(bitmapFileHeader.bfType == 'MB');
	assert(bitmapInfoHeader.biBitCount == 24 || bitmapInfoHeader.biBitCount == 32);
	assert(bitmapInfoHeader.biCompression == BI_RGB);

	const bool is32bit = bitmapInfoHeader.biBitCount == 32;

	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;

	input.seekg(bitmapFileHeader.bfOffBits);
	const int padding = (4 - ((width * 3) % 4)) % 4;

	int startY = height - 1;
	int endY = -1;
	int yIncrement = -1;

	if (height < 0) {
		height = -height;
		startY = 0;
		endY = height;
		yIncrement = 1;
	}

	pPixels = new Color[width * height];

	for (int y = startY; y != endY; y+= yIncrement) {
		for (int x = 0; x < int(width); x++) {
			unsigned char b = input.get();
			unsigned char g = input.get();
			unsigned char r = input.get();
			SetPixel(x, y, Color(r, g, b));
			if (is32bit) {
				input.seekg(1, std::ios_base::cur);
			}
		}
		if(!is32bit){
			input.seekg(padding, std::ios_base::cur);
		}
	}

}

Surface::Surface(const Surface& source)
	:
	Surface(source.width, source.height) {
	const int totalPixelsCount = width * height;
	for (int i = 0; i < totalPixelsCount; i++) {
		pPixels[i] = source.pPixels[i];
	}
}

Surface::Surface(Surface && source)
	:
	width(source.width),
	height(source.height),
	pPixels(source.pPixels)
{
	source.pPixels = nullptr;
	source.width = 0;
	source.height = 0;
}

Surface& Surface::operator=(const Surface& source) {
	if (this == &source) {
		return *this;
	}
	delete[] pPixels;
	pPixels = nullptr;

	width = source.width;
	height = source.height;

	const int totalPixelsCount = width * height;
	pPixels = new Color[totalPixelsCount];

	for (int i = 0; i < totalPixelsCount; i++) {
		pPixels[i] = source.pPixels[i];
	}
	return *this;
}

Surface & Surface::operator=(Surface && rhs)
{
	if (&rhs != this) {
		width = rhs.width;
		height = rhs.height;
		delete[] pPixels;
		pPixels = rhs.pPixels;

		rhs.pPixels = nullptr;
		rhs.width = 0;
		rhs.height = 0;
	}
	return *this;
}

Surface::~Surface() {
	delete[] pPixels;
	pPixels = nullptr;
}

void Surface::SetPixel(int x, int y, Color c) {
	assert(0 <= x && x < width);
	assert(0 <= y && y < height);
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const {
	assert(0 <= x && x < width);
	assert(0 <= y && y < height);
	return pPixels[y * width + x];
}

void Surface::FillSurface(const Color& c) {
	const int totalPixelsCount = width * height;

	for (int i = 0; i < totalPixelsCount; i++) {
		pPixels[i] = c;
	}
}

int Surface::GetWidth() const {
	return width;
}

int Surface::GetHeight() const {
	return height;
}

RectI Surface::GetSurfaceRect() const {
	return RectI(0,0, width, height);
}
