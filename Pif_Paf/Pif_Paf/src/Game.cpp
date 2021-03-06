#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "AssetManager.h"
#include <fstream>
SDL_Texture* playerTexture, * targetTexture, * pauseTexture, * bulletTexture;
SDL_Rect srcPlayerRect, dstPlayerRect, dstTargetRect, dstBulletRect;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;

AssetManager* Game::assets = new AssetManager(&manager);


auto& player(manager.addEntity());
//auto& bullet(manager.addEntity());
//auto& target(manager.addEntity());

enum groupLables : std::size_t
{
	groupPlayers,
	groupTargets,
	groupAmmo,
	groupBullets,
	groupTexts,
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

	std::fstream myfile;
	myfile.open("assets/highscore.txt");
	myfile >> highscore;
	myfile.close();

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
	assets->AddTexture("target", "assets/Target.svg.png");
	assets->AddTexture("ammo", "assets/ammo.png");
	//gradnient.LoadTexture("assets/gradient.png");
	//Bullet::textureInit(renderer, targetTexture); //dont load texture  what a pity

	/*playerTexture = TextureManager::LoadTexture("assets/Player.png", renderer);
	targetTexture = TextureManager::LoadTexture("assets/Target.svg.png", renderer);
	pauseTexture = TextureManager::LoadTexture("assets/pause-icon.png", renderer);
	bulletTexture = TextureManager::LoadTexture("assets/bullet.png", renderer);*/

	//ECS implementation dont't kill me for what have i done 
	
	
	player.addComponent<TransformComponent>(1920 / 2, 1080 / 2 - 300);
	player.addComponent<SpriteComponent>("player");
	player.addComponent<MouseController>();
	player.addGroup(groupPlayers);

	//assets->CreateBullet(Vector2D(500, 500),Vector2D(2,0), 200, 2, "bullet");   //you cant just make vector (2,0)   for vec(x,y)  x^2+y^2=1  always
	//assets->CreateBullet(Vector2D(500, 600), Vector2D(0.1, -0.1), 200, 2, "bullet");
	
	//assets->CreatePlayer(Vector2D(1920 / 2, 1080 / 2 - 100), "player");
	assets->CreateAmmo(Vector2D(1920 / 2 + 300, 1080 / 2 + 300), "ammo");
	assets->CreateTarget(Vector2D(1920 / 2 - 300, 1080 / 2 + 300), "target");
	assets->CreateText(Vector2D(1800, 20), "Hello World!", "Sans.ttf", 24, "text");

	playMusic("assets/Music.wav");

}


auto& players(manager.getGroup(groupPlayers));
auto& bullets(manager.getGroup(groupBullets));
auto& targets(manager.getGroup(groupTargets));
auto& ammo(manager.getGroup(groupAmmo));
auto& text(manager.getGroup(groupTexts));


void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN: 
		if (event.button.button == SDL_BUTTON_LEFT && !isPaused)
		{
			//SDL_GetMouseState(&absolute_cast<int>(player.getComponent<MouseController>().pos.x), &absolute_cast<int>(player.getComponent<MouseController>().pos.y)); //Vector2D not Vector2DInt
			//assets->CreateBullet(player.getComponent<TransformComponent>().position, ~Vector2D(player.getComponent<TransformComponent>().position - player.getComponent<MouseController>().pos), 150, 1, "bullet");//another attempt, but here I cant get player Position easily and I dont wanna ruin the code I guess
			if (player.getComponent<MouseController>().ammunition > 0)
			{
				SDL_GetMouseState(&player.getComponent<MouseController>().pos.x, &player.getComponent<MouseController>().pos.y);
				assets->CreateBullet(player.getComponent<TransformComponent>().position, Vector2D(player.getComponent<TransformComponent>().position - player.getComponent<MouseController>().pos), 70, 1, "bullet");//another attempt, but here I cant get player Position easily and I dont wanna ruin the code I guess
				//player.getComponent<MouseController>().ammunition--; // it was substracted twice, this one is unnecesary and broke mouse controler if statement
				framesSinceLastShot = 0;
				system("CLS");
				std::cout << "Score: " << destroyedtargets << "\n";
				std::cout << "Ammo: " << player.getComponent<MouseController>().ammunition - 1 << "\n";
			}
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			for (auto& a : ammo)	a->destroy();
			for (auto& t : targets) t->destroy();
			for (auto& b : bullets) b->destroy();
			player.getComponent<TransformComponent>().position = Vector2D(1920 / 2, 1080 / 2 - 300);
			player.getComponent<TransformComponent>().velocity = Vector2D(0, 0);
			assets->CreateAmmo(Vector2D(1920 / 2 + 300, 1080 / 2 +300), "ammo");
			assets->CreateTarget(Vector2D(1920 / 2 - 300, 1080 / 2+ 300), "target");
			framesSinceLastShot = 0;
			destroyedtargets = 0;
			player.getComponent<MouseController>().ammunition = 4;
			std::cout << "________________\nNEW GAME\n";
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
				//SDL_Delay(3000);//instead of menu
				setLastFrameTime();

			}
			break;
		}
	default:
		break;
	}
}

