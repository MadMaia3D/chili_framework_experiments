#include "Character.h"

Character::Character(Vei2 position)
	:
	image(".\\images\\link90x90.bmp"),
	spriteSheet(5, 4, image),
	position(position)
{
	for (int v = 0; v < int(State::standingLeft); v++) {
		animations.emplace_back(1, v, 4, frameDuration, spriteSheet);
	}
	for (int v = 0; v < int(State::count) - int(State::standingLeft); v++) {
		animations.emplace_back(0, v, 1, frameDuration, spriteSheet);
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
		direction = input;

		if (direction.x == -1) {
			currentAnimation = State::walkingLeft;
		}
		else if (direction.x == 1) {
			currentAnimation = State::walkingRight;
		}
		else if (direction.y == -1) {
			currentAnimation = State::walkingUp;
		}
		else if (direction.y == 1) {
			currentAnimation = State::walkingDown;
		}
	}
	else {
		if (direction.x == -1) {
			currentAnimation = State::standingLeft;
		}
		else if (direction.x == 1) {
			currentAnimation = State::standingRight;
		}
		else if (direction.y == -1) {
			currentAnimation = State::standingUp;
		}
		else if (direction.y == 1) {
			currentAnimation = State::standingDown;
		}
		direction = {0,0};
	}
}

void Character::Update(float deltaTime)
{
	position += Vec2(direction.GetNormalized()) * speed * deltaTime;
	animations[int(currentAnimation)].Update(deltaTime);
}

void Character::Draw(Graphics& gfx) const
{
	animations[int(currentAnimation)].Draw(Vei2(position), gfx);
}