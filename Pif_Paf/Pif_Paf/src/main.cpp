#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Pif Paf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Surface* surface = IMG_Load("assets/background-cloud.jpg");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		std::cout << "Blad przy ladowaniu tekstury";
	}
	SDL_FreeSurface(surface);

	SDL_Rect destination;
	destination.x = 128;
	destination.y = 0;
	destination.w = 128;
	destination.h = 128;

	SDL_RenderCopy(renderer, texture, NULL, &destination);
	SDL_RenderPresent(renderer);

	std::cout << "Hello world\n";
	std::getchar();
	return 0;
}