#pragma once

#include "Graphics.h"
#include <vector>
#include "MathUtilities.h"
#include <random>
#include <assert.h>
class DoomFire {
public:
	DoomFire()
		:
		fireCells(FIRE_WIDTH * FIRE_HEIGHT, 0),
		rng(std::random_device{}()),
		decayDist(0, 1),
		windDist(0, 1) {
		constexpr int nInterpolationColors = 8;
		PreparePalette(nInterpolationColors);
		SetupInitialFire();
	}

	void Update() {
		for (int y = 1; y < FIRE_HEIGHT; y++) {
			for (int x = 0; x < FIRE_WIDTH; x++) {
				SpreadFire(y * FIRE_WIDTH + x);
			}
		}
	}

	void Draw(Graphics& gfx) const {
		for (int y = 0; y < FIRE_HEIGHT; y++) {
			for (int x = 0; x < FIRE_WIDTH; x++) {
				DrawCellAtPosition({ x,y }, gfx);
			}
		}
	}
private:
	void SpreadFire(int from) {
		const int rand = decayDist(rng);
		const int wind = windDist(rng);
		const int to = std::max(0, from - FIRE_WIDTH + wind);
		fireCells[to] = std::max(0, fireCells[from] - rand);
	}

	void DrawCellAtPosition(Vector2<int> cellPosition, Graphics& gfx) const {
		const int xPos = cellPosition.x * cellWidth + firePosition.x;
		const int yPos = cellPosition.y * cellHeight + firePosition.y;
		const int fireIntensity = fireCells[cellPosition.y * FIRE_WIDTH + cellPosition.x];
		const Color c = fireColors[fireIntensity];
		gfx.DrawRect(xPos, yPos, cellWidth, cellHeight, c);
	}

	void SetupInitialFire() {
		for (int x = 0; x < FIRE_WIDTH; x++) {
			constexpr int y = FIRE_HEIGHT - 1;
			const int intensity = (int)fireColors.size() - 1;
			fireCells[y * FIRE_WIDTH + x] = intensity;
		}
	}

	void PreparePalette(int nInterpolationColors) {
		const Color darkRed(113, 18, 0);
		const Color brightOrange(232, 66, 0);
		const Color yellowOrange(217, 130, 0);
		const Color yellow(196, 169, 0);
		InterpolateColors(Colors::Black, darkRed, nInterpolationColors);
		InterpolateColors(darkRed, brightOrange, nInterpolationColors);
		InterpolateColors(brightOrange, yellowOrange, nInterpolationColors);
		InterpolateColors(yellowOrange, yellow, nInterpolationColors);
		InterpolateColors(yellow, Colors::White, nInterpolationColors);
		fireColors.emplace_back(Colors::White);
		fireColors.shrink_to_fit();
	}

	void InterpolateColors(const Color& a, const Color& b, int nInterpolations) {
		nInterpolations++;
		const float step = 1.0f / nInterpolations;
		for (float t = 0.0f; t < 1.0f; t += step) {
			const Color c = MathUtilities::LerpColor(a, b, t);
			fireColors.emplace_back(c);
		}
	}

private:
	Vector2<int> firePosition{ 100,200 };
	static constexpr int FIRE_WIDTH = 300;
	static constexpr int FIRE_HEIGHT = 120;
	static constexpr int cellWidth = 2;
	static constexpr int cellHeight = 2;
	std::vector<Color> fireColors;
	std::vector<int> fireCells;
	std::mt19937 rng;
	std::uniform_int_distribution<int> decayDist;
	std::uniform_int_distribution<int> windDist;
};