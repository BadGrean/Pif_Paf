#include "Player.h"


void Player::scaleToWindowSize()
{
	sizeH = sizeH * GameInfo::windowSizeY / 1080;
	sizeW = sizeW * GameInfo::windowSizeY / 1080;
}

void Player::update(SDL_Rect* dst)
{
	speedX = speedX;
	speedY = speedY + acceleration * deltaTime() / 1000; //grawitacja

	posX = posX + speedX * deltaTime() / 1000 * GameInfo::windowSizeY / 1080;
	posY = posY + speedY * deltaTime() / 1000 * GameInfo::windowSizeY / 1080;

	dst->x = (int(posX) % windowSizeX + windowSizeX) % windowSizeX;
	dst->y = (int(posY) % windowSizeY + windowSizeY) % windowSizeY;
}

void Player::render(SDL_Renderer* renderer,SDL_Texture* texture,const SDL_Rect* src, const SDL_Rect* dst)
{
	SDL_RenderCopy(renderer, texture, NULL, dst);
	textureEdgeBending(renderer, texture, NULL, dst, sizeW, sizeH);
}
