#include "Game.h"

SDL_Texture* playerTexture, *targetTexture, *pauseTexture;
SDL_Rect srcPlayerRect, dstPlayerRect, dstTargetRect;

Game::Game()
{

}


Game::~Game()
{

}


void Game::dataInit()
{

	std::cout << Player::sizeH;

	scaleToWindowSize();

	std::cout << Player::sizeH;

	dstPlayerRect.x = 0;
	dstPlayerRect.y = 0;
	dstPlayerRect.h = sizeH;
	dstPlayerRect.w = sizeW;

	dstTargetRect.x = 100;
	dstTargetRect.y = 100;
	dstTargetRect.h = 64;
	dstTargetRect.w = 64;

}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP; //added DESKTOP - Alt+Tab does not crash
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialised\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);
			std::cout << "Window created\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0); //creates renderer (there may be more than one)
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created\n";
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	SDL_Surface* tmpSurface = IMG_Load("assets/Player.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	tmpSurface = IMG_Load("assets/Target.svg.png");
	targetTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	tmpSurface = IMG_Load("assets/pause-icon.png");
	pauseTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}


void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN: 
		if (event.button.button == SDL_BUTTON_LEFT)
		{
		Player::posX = event.button.x;
		Player::posY = event.button.y;
		Player::speedX = 0;
		speedY = 0;
		}
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:  
			isPaused = !isPaused;  //for later use menu 
			if (paused())
			{
				SDL_RenderCopy(renderer, pauseTexture, NULL, &dstPlayerRect);
				SDL_RenderPresent(renderer);
				SDL_Delay(3000);//instead of menu
				setLastFrameTime();
			}
			dstTargetRect.x = rand() % windowSizeX + 1; 
			dstTargetRect.y = rand() % windowSizeY + 1;
			break;

		case SDL_SCANCODE_UP:
			Player::speedY -= Player::speedIncrement;
			break;
		case SDL_SCANCODE_DOWN:
			Player::speedY += Player::speedIncrement;
			break;
		case SDL_SCANCODE_LEFT:
			Player::speedX -= Player::speedIncrement;
			break;
		case SDL_SCANCODE_RIGHT:
			Player::speedX += Player::speedIncrement;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}


void Game::update()
{

	Player::speedX = Player::speedX;
	Player::speedY = Player::speedY + Player::acceleration * (time() - lastFrameTime()) / 1000; //grawitacja

	Player::posX = Player::posX + Player::speedX * (time() - lastFrameTime()) / 1000;
	Player::posY = Player::posY + Player::speedY * (time() - lastFrameTime()) / 1000;

	
	//walls loop back
	dstPlayerRect.x = (int(Player::posX) % windowSizeX + windowSizeX) % windowSizeX;
	dstPlayerRect.y = (int(Player::posY) % windowSizeY + windowSizeY) % windowSizeY; //aby modulo z ujemnych dzialalo poprawnie
	
}


void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, playerTexture, NULL, &dstPlayerRect);
	SDL_RenderCopy(renderer, targetTexture, NULL, &dstTargetRect);
	SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game clean\n";
}