#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "AssetManager.h"
SDL_Texture* playerTexture, * targetTexture, * pauseTexture, * bulletTexture;
SDL_Rect srcPlayerRect, dstPlayerRect, dstTargetRect, dstBulletRect;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;

AssetManager* Game::assets = new AssetManager(&manager);


auto& player(manager.addEntity());
auto& bullet(manager.addEntity());

enum groupLables : std::size_t
{
	groupPlayers,
	groupTargets,
	groupAmmo,
	groupBullets,
};

Game::Game()
{

}

Game::~Game()
{

}

void Game::scaleToWindowSize()
{
	Player::scaleToWindowSize();
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

	assets->AddTexture("player", "assets/Player.png");
	assets->AddTexture("bullet", "assets/bullet.png");
	//Bullet::textureInit(renderer, targetTexture); //dont load texture  what a pity

	/*playerTexture = TextureManager::LoadTexture("assets/Player.png", renderer);
	targetTexture = TextureManager::LoadTexture("assets/Target.svg.png", renderer);
	pauseTexture = TextureManager::LoadTexture("assets/pause-icon.png", renderer);
	bulletTexture = TextureManager::LoadTexture("assets/bullet.png", renderer);*/

	//ECS implementation dont't kill me for what have i done 
	
	
	player.addComponent<TransformComponent>(100,500);
	player.addComponent<SpriteComponent>("player");
	player.addComponent<MouseController>();
	player.addGroup(groupPlayers);

	assets->CreateBullet(Vector2D(500, 500),Vector2D(2,0), 200, 2, "bullet"); //you cant just make vector (2,0)   for vec(x,y)  x^2+y^2=1  always
	assets->CreateBullet(Vector2D(500, 600), Vector2D(0.1, -0.1), 200, 2, "bullet");
	
	

	//playMusic("assets/Music.wav");
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN: 
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			assets->CreateBullet(Vector2D(2, 3), Vector2D(1,2), 1000, 2, "bullet");//another attempt, but here I cant get player Position easily and I dont wanna ruin the code I guess
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
		}
	default:
		break;
	}
}

void Game::update()
{
	//Player::update(&dstPlayerRect);
	//Bullet::update(&dstBulletRect);
	//walls loop back
	//player->update();
	manager.refresh();
	manager.update();
	//aby modulo z ujemnych dzialalo poprawnie
	
}

auto& players(manager.getGroup(groupPlayers));
auto& bullets(manager.getGroup(groupBullets));

void Game::render()
{
	SDL_RenderClear(renderer);
	//Player::render(renderer, playerTexture, NULL, &dstPlayerRect);
	//Bullet::render(renderer, bulletTexture, NULL, &dstBulletRect);
	//SDL_RenderCopy(renderer, targetTexture, NULL, &dstTargetRect);
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& b : bullets)
	{
		b->draw();
	}
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