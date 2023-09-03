#include "RectI.h"

RectI::RectI(int x, int y, int width, int height)
	:
	left(x),
	top(y),
	right(x + width),
	bottom(y + height) {
}

RectI::RectI(Vei2 position, int width, int height)
	:
	left(position.x),
	top(position.y),
	right(left + width),
	bottom(top + height) {
}

RectI::RectI(Vei2 topLeft, Vei2 bottomBottom)
	:
	left(topLeft.x),
	top(topLeft.y),
	right(bottomBottom.x),
	bottom(bottomBottom.y) {
}

bool RectI::ContainsPoint(const Vei2& point) const {
	const bool containsOnXaxis = right > point.x && left < point.x;
	const bool containsOnYaxis = bottom > point.y && top < point.y;
	return containsOnXaxis && containsOnYaxis;
}

bool RectI::IsColliding(const RectI& rect) const {
	const bool isCollidingXaxis = right > rect.left && left < rect.right;
	const bool isCollidingYaxis = bottom > rect.top && top < rect.bottom;
	return isCollidingXaxis && isCollidingYaxis;
}

int RectI::GetWidth() const {
	return right - left;
}

int RectI::GetHeight() const {
	return bottom - top;
}

RectI RectI::RectFromCenter(Vei2 point, int width, int height) {
	const int top = point.x - width / 2;
	const int left = point.y - height / 2;
	return RectI(top, left, width, height);
}
