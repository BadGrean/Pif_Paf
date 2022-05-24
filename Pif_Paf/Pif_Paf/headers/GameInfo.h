#pragma once


class GameInfo
{
private:
	friend class Player;
	friend class Game;
	bool isRunning, isPaused = false;
	int windowSizeX, windowSizeY;
	unsigned int currentTime, lastTime = 0;
};