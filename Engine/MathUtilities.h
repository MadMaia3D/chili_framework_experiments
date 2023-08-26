#pragma once
#include "Colors.h"

class MathUtilities {
public:
	static constexpr float PI = 3.1415f;

	static int LerpInt (const int a, const int b, const float t) {
		return int(a * (1 - t) + b * (t));
	}

	static Color LerpColor(const Color& a, const Color& b, const float t) {
		const int red = LerpInt(a.GetR(), b.GetR(), t);
		const int green = LerpInt(a.GetG(), b.GetG(), t);
		const int blue = LerpInt(a.GetB(), b.GetB(), t);
		return Color(red, green, blue);
	}

	static float DegreesToRadians(float degree) {
		return PI / 180.0f * degree;
	}

	static float RadiansToDegrees(float radians) {
		return 180.0f / PI * radians;
	}
};