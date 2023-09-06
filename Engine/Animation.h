#pragma once
#include "Graphics.h"
#include <vector>

class Animation {
public:
	Animation(int x, int y, int nColumns, int nRows, int nFrames, float frameDuration,
		const Surface& spriteSheet, const Color& chroma = Colors::Magenta);
	void Update(float deltaTime);
	void Draw( Vei2 position, Graphics& gfx) const;
	void AdvanceFrame();
private:
	const Surface& spriteSheet;
	const Color& chroma;
	const float frameDuration;
	const int totalFramesCount;
	std::vector<RectI> frameRects;
	int currentFrame = 0;
	float currentTime = 0.0f;
};