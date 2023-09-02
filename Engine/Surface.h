#pragma once
#include "Colors.h"
class Surface {
public:
	Surface(int width, int height);
	Surface(const Surface& source);
	Surface& operator=(const Surface& source);
	~Surface();
private:
	int width;
	int height;
	Color* pPixels = nullptr;
};