#pragma once
#include "Vector2.h"

class RectI {
public:
	RectI(int x, int y, int width, int height);
	RectI(Vector2<int> position, int width, int height);
	Vector2<int> GetPosition();
	int GetWidth();
	int GetHeight();
	bool ContainsPoint(Vector2<int> point);
	static RectI GetRectFromCenter(Vector2<int> center, int halfWidth, int halfHeight);
public:
	int left;
	int top;
	int right;
	int bottom;
};