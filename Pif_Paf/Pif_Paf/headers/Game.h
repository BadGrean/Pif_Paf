#pragma once
#include "Music.h"
#include "GameInfo.h"
#include "Player.h"
#include "Bullet.h"




class Game: public Player, public Bullet, public virtual GameInfo
{
public:
	Game();
	~Game();

	void scaleToWindowSize();
	void dataInit();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
	bool paused() { return isPaused; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
private:
	SDL_Window* window;
	
};


	
