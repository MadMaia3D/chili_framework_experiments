#pragma once
#include "Graphics.h"
#include <vector>
#include "MathUtilities.h"

class PolyLineEntity {
public:
	PolyLineEntity() = default;
	PolyLineEntity(const Vector2<float>& position, const std::vector<Vector2<float>>& points)
		:
		position(position),
		points(points)
	{}

	void Move(const Vector2<float>& offset) {
		position += offset;
	}

	const Vector2<float>& GetPosition() const {
		return position;
	}

	void Rotate(float degrees) {
		rotation += degrees;
	}

	void SetScale(const Vector2<float>& newScale) {
		scale = newScale;
	}
	void SetScale(float newScale) {
		scale.x = newScale;
		scale.y = newScale;
	}

	void SetColor(Color c) {
		color = c;
	}

	void LookAt(const Vector2<float>& targetPosition) {
		auto deltaPosition = targetPosition - position;
		if (deltaPosition.x == 0.0f || deltaPosition.y == 0.0f) {
			return;
		}
		float rotationInRadians = std::atan2(deltaPosition.y , deltaPosition.x);
		rotation = MathUtilities::RadiansToDegrees(rotationInRadians);
	}

	void Draw(Graphics& gfx) const {
		const auto pointsSize = points.size();
		if (pointsSize == 0) {
			return;
		}
		
		auto pointsCopy = GetTransformatedModel();
		for (int i = 0; i < pointsSize - 1 ; i++) {
			gfx.DrawLine(pointsCopy[i], pointsCopy[i + 1], color);
		}

		gfx.DrawLine(pointsCopy.front(), pointsCopy.back(), color);

		if (pointsSize == 1) {
			gfx.DrawCircle(pointsCopy.front(), 3, color);
		}
	}
private:
	const std::vector<Vector2<float>> GetTransformatedModel() const {
		auto pointsCopy = points;
		const float rotationInRadians = MathUtilities::DegreesToRadians(rotation);

		for (auto &point : pointsCopy) {
			point.x *= scale.x;
			point.y *= scale.y;
			point.Rotate(rotationInRadians);
			point += position;
		}
		return pointsCopy;
	}
private:
	std::vector<Vector2<float>> points;
	Vector2<float> position{ 0.0f ,0.0f };
	float rotation = 0.0f;
	Vector2<float> scale{ 1.0f, 1.0f};
	Color color = Colors::White;
};