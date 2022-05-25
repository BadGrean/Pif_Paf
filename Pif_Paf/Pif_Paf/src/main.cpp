#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char *argv[])
{
	
	game = new Game();
	game->init("Pif Paf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920/5, 1080/5, true);
	game->dataInit();
	
	while (game->running())
	{
		game->handleEvents();
		game->time();

		
		if (game->deltaTime() > 10) //100tick cap + 100fps cap
		{
			game->update();
			game->setLastFrameTime();
			game->render();
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