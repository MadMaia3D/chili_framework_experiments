#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"
#include <vector>

class Animation {
public:
	Animation(int x, int y, int nFrames, float frameDuration, const SpriteSheet& spriteSheet);
	void Update(float deltaTime);

	template<typename SpriteEffect>
	void Draw(Vei2 position, const SpriteEffect& effect, Graphics& gfx) const
	{
		gfx.DrawSprite(position.x, position.y, frameRects[currentFrame], spriteSheet.image, effect);
	}
private:
	void AdvanceFrame();
private:
	const SpriteSheet& spriteSheet;
	const float frameDuration;
	const int totalFramesCount;
	std::vector<RectI> frameRects;
	int currentFrame = 0;
	float currentTime = 0.0f;
};