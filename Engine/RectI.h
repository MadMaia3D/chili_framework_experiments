#pragma once
#include "Vector2.h"

class RectI {
public:
	RectI(int x, int y, int width, int height);
	RectI(Vector2 position, int width, int height);
	Vector2 GetPosition();
	int GetWidth();
	int GetHeight();
	bool ContainsPoint(Vector2 point);
	static RectI GetRectFromCenter(Vector2 center, int halfWidth, int halfHeight);
public:
	int left;
	int top;
	int right;
	int bottom;
};