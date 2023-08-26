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
		cells(nColumns * nRows, 0),
		rng(std::random_device{}()),
		decayDist(0,1),
		windDist(-1,1)
	{
		constexpr int nInterpolationColors = 8;
		PreparePalette(nInterpolationColors);
		SetupInitialFire();
	}

	void Update() {
		for (int y = 0; y < nRows - 1; y++) {
			for (int x = 0; x < nColumns; x++) {
				const int randomDecay = decayDist(rng);
				//const int randomWind = windDist(rng);

				const int intensity = GetIntensityFromLineBellow({ x,y }, 1, randomDecay);
				SetIntensityAtPosition({ x,y }, intensity);
			}
		}
	}

	void Draw(Graphics& gfx) const {
		for (int y = 0; y < nRows; y++) {
			for (int x = 0; x < nColumns; x++) {
				DrawCellAtPosition({ x,y }, gfx);
			}
		}
	}
private:
	int GetIntensityFromLineBellow(const Vector2<int> currentPos, int wind, int decay) {
		assert(decay >= 0);
		int sourceX = currentPos.x - wind;

		if (sourceX < 0) {
			sourceX += nColumns;
		} else if (sourceX >= nColumns) {
			sourceX -= nColumns;
		}

		const Vector2<int> sourcePosition(sourceX, currentPos.y + 1);
		const int intensityBellow = GetIntensityAtPosition(sourcePosition);
		const int intensity = std::max(0, intensityBellow - decay);
		return intensity;
	}


	void DrawCellAtPosition(Vector2<int> cellPosition, Graphics& gfx) const {
		const int xPos = cellPosition.x * cellWidth + firePosition.x;
		const int yPos = cellPosition.y * cellHeight + firePosition.y;
		const int fireIntensity = GetIntensityAtPosition(cellPosition);
		const Color c = fireColors[fireIntensity];
		gfx.DrawRect(xPos, yPos, cellWidth, cellHeight, c);
	}

	int GetIntensityAtPosition(Vector2<int> position) const {
		return cells[position.y * nColumns + position.x];
	}

	void SetIntensityAtPosition(Vector2<int> position, int intensity) {
		cells[position.y * nColumns + position.x] = intensity;
	}

	void SetupInitialFire() {
		for (int x = 0; x < nColumns; x++) {
			constexpr int y = nRows - 1;
			const int intensity = (int)fireColors.size() - 1;
			SetIntensityAtPosition({ x, y }, intensity);
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
	Vector2<int> firePosition{ 50,100 };
	static constexpr int nColumns = 200;
	static constexpr int nRows = 120;
	static constexpr int cellWidth = 3;
	static constexpr int cellHeight = 3;
	std::vector<Color> fireColors;
	std::vector<int> cells;
	std::mt19937 rng;
	std::uniform_int_distribution<int> decayDist;
	std::uniform_int_distribution<int> windDist;
};