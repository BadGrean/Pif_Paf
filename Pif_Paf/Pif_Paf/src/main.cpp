#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char *argv[])
{
	
	game = new Game();
	game->init("Pif Paf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, true);
	game->dataInit();
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	
	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		//game->time();
		//if (game->deltaTime() > 10) //100tick cap + 100fps cap
		//{
		game->update();
		//game->setLastFrameTime();
		game->render();
		//}

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime); //frames as time
		}

	}
	game->clean();
	return 0;
}

/*
To do list when add new object:
	
	*class Object: public virtual GameInfo
		{friend class Game;}
	*class GameInfo
		{friend class Object;}
	*class Game: public Object*
	
	*in game.cpp
	SDL_Texture *objectTexture;
	SDL_Rect dstObjectRect;
	*Game::init
	tmpSurface = IMG_Load("Object.png");
	objectTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	*class Object + void Game::...
	scaleToWindowSize()
	update()
	render()
*/