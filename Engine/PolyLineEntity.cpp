#include "PolyLineEntity.h"

PolyLineEntity::PolyLineEntity(const Vector2<float>& position, const std::vector<Vector2<float>>& points)
	:
	position(position),
	points(points) {
}

void PolyLineEntity::Move(const Vector2<float>& offset) {
	position += offset;
}

const Vector2<float>& PolyLineEntity::GetPosition() const {
	return position;
}

void PolyLineEntity::Rotate(float degrees) {
	rotation += degrees;
}

void PolyLineEntity::SetScale(const Vector2<float>& newScale) {
	scale = newScale;
}

void PolyLineEntity::SetScale(float newScale) {
	scale.x = newScale;
	scale.y = newScale;
}

void PolyLineEntity::SetColor(Color c) {
	color = c;
}

void PolyLineEntity::LookAt(const Vector2<float>& targetPosition) {
	auto deltaPosition = targetPosition - position;
	if (deltaPosition.x == 0.0f || deltaPosition.y == 0.0f) {
		return;
	}
	float rotationInRadians = std::atan2(deltaPosition.y, deltaPosition.x);
	rotation = MathUtilities::RadiansToDegrees(rotationInRadians);
}

void PolyLineEntity::Draw(Graphics & gfx) const {
	const auto pointsSize = points.size();
	if (pointsSize == 0) {
		return;
	}

	auto pointsCopy = GetTransformatedModel();
	for (int i = 0; i < pointsSize - 1; i++) {
		gfx.DrawLine(pointsCopy[i], pointsCopy[i + 1], color);
	}

	gfx.DrawLine(pointsCopy.front(), pointsCopy.back(), color);

	if (pointsSize == 1) {
		gfx.DrawCircle(pointsCopy.front(), 3, color);
	}
}

const std::vector<Vector2<float>> PolyLineEntity::GetTransformatedModel() const {
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
