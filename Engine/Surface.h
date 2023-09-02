#pragma once
#include <string>
#include <fstream>
#include "Colors.h"

class Surface {
public:
	Surface(std::string pathName);
	Surface(int width, int height);
	Surface(const Surface& source);
	Surface& operator=(const Surface& source);
	~Surface();
	int GetWidth() const;
	int GetHeight() const;
	void SetPixel(int x, int y, const Color& color);
	Color GetPixel(int x, int y) const;
private:
	int width;
	int height;
	Color* pPixels = nullptr;
};