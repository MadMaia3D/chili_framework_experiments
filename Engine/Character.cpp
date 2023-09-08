#include "Character.h"

Character::Character(Vei2 position)
	:
	image(".\\images\\link90x90.bmp"),
	spriteSheet(5, 4, image),
	position(position)
{
	for (int row = 0; row < int(State::standingLeft); row++) {
		animations.emplace_back(1, row, 4, frameDuration, spriteSheet);
	}
	for (int row = 0; row < int(State::count) - int(State::standingLeft); row++) {
		animations.emplace_back(0, row, 1, frameDuration, spriteSheet);
	}
}

void Character::ProcessInput(const Keyboard& keyboard)
{
	Vei2 input(0, 0);
	if (keyboard.KeyIsPressed('W')) {
		input.y = -1;
	}
	if (keyboard.KeyIsPressed('S')) {
		input.y = 1;
	}
	if (keyboard.KeyIsPressed('A')) {
		input.x = -1;
	}
	if (keyboard.KeyIsPressed('D')) {
		input.x = 1;
	}

	if (input != Vei2(0, 0)) {
		lastInput = input;

		if (input.x == -1) {
			currentAnimation = State::walkingLeft;
		}
		else if (input.x == 1) {
			currentAnimation = State::walkingRight;
		}
		else if (input.y == -1) {
			currentAnimation = State::walkingUp;
		}
		else if (input.y == 1) {
			currentAnimation = State::walkingDown;
		}
	}
	else {
		if (lastInput.x == -1) {
			currentAnimation = State::standingLeft;
		}
		else if (lastInput.x == 1) {
			currentAnimation = State::standingRight;
		}
		else if (lastInput.y == -1) {
			currentAnimation = State::standingUp;
		}
		else if (lastInput.y == 1) {
			currentAnimation = State::standingDown;
		}
		lastInput = {0,0};
	}
}

void Character::Update(float deltaTime)
{
	position += Vec2(lastInput.GetNormalized()) * speed * deltaTime;
	animations[int(currentAnimation)].Update(deltaTime);
}

void Character::Draw(Graphics& gfx) const
{
	animations[int(currentAnimation)].Draw(Vei2(position), gfx);
}

void Character::Draw(float alpha, Graphics& gfx) const
{
	animations[int(currentAnimation)].Draw(Vei2(position), alpha, gfx);
}