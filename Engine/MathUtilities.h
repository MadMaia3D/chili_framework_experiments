#pragma once
#include "Colors.h"
#include "Vector2.h"

class MathUtilities {
public:
	static constexpr float PI = 3.1415f;


	/*static int LerpInt (const int a, const int b, const float t) {
		return int(a * (1 - t) + b * (t));
	}*/

	template <typename T>
	static T LerpNumber(const T a, const T b, const float t)
	{
		return T(a * (T(1) - t) + b * (t));
	}

	static Color LerpColor(const Color& a, const Color& b, const float t) {
		const int red = LerpNumber<int>(a.GetR(), b.GetR(), t);
		const int green = LerpNumber<int>(a.GetG(), b.GetG(), t);
		const int blue = LerpNumber<int>(a.GetB(), b.GetB(), t);
		return Color(red, green, blue);
	}

	template <typename T>
	static Vector2<T> LerpVector2(const Vector2<T>& p1, const Vector2<T>& p2, const float t) {
		const T result_x = LerpNumber<float>(p1.x, p2.x, t);
		const T result_y = LerpNumber<float>(p1.y, p2.y, t);
		return { result_x , result_y};
	}

	static float DegreesToRadians(float degree) {
		return PI / 180.0f * degree;
	}

	static float RadiansToDegrees(float radians) {
		return 180.0f / PI * radians;
	}
};