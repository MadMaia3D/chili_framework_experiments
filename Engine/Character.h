#pragma once
#include "Graphics.h"
#include "Animation.h"
#include "Keyboard.h"
#include <vector>

class Character {
private:
	enum class State {
		walkingLeft,
		walkingRight,
		walkingUp,
		walkingDown,
		standingLeft,
		standingRight,
		standingUp,
		standingDown,
		count
	};
public:
	Character(Vei2 position);
	void ProcessInput(const Keyboard& keyboard);
	void Update(float deltaTime);
	void Draw(Graphics& gfx) const;
private:
	const Surface image;
	const SpriteSheet spriteSheet;
	std::vector<Animation> animations;
	State currentAnimation = State::standingDown;
	Vec2 position;
	Vec2 direction;
	static constexpr float frameDuration = 0.15f;
	static constexpr float speed = 140.0f;
};