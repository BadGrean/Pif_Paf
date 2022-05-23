#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Player
{
public:

private:
	double posX = 0, posY = 0;
	int acceleration = 100;
	double speedX = 0, speedY = 0;
	int sizeH = 32, sizeW = 32;
	friend class Game;
};


class Game: public Player
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
	//void pauseMenu();
private:
	bool isRunning, isPaused = false;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowSizeX, windowSizeY;
	unsigned int currentTime, lastTime = 0;

};


