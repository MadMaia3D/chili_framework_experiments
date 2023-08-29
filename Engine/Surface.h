#pragma once
#include <string>
#include "Colors.h"

class Surface {
public:
	Surface(int width, int height);
	Surface(std::string file);
	Surface(const Surface& source);
	Surface& operator=(const Surface& source);
	~Surface();
	void SetPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	void FillSurface(const Color& c);
	int GetWidth() const;
	int GetHeight() const;
private:
	int width;
	int height;
	Color* pPixels = nullptr;
};