#pragma once
#include "Vector2.h"

class RectI {
public:
	RectI(int x, int y, int width, int height);
	RectI(Vei2 position, int width, int height);
	RectI(Vei2 topLeft, Vei2 bottomBottom);
	bool ContainsPoint(const Vei2& point) const;
	bool IsColliding(const RectI& rect) const;
	int GetWidth() const;
	int GetHeight()const;
public:
	int left;
	int top;
	int right;
	int bottom;
};