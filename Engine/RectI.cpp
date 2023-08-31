#include "RectI.h"

RectI::RectI(int x, int y, int width, int height) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

RectI::RectI(Vector2<int> position, int width, int height)
	:
	RectI(position.x, position.y, width, height)
{}

Vector2<int> RectI::GetPosition() {
	return{ left, top };
}

int RectI::GetWidth() const {
	return right - left;
}

int RectI::GetHeight() const {
	return bottom - top;
}

bool RectI::ContainsPoint(Vector2<int> point) {
	return left <= point.x && point.x <= right && top <= point.y && point.y <= bottom;
}

RectI RectI::GetRectFromCenter(Vector2<int> center, int halfWidth, int halfHeight) {
	return RectI(center.x - halfWidth , center.y - halfHeight, halfWidth * 2, halfHeight * 2);
}
