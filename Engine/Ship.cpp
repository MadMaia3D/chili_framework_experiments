#include "Ship.h"

Ship::Ship(const Vector2<float>& position)
	:
	PolyLineEntity(position, { { 0,-20 },{ 10,15 },{ 0, 10 } ,{ -10,15 } })
{
}
void Ship::ApplyThrust(float intensity)
{
	Vec2 force(0.0f, -intensity);
	float radians = MathUtilities::DegreesToRadians(GetRotation());
	force.Rotate(radians);
	velocity += force;
	isThrusting = true;
}

void Ship::Update(float deltaTime)
{
	Move(velocity * deltaTime);
}

void Ship::Draw(Graphics & gfx) const
{
	PolyLineEntity::Draw(gfx);
	if (isThrusting) {
		auto transformedThrustLine = GetTransformedModel(thrustLine);
		gfx.DrawPolyLine(transformedThrustLine, GetColor());
		isThrusting = false;
	}
}
