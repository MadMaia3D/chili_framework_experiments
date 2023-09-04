/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <random>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	dude({ Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2 }),
	pooSprite(".\\images\\poo.bmp"),
	menuSprite(".\\images\\dapoopoo.bmp"),
	gameOverSprite(".\\images\\game_over.bmp")
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> xDist(0.0f, float(Graphics::ScreenWidth - pooSprite.GetWidth()));
	std::uniform_real_distribution<float> yDist(0.0f, float(Graphics::ScreenHeight - pooSprite.GetHeight()));
	std::uniform_real_distribution<float> velocityDist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> speedDist(100.0f, 200.0f);

	constexpr float minDistance = 150.0f;
	constexpr float minDistanceSquared = minDistance * minDistance;
	Vec2 dudePosition = dude.GetPosition();
	for (int i = 0; i < 10; i++) {
		Vec2 position;
		do {
			position = Vec2(xDist(rng), yDist(rng));
		} while (dudePosition.GetDistanceSquared(position) < minDistanceSquared);

		const Vec2 velocity(velocityDist(rng), velocityDist(rng));
		const float speed = speedDist(rng);
		poos.emplace_back(position, velocity.GetNormalized(), speed, pooSprite);
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = frameTimer.Mark();
	switch (gameState) {
	case Game::MENU:
		if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
			gameState = GameState::PLAYING;
		}
		break;
	case Game::PLAYING:
	{
		dude.ProcessInput(wnd.kbd, dt);

		const RectI dudeRect = dude.GetRect();
		for (Poo& poo : poos) {
			poo.Update(dt);
			if (poo.GetRect().IsColliding(dudeRect)) {
				gameState = GameState::GAMEOVER;
			}
		}
	}
	break;
	case Game::GAMEOVER:
		break;
	default:
		break;
	}


}

void Game::ComposeFrame()
{
	if (gameState == GameState::MENU) {
		const int centerX = Graphics::ScreenWidth / 2 - menuSprite.GetWidth() / 2;
		const int centerY = Graphics::ScreenHeight / 2 - menuSprite.GetHeight() / 2;
		gfx.DrawSprite(centerX, centerY, menuSprite, Colors::Black);
		return;
	}


	for (const Poo& poo : poos) {
		poo.Draw(gfx);
	}

	dude.Draw(gfx);

	if (gameState == GameState::GAMEOVER) {
		const int centerX = Graphics::ScreenWidth / 2 - gameOverSprite.GetWidth() / 2;
		const int centerY = Graphics::ScreenHeight / 2 - gameOverSprite.GetHeight() / 2;
		gfx.DrawSprite(centerX, centerY, gameOverSprite, Colors::Black);
	}
}
