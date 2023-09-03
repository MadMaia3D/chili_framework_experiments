#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>

Surface::Surface(std::string pathName) {
	std::ifstream inputFile(pathName, std::ios_base::binary);
	assert(inputFile);

	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	
	inputFile.read(reinterpret_cast<char*>(&bitmapFileHeader), sizeof(bitmapFileHeader));
	inputFile.read(reinterpret_cast<char*>(&bitmapInfoHeader), sizeof(bitmapInfoHeader));
	
	assert(bitmapFileHeader.bfType == 'MB');
	assert(bitmapInfoHeader.biCompression == BI_RGB);
	assert(bitmapInfoHeader.biBitCount == 24 || bitmapInfoHeader.biBitCount == 32);

	const bool is32Bit = bitmapInfoHeader.biBitCount == 32;
	const bool isReversed = bitmapInfoHeader.biHeight < 0;

	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;

	int startY = height - 1;
	int endY = -1;
	int deltaY = -1;	

	if (isReversed) {
		height = -height;
		startY = 0;
		endY = height;
		deltaY = 1;
	}
	// bitmaps files have a row size that is multiple of 4
	// the padding must be taken in consideration so we can load bitmaps which the width is not multiple of 4
	const int bmpPadding = (4 - (width % 4)) % 4 * 3;
	inputFile.seekg(bitmapFileHeader.bfOffBits, std::ios_base::beg);

	pPixels = new Color[width * height];

	for (int y = startY; y != endY; y += deltaY) {
		for (int x = 0; x < width; x++) {
			const char b = inputFile.get();
			const char g = inputFile.get();
			const char r = inputFile.get();
			pPixels[y * width + x] = Color(r, g, b);
			if (is32Bit) {
				inputFile.seekg(1, std::ios_base::cur);
			}
		}
		inputFile.seekg(bmpPadding, std::ios_base::cur);
	}
}

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

RectI Surface::GetRect() const {
	return RectI(0,0, width, height);
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