void Game::update()
{
	framesSinceLastShot++;
	if (framesSinceLastShot < 180)
	{
		for (auto it = 0; it < bullets.size(); it++)
		{
			auto b = bullets[it];
			//?zapisz dane z entity1
			Vector2D bPos = b->getComponent<TransformComponent>().position;
			Vector2D bSize(64, 64);
			for (auto& t : targets)
			{
				Vector2D tPos = t->getComponent<TransformComponent>().position;
				Vector2D tSize(64, 64);
				if (bPos.x + bSize.x >= tPos.x && tPos.x + tSize.x >= bPos.x && bPos.y + bSize.y >= tPos.y && tPos.y + tSize.y >= bPos.y)
				{
					it++;
					t->destroy();
					destroyedtargets++;
					enable_ammmo = true;
					b->destroy();

					assets->CreateTarget(Vector2D((std::rand() % (1920 - 64)), (std::rand() % (1080 - 64))), "target");

					if (enable_ammmo && ammo.size() < 2)
					{
						assets->CreateAmmo(Vector2D((std::rand() % (1920 - 64)), (std::rand() % (1920 - 64))), "ammo");

					}
				}
			}
		}
		for (auto& p : players)
		{
			//?zapisz dane z entity1
			Vector2D bPos = p->getComponent<TransformComponent>().position;
			Vector2D bSize(64, 64);
			for (auto& a : ammo)
			{
				Vector2D tPos = a->getComponent<TransformComponent>().position;
				Vector2D tSize(64, 64);
				if (bPos.x + bSize.x >= tPos.x && tPos.x + tSize.x >= bPos.x && bPos.y + bSize.y >= tPos.y && tPos.y + tSize.y >= bPos.y)
				{
					a->destroy();
					player.getComponent<MouseController>().ammunition += 3;
					enable_ammmo = false;

				}
			}
		}




		//Player::update(&dstPlayerRect);
		//Bullet::update(&dstBulletRect);
		//walls loop back
		//player->update();
		manager.refresh();
		manager.update();
		//aby modulo z ujemnych dzialalo poprawnie
	}
	else if(framesSinceLastShot >= 180)
	{
		SDL_Event sdlevent;
		sdlevent.type = SDL_MOUSEBUTTONDOWN;
		sdlevent.button.button = SDL_BUTTON_RIGHT;

		SDL_PushEvent(&sdlevent);
		framesSinceLastShot = 0;
	}

}


void Game::render()
{
	SDL_RenderClear(renderer);
	//Player::render(renderer, playerTexture, NULL, &dstPlayerRect);
	//Bullet::render(renderer, bulletTexture, NULL, &dstBulletRect);
	//SDL_RenderCopy(renderer, targetTexture, NULL, &dstTargetRect);

	/*

	TextureManager gradnient;
	SDL_Rect gd, zer;
	gd.x = player.getComponent<TransformComponent>().position.x + framesSinceLastShot/2*64/180;
	gd.y = player.getComponent<TransformComponent>().position.y+64;
	gd.w = (180 - framesSinceLastShot)*64/180;
	gd.h = 8;
	zer.x = zer.y = zer.w = zer.h = 0;
	gradnient.Draw(gradnient.LoadTexture("assets/gradient.png"), zer, gd);
	*/
	

	for (auto& b : bullets)
	{
		b->draw();
	}
	for (auto& t : targets)
	{
		t->draw();
	}
	for (auto& a : ammo)
	{
		a->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}

	if (destroyedtargets > highscore)
	{
		newHighscore(destroyedtargets);
	}
	TextureManager timeBar, ammoCount, currentScore;
	SDL_Rect tB, aC, zer, cS;
	tB.x = 1720 + framesSinceLastShot;
	tB.y = 20;
	tB.w = 180 - framesSinceLastShot;
	tB.h = 20;
	zer.x = zer.y = zer.w = zer.h = 0;
	timeBar.Draw(timeBar.LoadTexture("assets/gradient.png"), zer, tB);

	aC.y = 20 + 20 + 1;
	aC.h = aC.w = 10;
	for (int i = 0; i < player.getComponent<MouseController>().ammunition; i++)
	{
		aC.x = 1900 - 10 - 10 * i;
		ammoCount.Draw(ammoCount.LoadTexture("assets/bullet.png"), zer, aC);
	}

	cS.y = 5;
	cS.h = cS.w = 10;
	int power = 0;
	int score = destroyedtargets;
	do
	{
		cS.x = 1900 - 10 - 10 * power;
		ammoCount.Draw(ammoCount.LoadTexture("assets/fade.png"), zer, cS);
		if (score % 2)
		{
			ammoCount.Draw(ammoCount.LoadTexture("assets/Target.svg.png"), zer, cS);
		}
		score /= 2;
		power++;
	} while (score > 0);

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