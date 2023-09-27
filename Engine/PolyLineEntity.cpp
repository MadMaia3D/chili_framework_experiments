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

float PolyLineEntity::GetRotation() const
{
	return rotation;
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

Color PolyLineEntity::GetColor() const
{
	return color;
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

	auto pointsCopy = GetTransformedModel(points);

	gfx.DrawPolyLineClosed(pointsCopy, color);
	if (pointsSize == 1) {
		gfx.DrawCircle(pointsCopy.front(), 3, color);
	}
}

const std::vector<Vector2<float>> PolyLineEntity::GetTransformedModel(const std::vector<Vector2<float>>& model) const {
	auto pointsCopy = model;
	const float rotationInRadians = MathUtilities::DegreesToRadians(rotation);

	for (auto &point : pointsCopy) {
		point.x *= scale.x;
		point.y *= scale.y;
		point.Rotate(rotationInRadians);
		point += position;
	}
	return pointsCopy;
}
