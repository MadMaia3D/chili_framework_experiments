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
	void Update(float deltaTime) {
		velocity += acceleration * deltaTime;
		position += velocity * deltaTime;
	}
	void SetColor(const Color& c) {
		color = c;
	}
	void Draw(Graphics& gfx) const {
		gfx.DrawCircle(position, 3, color);
	}
private:
	Color color = Colors::White;
	Vector2<float> position;
	Vector2<float> velocity;
	Vector2<float> acceleration;
};