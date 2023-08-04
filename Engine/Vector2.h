#pragma once

class Vector2 {
public:
	Vector2() = default;
	Vector2(int x, int y);
	int GetDistanceSquared(Vector2 position);
public:
	int x = 0;
	int y = 0;
};