#include "ChiliWin.h"
#include <cassert>
#include "Surface.h"
#include <fstream>

Surface::Surface(int width, int height)
	:
	width(width),
	height(height)
{
	assert(width > 0);
	assert(height > 0);
	const int totalPixelsCount = width * height;
	pPixels = new Color[totalPixelsCount];
}

Surface::Surface(std::string file) {
	std::ifstream input(file, std::ios::binary);

	BITMAPFILEHEADER bitmapFileHeader;
	input.read(reinterpret_cast<char*>(&bitmapFileHeader), sizeof(bitmapFileHeader));

	BITMAPINFOHEADER bitmapInfoHeader;
	input.read(reinterpret_cast<char*>(&bitmapInfoHeader), sizeof(bitmapInfoHeader));

	assert(bitmapFileHeader.bfType = 'BM');
	assert(bitmapInfoHeader.biBitCount == 24);
	assert(bitmapInfoHeader.biCompression == BI_RGB);

	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;

	input.seekg(bitmapFileHeader.bfOffBits);
	const int padding = (4 - ((width * 3) % 4)) % 4;

	bool isInverted = false;
	if (height < 0) {
		height = -height;
		isInverted = true;
	}

	pPixels = new Color[width * height];

	if (!isInverted) {
		for (int y = height - 1; y >= 0; y--) {
			for (int x = 0; x < int(width); x++) {
				unsigned char b = input.get();
				unsigned char g = input.get();
				unsigned char r = input.get();
				SetPixel(x, y, Color(r, g, b));
			}
			input.seekg(padding, std::ios_base::cur);
		}
	} else {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < int(width); x++) {
				unsigned char b = input.get();
				unsigned char g = input.get();
				unsigned char r = input.get();
				SetPixel(x, y, Color(r, g, b));
			}
			input.seekg(padding, std::ios_base::cur);
		}
	}
}

Surface::Surface(const Surface& source)
	:
	Surface(source.width, source.height)
{
	const int totalPixelsCount = width * height;
	for (int i = 0; i < totalPixelsCount; i++) {
		pPixels[i] = source.pPixels[i];
	}
}

Surface& Surface::operator=(const Surface& source) {
	if (this == &source) {
		return *this;
	}
	delete [] pPixels;
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