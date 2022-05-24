#include "Player.h"

void Player::scaleToWindowSize()
{
	sizeH = sizeH * GameInfo::windowSizeY / 1080;
	sizeW = sizeW * GameInfo::windowSizeY / 1080;
	acceleration = acceleration * GameInfo::windowSizeY / 1080;
	speedIncrement = speedIncrement * GameInfo::windowSizeY / 1080;  //speed and acceleration does not scale properly
}

void Player::update()
{
	Player::speedX = Player::speedX;
	Player::speedY = Player::speedY + Player::acceleration * (time() - lastFrameTime()) / 1000; //grawitacja

	Player::posX = Player::posX + Player::speedX * (time() - lastFrameTime()) / 1000;
	Player::posY = Player::posY + Player::speedY * (time() - lastFrameTime()) / 1000;
}

void Player::render(SDL_Renderer* renderer,SDL_Texture* playerTexture,const SDL_Rect* src, const SDL_Rect* dst)
{
	SDL_RenderCopy(renderer, playerTexture, NULL, dst);
	if (GameInfo::windowSizeX - dst->x < sizeW)
	{
		SDL_Rect  temp = *(SDL_Rect*)dst;
		temp.x = dst->x - GameInfo::windowSizeX;
		SDL_RenderCopy(renderer, playerTexture, NULL, &temp);
	}
	if (GameInfo::windowSizeY - dst->y < sizeH)
	{
		SDL_Rect  temp = *(SDL_Rect*)dst;
		temp.y = dst->y - GameInfo::windowSizeY;
		SDL_RenderCopy(renderer, playerTexture, NULL, &temp);

		if (GameInfo::windowSizeX - dst->x < sizeW)
		{
			temp.x = dst->x - GameInfo::windowSizeX;
			SDL_RenderCopy(renderer, playerTexture, NULL, &temp);
		}
	}
}
