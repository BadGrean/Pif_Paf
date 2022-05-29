#pragma once
#include "GameInfo.h"

class GameMath
{
public:
	int vectorInWindowX(double* vector, double* offset);
	int vectorInWindowY(double* vector, double* offset);
	void vector(int srcVector[2], int dstVector[2], int result[2]);
	friend class GameObject;
};