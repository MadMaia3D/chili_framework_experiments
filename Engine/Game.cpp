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
	CreateGaussianDistribution();
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
	constexpr int barWidth = 1;
	constexpr int xPos = 10;
	constexpr int yPos = 590;
	for (int i = 0; i < maxValues; i++) {
		for (int y = 0; y < values[i]; y++) {
			for (int x = 0; x < barWidth; x++) {
				gfx.PutPixel(xPos + i * barWidth + x, yPos - y, Colors::White);
			}
		}
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		CreateGaussianDistribution();
	}
}

void Game::CreateGaussianDistribution() {
	for (int& i : values) {
		i = 0;
	}
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> distribution(0, maxValues - 1);
	for (int i = 0; i < 10000; i++) {
		int nRandomGenerators = 3;

		int accumulatedRandom = 0;
		for (int i = 0; i < nRandomGenerators; i++) {
			accumulatedRandom += distribution(rng);
		}
		int randomIndex = accumulatedRandom/ nRandomGenerators;

		values[randomIndex] += 5;
	}
}

void Game::ComposeFrame()
{
}
