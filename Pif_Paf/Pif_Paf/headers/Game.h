#pragma once
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
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};



