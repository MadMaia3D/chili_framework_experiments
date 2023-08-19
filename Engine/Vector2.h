#pragma once
#include <cmath>

template <typename T>
class Vector2 {
public:
	Vector2() = default;

	Vector2(T x, T y)
		:
		x(x),
		y(y)
	{}
	Vector2(const Vector2<float>& source) 
	:
		x(T(source.x)),
		y(T(source.y))
	{}

	Vector2 operator+(const Vector2& other) {
		return{ x + other.x, y + other.y };
	}
	Vector2& operator+=(const Vector2& other) {
		return *this + other;
	}
	Vector2 operator-(const Vector2& other) {
		return{ x - other.x, y - other.y };
	}
	Vector2& operator-=(const Vector2& other) {
		return *this - other;
	}
	Vector2 operator*(T value) {
		return{ x * value, y * value };
	}
	Vector2& operator*=(T value) {
		return *this * value;
	}
	Vector2 operator/(T value) {
		return{ x / value, y / value };
	}
	Vector2& operator/=(T value) {
		return *this / value;
	}

	float GetDistanceSquared(Vector2 position) {
		const float deltaX = float(x) - position.x;
		const float deltaY = float(y) - position.y;
		return deltaX * deltaX + deltaY * deltaY;
	}

	float GetLengthSquared() {
		return x * x + y * y;
	}

	float GetLength() {
		std::sqrt(GetLengthSquared());
	}

	Vector2 Rotated(float angle) {
		const float sinTheta = std::sin(angle);
		const float cosTheta = std::cos(angle);
		const T resultX = T(x * cosTheta - y * sinTheta);
		const T resultY = T(x * sinTheta + y * cosTheta);
		return{ resultX, resultY };
	}
	void Rotate(float angle) {
		*this = this->Rotated(angle);
	}
public:
	T x = 0;
	T y = 0;
};