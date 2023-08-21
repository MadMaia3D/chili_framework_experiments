#pragma once

class MathUtilities {
public:
	static constexpr float PI = 3.1415f;

	static int LerpInt (const int a, const int b, const float t) {
		return int(a * (1 - t) + b * (t));
	}

	static float DegreesToRadians(float degree) {
		return PI / 180.0f * degree;
	}

	static float RadiansToDegrees(float radians) {
		return 180.0f / PI * radians;
	}
};