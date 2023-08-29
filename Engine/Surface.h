#pragma once
#include <string>
#include "Colors.h"

class Surface {
public:
	Surface(unsigned int width, unsigned int height);
	Surface(std::string file);
	Surface(const Surface& source);
	Surface& operator=(const Surface& source);
	~Surface();
	void SetPixel(unsigned int x, unsigned int y, Color c);
	Color GetPixel(unsigned int x, unsigned int y) const;
	void FillSurface(const Color& c);
	int GetWidth() const;
	int GetHeight() const;
private:
	unsigned int width;
	unsigned int height;
	Color* pPixels = nullptr;
};