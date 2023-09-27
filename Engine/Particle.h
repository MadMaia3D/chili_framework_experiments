#pragma once
#include "Graphics.h"
#include <cmath>

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

class ParticleBody : public Particle {
public:
	ParticleBody(Vector2<float> position, float mass, Vector2<float> velocity = { 0.0f,0.0f }, Vector2<float> acceleration = { 0.0f,0.0f })
		:
		Particle(position, velocity, acceleration),
		mass(mass)
	{}
	void GravitateTo (const ParticleBody& body, float deltaTime) {
		const Vector2<float> deltaPosition = body.GetPosition() - GetPosition();
		const Vector2<float> direction = deltaPosition.GetNormalized();

		const float distanceSquared = GetPosition().GetDistanceSquared(body.GetPosition());
		const float forceMagnitude = body.mass / distanceSquared;

		const Vector2<float> gravity = forceMagnitude * direction * GRAVITATIONAL_CONSTANT;

		ApplyForce(gravity * deltaTime);
	}
private:
	float mass;
	static constexpr float GRAVITATIONAL_CONSTANT = 1000.0f;
};