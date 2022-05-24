#pragma once
#include "GameInfo.h"

class Player : public virtual GameInfo
{
public:
	void scaleToWindowSize();
	void update();
	void render(SDL_Renderer* renderer, SDL_Texture* playerTexture, const SDL_Rect* src, const SDL_Rect* dst);
private:
	double posX = 0, posY = 0;
	double speedX = 0, speedY = 0;
	int acceleration = 100;
	int speedIncrement = 200;
	int sizeH = 32, sizeW = 32;
	friend class Game;
};
