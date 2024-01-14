#pragma once

#include <SDL.h>

class FrameHandler {

private:
	Uint64 frameLength;
	Uint64 startTime;
	unsigned int frameCount;
	Uint64 lastFrame;
public:
	FrameHandler(int fr);

	void restartTime();

	bool drawNewFrame();

	unsigned int getFrameCount();

	Uint64 timeSinceStart();

};

