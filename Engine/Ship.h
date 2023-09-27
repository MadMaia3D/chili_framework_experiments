#pragma once
#include "PolyLineEntity.h"

class Ship : public PolyLineEntity {
public:
	Ship(const Vector2<float>& position);
	void ApplyThrust(float intensity);
	void Update(float deltaTime);
	void Draw(Graphics& gfx) const;
private:
	Vec2 velocity = { 0.0f, 0.0f };
	std::vector<Vector2<float>> thrustLine = { { -2 , 12 },{ 0 , 35 },{ 2, 12 } };
	mutable bool isThrusting = false;
};