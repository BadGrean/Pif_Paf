#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
SDL_Texture* playerTexture, * targetTexture, * pauseTexture, * bulletTexture;
SDL_Rect srcPlayerRect, dstPlayerRect, dstTargetRect, dstBulletRect;
GameObject* player;


Game::Game()
{

}

Game::~Game()
{

}

void Game::scaleToWindowSize()
{
	Player::scaleToWindowSize();
	Bullet::scaleToWindowSize();
}

void Game::dataInit()
{
	dstPlayerRect.x = Player::posX;
	dstPlayerRect.y = Player::posY;
	dstPlayerRect.h = Player::sizeH = GameInfo::standardSize;
	dstPlayerRect.w = Player::sizeW = GameInfo::standardSize;

	dstTargetRect.x = 100;
	dstTargetRect.y = 100;
	dstTargetRect.h = 64;
	dstTargetRect.w = 64;

	dstBulletRect.x = 1000;
	dstBulletRect.y = 100;
	dstBulletRect.h = Bullet::sizeH = GameInfo::standardSize / 2;
	dstBulletRect.w = Bullet::sizeW = GameInfo::standardSize / 2;

	scaleToWindowSize();
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
			standardSize = windowSizeY * 4 / 135;
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
	Bullet::textureInit(renderer, targetTexture); //dont load texture  what a pity

	playerTexture = TextureManager::LoadTexture("assets/Player.png", renderer);
	targetTexture = TextureManager::LoadTexture("assets/Target.svg.png", renderer);
	pauseTexture = TextureManager::LoadTexture("assets/pause-icon.png", renderer);
	bulletTexture = TextureManager::LoadTexture("assets/bullet.png", renderer);
	player = new GameObject("assets/Player.png", renderer, 0, 0);

	playMusic("assets/Music.wav");
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
		//Player::posX = event.button.x;
		//Player::posY = event.button.y;
		//Player::speedX = 0;
			Bullet::posX = dstBulletRect.x = dstPlayerRect.x + Player::sizeW / 2 - Bullet::sizeW / 2;
			Bullet::posY = dstBulletRect.y = dstPlayerRect.y + Player::sizeH / 2 - Bullet::sizeH / 2;



			Bullet::speedX = Bullet::speedIncrement * (event.button.x - (dstBulletRect.x + Bullet::sizeW / 2) % windowSizeX) / sqrt(((dstBulletRect.x + Bullet::sizeW / 2) % windowSizeX - event.button.x) * ((dstBulletRect.x + Bullet::sizeW / 2) % windowSizeX - event.button.x) + ((dstBulletRect.y + Bullet::sizeH / 2) % windowSizeY - event.button.y) * ((dstBulletRect.y + Bullet::sizeH / 2) % windowSizeY - event.button.y));
			Bullet::speedY = Bullet::speedIncrement * (event.button.y - (dstBulletRect.y + Bullet::sizeH / 2) % windowSizeY) / sqrt(((dstBulletRect.x + Bullet::sizeW / 2) % windowSizeX - event.button.x) * ((dstBulletRect.x + Bullet::sizeW / 2) % windowSizeX - event.button.x) + ((dstBulletRect.y + Bullet::sizeH / 2) % windowSizeY - event.button.y) * ((dstBulletRect.y + Bullet::sizeH / 2) % windowSizeY - event.button.y));
			//td::cout << int(Bullet::speedIncrement * ((dstBulletRect.x + Bullet::sizeW / 2) % windowSizeX - event.button.x) / sqrt(((dstBulletRect.x + Bullet::sizeW / 2) % windowSizeX - event.button.x) * ((dstBulletRect.x + Bullet::sizeW / 2) % windowSizeX - event.button.x) + ((dstBulletRect.y + Bullet::sizeH / 2) % windowSizeY - event.button.y) * ((dstBulletRect.y + Bullet::sizeH / 2) % windowSizeY - event.button.y))) <<"\nBullet speed: ";
			Player::speedY = 0;
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
	Player::update(&dstPlayerRect);
	Bullet::update(&dstBulletRect);
	//walls loop back
	player->Update();
	//aby modulo z ujemnych dzialalo poprawnie
	
}

void Game::render()
{
	SDL_RenderClear(renderer);
	Player::render(renderer, playerTexture, NULL, &dstPlayerRect);
	Bullet::render(renderer, bulletTexture, NULL, &dstBulletRect);
	//SDL_RenderCopy(renderer, targetTexture, NULL, &dstTargetRect);
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	stopMusic();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game clean\n";
}