#pragma once
#include "Graphics.h"
#include "Vector2.h"

class Particle {
public:
	Particle(Vector2<float> position, Vector2<float> velocity = { 0.0f,0.0f }, Vector2<float> acceleration = { 0.0f,0.0f })
		:
		position(position),
		velocity(velocity),
		acceleration(acceleration) {
	}
	void Accelerate(Vector2<float> force) {
		velocity += force;
	}
	void ApplyForce(Vector2<float> force)
	{
		Accelerate(force);
	}
	void Update(float deltaTime) {
		velocity += acceleration * deltaTime;
		position += velocity * deltaTime;
	}
	void SetColor(const Color& c) {
		color = c;
	}
	void Draw(int radius, Graphics& gfx) const {
		gfx.DrawCircle(position, radius, color);
	}
protected:
	Vector2<float> GetPosition() const {
		return position;
	}
private:
	Color color = Colors::White;
	Vector2<float> position;
	Vector2<float> velocity;
	Vector2<float> acceleration;
};