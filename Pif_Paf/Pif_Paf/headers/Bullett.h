#pragma once
#include "GameInfo.h"

class Bullet : public virtual GameInfo
{
private:

	friend class Game;

	void textureInit(SDL_Renderer* renderer, SDL_Texture* texture);
	void scaleToWindowSize();
	void update(SDL_Rect* dst);
	void render(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst);

	int sizeH, sizeW;
	double posX = 0, posY = 0;
	double speedX = 0, speedY = 0;
	int speedIncrement = 200;
};