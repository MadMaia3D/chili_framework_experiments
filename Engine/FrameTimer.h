#pragma once
#include <chrono>

class FrameTimer {
public:
	FrameTimer() {
		last = std::chrono::steady_clock::now();
	}

	float Mark() {
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		std::chrono::duration<float> duration = now - last;
		last = now;
		float elapsedSeconds = duration.count();
		return elapsedSeconds;
	}

private:
	std::chrono::steady_clock::time_point last;
};