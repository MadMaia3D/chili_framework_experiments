#pragma once
#include "Vector2.h"

class RectI {
public:
	RectI(int x, int y, int width, int height);
	RectI(Vector2 position, int width, int height);
	Vector2 GetPosition();
	int GetWidth();
	int GetHeight();
private:
	int x0;
	int y0;
	int x1;
	int y1;
};