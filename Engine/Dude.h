#pragma once
#include "Graphics.h"
#include "Keyboard.h"

class Dude {
public:
	Dude(Vec2 position)
		:
		sprite(".\\images\\dude.bmp"),
		width(sprite.GetWidth()),
		height(sprite.GetHeight()),
		position(position)
	{
	}

	void ProcessInput(const Keyboard& kbd, float deltaTime)
	{
		Vec2 deltaPosition;
		if (kbd.KeyIsPressed('A')) {
			deltaPosition.x -= 1;
		}
		if (kbd.KeyIsPressed('D')) {
			deltaPosition.x += 1;
		}
		if (kbd.KeyIsPressed('W')) {
			deltaPosition.y -= 1;
		}
		if (kbd.KeyIsPressed('S')) {
			deltaPosition.y += 1;
		}

		deltaPosition.Normalize();

		position += deltaPosition * speed * deltaTime;
		LimitToBounds();
	}

	void LimitToBounds()
	{
		if (position.x < 0) {
			position.x = 0;
		}
		else if (position.x + width >= Graphics::ScreenWidth) {
			position.x = float(Graphics::ScreenWidth - width - 1);
		}
		if (position.y < 0) {
			position.y = 0;
		}
		else if (position.y + height >= Graphics::ScreenHeight) {
			position.y = float(Graphics::ScreenHeight - height - 1);
		}
	}

	void Draw(Graphics& gfx) const
	{
		gfx.DrawSprite(int(position.x), int(position.y), sprite, Colors::Magenta);
	}

	Vec2 GetPosition() const
	{
		return position;
	}

	const RectI GetRect() const
	{
		return{ position, width, height };
	}

private:
	Surface sprite;
	int width;
	int height;
	Vec2 position;
	static constexpr float speed = 150.0f;
};