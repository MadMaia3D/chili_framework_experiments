#include "RectI.h"

RectI::RectI(int x, int y, int width, int height) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

RectI::RectI(Vector2 position, int width, int height) {
	RectI(position.x, position.y, width, height);
}

Vector2 RectI::GetPosition() {
	return Vector2(left, top);
}

int RectI::GetWidth() {
	return right - left;
}

int RectI::GetHeight() {
	return bottom - top;
}

bool RectI::ContainsPoint(Vector2 point) {
	return left <= point.x && point.x <= right && top <= point.y && point.y <= bottom;
}

RectI RectI::GetRectFromCenter(Vector2 center, int halfWidth, int halfHeight) {
	return RectI(center.x - halfWidth , center.y - halfHeight, halfWidth * 2, halfHeight * 2);
}
