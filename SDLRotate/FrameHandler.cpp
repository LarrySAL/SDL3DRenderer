#include "FrameHandler.h"

FrameHandler::FrameHandler(int frameRate) : 
	startTime(SDL_GetTicks64()), 
	frameCount(0), 
	lastFrame(0) {

	frameLength = static_cast<Uint64>((1 / static_cast<double>(frameRate)) * 1000);
}

void FrameHandler::restartTime() {
	startTime = SDL_GetTicks64();
	frameCount = 0;
	lastFrame = 0;
}

bool FrameHandler::drawNewFrame() {
	
	Uint64 currentTime = SDL_GetTicks64();
	Uint64 elapsedTime = currentTime - startTime;

	//check if time is apropiate and if frame hasn't been drawn already
	bool drawFrame = (
		((elapsedTime % frameLength) == 0) && 
		(lastFrame != currentTime)
	);

	if (drawFrame) {
		frameCount++;
		lastFrame = currentTime;
		return true;
	}
	return false;
}

unsigned int FrameHandler::getFrameCount(){
	return frameCount;
}

Uint64 FrameHandler::timeSinceStart() {
	Uint64 currentTime = SDL_GetTicks64();
	Uint64 elapsedTime = currentTime - startTime;
	return elapsedTime;
}