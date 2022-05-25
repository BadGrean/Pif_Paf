#pragma once
#include "GameInfo.h"

class Player : public virtual GameInfo
{
private:

	friend class Game;

	
	void scaleToWindowSize();
	void update(SDL_Rect* dst);
	void textureInit(SDL_Renderer* renderer, SDL_Texture* playerTexture);
	void render(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst);
	
	int sizeH, sizeW;

	double posX = 0, posY = 0;
	double speedX = 0, speedY = 0;
	int acceleration = 100;
	int speedIncrement = 200;
};
