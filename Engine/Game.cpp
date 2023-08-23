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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> xDist(0.0f, 800.0f);
	std::uniform_real_distribution<float> yDist(0.0f, 600.0f);
	
	std::vector<Vector2<float>> arrowModel = { { -15.0f,0.0f },{ 10.0f ,0.0f },{ 10.0f, 5.0f }, {20.0f, 0.0f},{ 10.0f, -5.0f },{ 10.0f ,0.0f } };
	std::vector<Vector2<float>> simpleArrowModel = { { -5.0f, 0.0f },{ -10.0f, 6.0f },{ 10.0f, 0.0f },{ -10.0f, -6.0f } };
	std::vector<Vector2<float>> lineModel = { { -5.0f, 0.0f },{ 5.0f, 0.0f } };

	for (int i = 0; i < 1000; i++) {
		Vector2<float> position(xDist(rng), yDist(rng));

		PolyLineEntity entity(position, simpleArrowModel);

		unsigned char r = int(entity.GetPosition().x / 800 * 255);
		unsigned char g = int(entity.GetPosition().y / 600 * 255);
		unsigned char b = 255;

		entity.SetColor({r,g,b});
		entity.SetScale({1.0f,0.5f});

		entities.emplace_back(entity);
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
	const float deltaTime = frameTimer.Mark();
	const auto mousePos = wnd.mouse.GetPos();
	for (auto &entity : entities) {
		entity.LookAt(mousePos);
	}
}

void Game::ComposeFrame()
{
	for (auto &entity : entities) {
		entity.Draw(gfx);
	}
}
