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
	gfx(wnd)
{
	SpawnFireworks();
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
	while (!wnd.kbd.KeyIsEmpty()) {
		const Keyboard::Event event = wnd.kbd.ReadKey();
		if (event.IsPress() && event.GetCode() == VK_SPACE) {
			SpawnFireworks();
		}
	}

	float deltaTime = frameTimer.Mark();

	for (Particle& p : particles) {
		p.Update(deltaTime);
	}
}

void Game::SpawnFireworks() {
	particles.clear();

	constexpr float PI = 3.141592f;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> directionDist(-PI / 10, PI / 10);
	std::uniform_real_distribution<float> speedDist(600.0f, 900.0f);
	std::uniform_int_distribution<int> redDist(200, 255);
	std::uniform_int_distribution<int> greenlDist(128, 200);
	std::uniform_int_distribution<int> blueDist(0, 64);
	constexpr int nParticles = 100;

	for (int i = 0; i < nParticles; i++) {
		float speed = speedDist(rng);
		speed += speedDist(rng);
		speed += speedDist(rng);
		speed /= 3;

		float rotation = directionDist(rng);
		rotation += directionDist(rng);
		rotation += directionDist(rng);
		rotation /= 3;

		unsigned char r = redDist(rng);
		unsigned char g = greenlDist(rng);
		unsigned char b = blueDist(rng);
		Color color = { r, g, b };

		Vector2<float> velocity = { 0.0f, -speed };
		velocity.Rotate(rotation);

		particles.emplace_back(Vector2<float>{ 400.0f, 500.0f }, velocity, Vector2<float>{ 0.0f, 800.0f });
		particles.back().SetColor(color);
	}
}

void Game::ComposeFrame()
{
	for (Particle& p : particles) {
		p.Draw(gfx);
	}
}
