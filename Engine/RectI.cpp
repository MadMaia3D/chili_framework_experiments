#include "RectI.h"

RectI::RectI(int x, int y, int width, int height) {
	x0 = x;
	y0 = y;
	x1 = x + width;
	y1 = y + height;
}

RectI::RectI(Vector2 position, int width, int height) {
	RectI(position.x, position.y, width, height);
}

Vector2 RectI::GetPosition() {
	return Vector2(x0, y0);
}

int RectI::GetWidth() {
	return x1 - x0;
}

int RectI::GetHeight() {
	return y1 - y0;
}