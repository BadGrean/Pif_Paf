#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class GameInfo
{
public:
	unsigned int time() { return SDL_GetTicks(); }
	unsigned int lastFrameTime() { return lastTime; } //da sie uproscic, ale nie myslalem o tym
	void setLastFrameTime() { lastTime = time(); }
private:
	friend class Player;
	friend class Game;
	bool isRunning, isPaused = false;
	int windowSizeX, windowSizeY;
	unsigned int currentTime, lastTime = 0;
};