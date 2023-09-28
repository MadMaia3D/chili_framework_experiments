#pragma once
#include "Particle.h"

class Spring {
public:
	Spring(Vec2 pivotPoint, Particle& weight, float k_constant = 10.0f, float length = 0.0f)
	:
		pivotPointPosition(pivotPoint),
		weight(weight),
		K(k_constant),
		length(length)
	{}
	void Update(float deltaTime) const
	{
		Vec2 distance = pivotPointPosition - weight.GetPosition();
		if (length > 1.0f) {
			distance.SetLength(distance.GetLength() - length);
		}
		weight.ApplyForce(distance * K * deltaTime);
		weight.Update(deltaTime);
	}
	void SetPivotPosition(Vec2 position)
	{
		pivotPointPosition = position;
	}
	void SetLength(float value)
	{
		length = value;
	}
	void Draw(Graphics& gfx) const
	{
		gfx.DrawLine(pivotPointPosition, weight.GetPosition(), Colors::Gray);
		weight.Draw(gfx, 10);
		gfx.DrawCircle(pivotPointPosition, 2, Colors::White);
	}
private:
	Vec2 pivotPointPosition;
	Particle& weight;
	float length;
	float K;
};