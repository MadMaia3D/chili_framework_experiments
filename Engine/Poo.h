#pragma once
#include "Graphics.h"
#include <string>

class Poo {
public:
	Poo(const Vec2& position, const Vec2& velocity, float speed, const Surface& surface)
		:
		sprite(surface),
		position(position),
		velocity(velocity),
		speed(speed)
	{
		width = sprite.GetWidth();
		height = sprite.GetHeight();
	}

	void Update(float deltaTime)
	{
		position += velocity * speed * deltaTime;
		BounceOffScreen();
	}

	void BounceOffScreen()
	{
		if (position.x < 0.0f) {
			position.x = 0.0f;
			velocity.x *= -1;
		}
		else if (position.x > Graphics::ScreenWidth - width) {
			position.x = float(Graphics::ScreenWidth - width);
			velocity.x *= -1;
		}
		if (position.y < 0.0f) {
			position.y = 0.0f;
			velocity.y *= -1;
		}
		else if (position.y > Graphics::ScreenHeight - height) {
			position.y = float(Graphics::ScreenHeight - height);
			velocity.y *= -1;
		}
	}

	void Draw(Graphics& gfx) const
	{
		gfx.DrawSprite(int(position.x), int(position.y), sprite, Colors::White);
	}

	const RectI GetRect() const
	{
		return{ position, width, height };
	}

private:
	const Surface& sprite;
	Vec2 position;
	Vec2 velocity;
	float speed;
	int width;
	int height;

};