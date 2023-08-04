#include "Vector2.h"

Vector2::Vector2(int x, int y) {
	(*this).x = x;
	(*this).y = y;
}

int Vector2::GetDistanceSquared(Vector2 position) {
	const int deltaX = x - position.x;
	const int deltaY = y - position.y;
	return deltaX * deltaX + deltaY * deltaY;
}
