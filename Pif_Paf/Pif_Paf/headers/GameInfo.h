#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


class GameInfo
{
public:
	unsigned int time() { return SDL_GetTicks(); }
	void setLastFrameTime() { lastTime = time(); }
	unsigned int deltaTime() { return time() - lastTime; }
	void textureEdgeBending(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst, int sizeW, int sizeH)
	{
		if (GameInfo::windowSizeX - dst->x < sizeW)
		{
			SDL_Rect  temp = *(SDL_Rect*)dst;
			temp.x = dst->x - GameInfo::windowSizeX;
			SDL_RenderCopy(renderer, texture, NULL, &temp);
		}
		if (GameInfo::windowSizeY - dst->y < sizeH)
		{
			SDL_Rect  temp = *(SDL_Rect*)dst;
			temp.y = dst->y - GameInfo::windowSizeY;
			SDL_RenderCopy(renderer, texture, NULL, &temp);

			if (GameInfo::windowSizeX - dst->x < sizeW)
			{
				temp.x = dst->x - GameInfo::windowSizeX;
				SDL_RenderCopy(renderer, texture, NULL, &temp);
			}
		}
	};

private:
	bool isRunning, isPaused = false;
	int windowSizeX, windowSizeY, standardSize;
	unsigned int lastTime = 0;

	friend class Player;
	friend class Game;
	friend class Bullet;
};