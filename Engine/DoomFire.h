#pragma once

#include "Graphics.h"
#include <vector>
#include "MathUtilities.h"
#include <random>

class DoomFire {
public:
	DoomFire()
		:
		cells(nColumns * nRows, 0),
		rng(std::random_device{}()),
		decayDist(0,1)
	{
		constexpr int nInterpolationColors = 6;
		PreparePalette(nInterpolationColors);
		SetupInitialFire();
	}

	void Update() {
		for (int y = 0; y < nRows - 1; y++) {
			for (int x = 0; x < nColumns; x++) {
				const int intensityBellow = GetIntensityAtPosition({ x,y + 1 });
				const int randomDecay = decayDist(rng);
				const int intensity = std::max(0, intensityBellow - randomDecay);
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
		constexpr int nBaseColors = 5;
		constexpr int nInterpolations = nBaseColors - 1;
		const int totalColors = nBaseColors + nInterpolations * nInterpolationColors;
		fireColors.reserve(totalColors);

		InterpolateColors(Colors::Black, Colors::Red, nInterpolationColors);
		InterpolateColors(Colors::Red, Colors::Orange, nInterpolationColors);
		InterpolateColors(Colors::Orange, Colors::Yellow, nInterpolationColors);
		InterpolateColors(Colors::Yellow, Colors::White, nInterpolationColors);
		fireColors.emplace_back(Colors::White);
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
	Vector2<int> firePosition{ 100,100 };
	static constexpr int nColumns = 120;
	static constexpr int nRows = 80;
	static constexpr int cellWidth = 5;
	static constexpr int cellHeight = 5;
	std::vector<Color> fireColors;
	std::vector<int> cells;
	std::mt19937 rng;
	std::uniform_int_distribution<int> decayDist;
};