#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

Game* game = nullptr;
Player* player = nullptr;

int main(int argc, char *argv[])
{
	game->dataInit();
	game = new Game();
	game->init("Pif Paf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, true);
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
	game->clean();
	return 0;
}

