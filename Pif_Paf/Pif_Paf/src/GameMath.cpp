#include "GameMath.h"

void GameMath::chSpeed(double speed[2], int acceleration)
{
	speed[0]++;
	speed[1]++;
	return;
}

void GameMath::chPosition(double position[2], double speed[2], int acceleration)
{ 
	position[0] += speed[0];
	position[1] += speed[1];
	return;
}

void GameMath::chDest(SDL_Rect* dst, double position[2], double speed[2], int acceleration)
{
	chSpeed(speed, acceleration);
	chPosition(position, speed, acceleration);
	dst->x = position[0];
	dst->y = position[1];
}

void GameMath::vectorInWindow(double* vector, double* offset, int result[2])
{
	result[0] = int(vector[0] + offset[0]) % GameInfo::windowSizeX;
	result[1] = int(vector[1] + offset[1]) % GameInfo::windowSizeY;
	return;
}

void GameMath::vector(int srcVector[2], int dstVector[2], int result[2])
{
	result[0] = (dstVector[0] - srcVector[0]) / sqrt( (dstVector[0] - srcVector[0]) ^ 2 + (dstVector[1] - srcVector[1]) ^ 2 );
	result[1] = (dstVector[1] - srcVector[1]) / sqrt((dstVector[0] - srcVector[0]) ^ 2 + (dstVector[1] - srcVector[1]) ^ 2);
	return;
}
