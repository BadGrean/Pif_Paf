#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Player.h"
#include "GameInfo.h"




class Game: public Player, public virtual GameInfo
{
public:
	Game();
	~Game();

	void dataInit();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
	bool paused() { return isPaused; }
	unsigned int time() { return SDL_GetTicks(); }
	unsigned int lastFrameTime() { return lastTime; } //da sie uproscic, ale nie myslalem o tym
	void setLastFrameTime() { lastTime = time(); }
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};



