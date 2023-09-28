#pragma once
#include "Graphics.h"
#include <cmath>

class Particle {
public:
	Particle(Vec2 position,
		Vec2 velocity = { 0.0f,0.0f },
		Vec2 acceleration = { 0.0f,0.0f },
		float friction = 0.0f)
		:
		position(position),
		velocity(velocity),
		acceleration(acceleration),
		friction (friction)
	{}
	void Accelerate(Vec2 force) {
		velocity += force;
	}
	void ApplyForce(Vec2 force)
	{
		Accelerate(force);
	}
	void Update(float deltaTime) {
		velocity += acceleration * deltaTime;

		Vec2 frictionForce = velocity.GetNormalized() * -friction;
		velocity += frictionForce * deltaTime;

		if (velocity.GetLengthSquared() < 10.0f) {
			velocity = { 0,0 };
		}
		position += velocity * deltaTime;
	}
	Vec2 GetPosition() const
	{
		return position;
	}
	bool IsMoving() const
	{
		return velocity.GetLengthSquared() > 10.0f;
	}
	void SetColor(const Color& c) {
		color = c;
	}
	void Draw(Graphics& gfx, int radius = 5) const {
		gfx.DrawCircle(position, radius, color);
	}
private:
	Color color = Colors::White;
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
	float friction;
};

class ParticleBody : public Particle {
public:
	ParticleBody(Vec2 position, float mass, Vec2 velocity = { 0.0f,0.0f }, Vec2 acceleration = { 0.0f,0.0f })
		:
		Particle(position, velocity, acceleration),
		mass(mass)
	{}
	void GravitateTo (const ParticleBody& body, float deltaTime) {
		const Vec2 deltaPosition = body.GetPosition() - GetPosition();
		const Vec2 direction = deltaPosition.GetNormalized();

		const float distanceSquared = GetPosition().GetDistanceSquared(body.GetPosition());
		const float forceMagnitude = body.mass / distanceSquared;

		const Vec2 gravity = forceMagnitude * direction * GRAVITATIONAL_CONSTANT;

		ApplyForce(gravity * deltaTime);
	}
private:
	float mass;
	static constexpr float GRAVITATIONAL_CONSTANT = 1000.0f;
};