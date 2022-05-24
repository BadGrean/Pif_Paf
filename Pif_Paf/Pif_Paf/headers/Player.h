#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "GameInfo.h"

class Player : public virtual GameInfo
{
public:
	void scaleToWindowSize();
private:
	double posX = 0, posY = 0;
	double speedX = 0, speedY = 0;
	int acceleration = 100;
	int speedIncrement = 200;
	int sizeH = 32, sizeW = 32;
	friend class Game;
};
