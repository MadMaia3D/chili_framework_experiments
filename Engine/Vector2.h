#pragma once

template <typename T>
class Vector2 {
public:
	Vector2() = default;

	Vector2(T x, T y)
		:
		x(x),
		y(y)
	{}
	// ===================== COMPARISSON OPERATORS ==========================
	bool operator==(const Vector2<T>& other) {
		return (x == other.x && y == other.y);
	}

	bool operator!=(const Vector2<T>& other) {
		return !(*this == other);
	}
	// ===================== ARITHMETIC OPERATORS ==========================
	Vector2<T> operator+(const Vector2<T>& other){
		return Vector2<T>(x + other.x, y + other.y);
	}

	Vector2<T>& operator+=(const Vector2<T> other) {
		*this = *this + other;
		return *this;
	}
	
	Vector2<T> operator-(const Vector2<T>& other) {
		return Vector2<T>(x - other.x, y - other.y);
	}

	Vector2<T>& operator-=(const Vector2<T> other) {
		*this = *this - other;
		return *this;
	}

	Vector2<T> operator*(T value) {
		return Vector2<T>(x * value, y * value);
	}

	Vector2<T>& operator*=(T value) {
		*this = *this * value;
		return *this;
	}

	Vector2<T> operator/(T value) {
		if (value == T(0)) {
			return *this;
		}
		return Vector2<T>(x / value, y / value);
	}

	Vector2<T>& operator/=(T value) {
		*this = *this / value;
		return *this;
	}

	// ===================== MEMBER FUNCTIONS ==========================
	T GetLengthSquared() const {
		return x * x + y * y;
	}

	T GetLength() const {
		return std::sqrt(GetLengthSquared());
	}

	Vector2<T> GetNormalized() const {
		T length = GetLength();
		
		if (length == T(0)) {
			return *this;
		}

		T xNormalized = x / length;
		T yNormalized = y / length;

		return Vector2<T>(xNormalized, yNormalized);
	}

	void Normalize() {
		*this = GetNormalized();
	}

public:
	T x = T(0);
	T y = T(0);
};

typedef Vector2<int> Vei2;
typedef Vector2<float> Vec2;