#include "Animation.h"
#include <assert.h>

Animation::Animation(int x, int y, int nFrames, float frameDuration, const SpriteSheet& spriteSheet)
	:
	spriteSheet(spriteSheet),
	frameDuration(frameDuration),
	totalFramesCount(nFrames)
{
	const int nColumns = spriteSheet.nColumns;
	const int nRows = spriteSheet.nRows;
	assert(nColumns > 0 && nRows > 0);
	assert(x < nColumns && y < nRows);

	const int spriteSheetWidth = spriteSheet.width;
	const int spriteSheetHeight = spriteSheet.height;
	const int frameWidth = spriteSheetWidth / nColumns;
	const int frameHeight = spriteSheetHeight / nRows;
	const int framesStartingColumn = x * frameWidth;
	const int framesRow = y * frameHeight;

	assert(framesStartingColumn + nFrames * frameWidth <= spriteSheetWidth);

	for (int i = 0; i < nFrames; i++) {
		const int rectX = framesStartingColumn + i * frameWidth;
		frameRects.emplace_back(rectX, framesRow, frameWidth, frameHeight);
	}
}

void Animation::Update(float deltaTime) {
	currentTime += deltaTime;

	while (currentTime > frameDuration) {
		currentTime -= frameDuration;
		AdvanceFrame();
	}
}

void Animation::Draw(Vei2 position, Graphics& gfx) const {
	gfx.DrawSprite(position.x, position.y, frameRects[currentFrame], spriteSheet.image, spriteSheet.chroma);
}

void Animation::AdvanceFrame() {
	if (++currentFrame >= totalFramesCount) {
		currentFrame = 0;
	}
}