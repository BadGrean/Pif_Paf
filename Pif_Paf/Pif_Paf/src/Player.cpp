#include "Player.h"

void Player::scaleToWindowSize()
{
	sizeH = sizeH * GameInfo::windowSizeY / 1080;
	sizeW = sizeW * GameInfo::windowSizeY / 1080;
	acceleration = acceleration * GameInfo::windowSizeY / 1080;
	speedIncrement = speedIncrement * GameInfo::windowSizeY / 1080;
}
