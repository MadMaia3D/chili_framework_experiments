#pragma once
#include "Graphics.h"
#include <vector>
#include "MathUtilities.h"

class PolyLineEntity {
public:
	PolyLineEntity() = default;
	PolyLineEntity(const Vector2<float>& position, const std::vector<Vector2<float>>& points);
	void Move(const Vector2<float>& offset);
	const Vector2<float>& GetPosition() const;
	void Rotate(float degrees);
	void SetScale(const Vector2<float>& newScale);
	void SetScale(float newScale);
	void SetColor(Color c);
	void LookAt(const Vector2<float>& targetPosition);
	void Draw(Graphics& gfx) const;
private:
	const std::vector<Vector2<float>> GetTransformatedModel() const;
private:
	std::vector<Vector2<float>> points;
	Vector2<float> position{ 0.0f ,0.0f };
	float rotation = 0.0f;
	Vector2<float> scale{ 1.0f, 1.0f};
	Color color = Colors::White;
};