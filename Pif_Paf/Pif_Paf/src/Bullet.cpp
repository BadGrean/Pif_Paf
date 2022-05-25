#include "Bullet.h"

void Bullet::scaleToWindowSize()
{
	sizeH = sizeH * GameInfo::windowSizeY / 1080;
	sizeW = sizeW * GameInfo::windowSizeY / 1080;
}

void Bullet::update(SDL_Rect* dst)
{
	speedX = speedX;
	speedY = speedY;

	posX = posX + speedX * deltaTime() / 1000 * GameInfo::windowSizeY / 1080;
	posY = posY + speedY * deltaTime() / 1000 * GameInfo::windowSizeY / 1080;

	dst->x = (int(posX) % windowSizeX + windowSizeX) % windowSizeX;
	dst->y = (int(posY) % windowSizeY + windowSizeY) % windowSizeY;
}

/*does not work*/
void Bullet::textureInit(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Surface* tmpSurface = IMG_Load("assets/Target.svg.png");
	texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Bullet::render(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst)
{
	SDL_RenderCopy(renderer, texture, NULL, dst);
	textureEdgeBending(renderer, texture, NULL, dst, sizeW, sizeH);
}
