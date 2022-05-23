#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "Music.h"

Game* game = nullptr;

int main(int argc, char *argv[])
{
	
	game = new Game();
	game->init("Pif Paf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, true);
	game->dataInit();
	playMusic("assets/Music.wav");
	while (game->running())
	{
		game->handleEvents();
		game->time();
		if (game->time() > game->lastFrameTime() + 10) //100fps cap
		{
			game->update();
			game->setLastFrameTime();
		}
		game->render();
	}
	stopMusic();
	game->clean();
	return 0;
}

