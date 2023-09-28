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
	Vector2(const Vector2<int>& source)
		:
		x(T(source.x)),
		y(T(source.y)) {
	}
	// COMPARISON OPERATORS
	bool operator==(const Vector2& other) const 
	{
		return (x == other.x && y == other.y);
	}
	bool operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}
	// ARITHMETIC OPERATORS
	Vector2 operator+(const Vector2& other) const
	{
		return{ x + other.x, y + other.y };
	}
	Vector2& operator+=(const Vector2& other) {
		*this = *this + other;
		return *this;
	}
	Vector2 operator-(const Vector2& other) const {
		return{ x - other.x, y - other.y };
	}

	Vector2& operator-=(const Vector2& other) {
		*this = *this - other;
		return *this;
	}
	Vector2 operator*(T value) const
	{
		return{ x * value, y * value };
	}
	Vector2& operator*=(T value) {
		*this = *this * value;
		return *this;
	}
	Vector2 operator/(T value) const
	{
		return{ x / value, y / value };
	}
	Vector2& operator/=(T value) {
		*this = *this / value;
		return *this;
	}

	// MEMBER FUNCTIONS
	float GetDistanceSquared(Vector2 position) {
		const float deltaX = float(x) - position.x;
		const float deltaY = float(y) - position.y;
		return deltaX * deltaX + deltaY * deltaY;
	}

	float GetLengthSquared() const
	{
		return float(x * x + y * y);
	}

	float GetLength() const
	{
		return std::sqrt(GetLengthSquared());
	}

	void SetLength(T value) {
		Normalize();
		*this *= value;
	}

	Vector2 GetNormalized() const
	{
		const float length = GetLength();
		if (length != (T)0) {
			return *this / (T)length;
		}
		return *this;
	}

	Vector2& Normalize() {
		return *this = GetNormalized();
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

template <typename T>
Vector2<T> operator*(float value, const Vector2<T>& vec)
{
	return{ vec.x * value, vec.y * value };
}

typedef Vector2<int> Vei2;
typedef Vector2<float> Vec2;