#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include <math.h>


class MouseController : public Component , public GameInfo
{
public:
	TransformComponent* transform;
	int ammunition = 4;
	void init()override
	{
		transform = &entity->getComponent<TransformComponent>();
	}
	Vector2DInt pos;
	void update() override
	{
		switch (Game::event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (Game::event.button.button == SDL_BUTTON_LEFT)
			{
				if (ammunition > 0)
				{
					transform->velocity.y = 0;
					int x = (int(transform->position.x) % 1920 + 1920) % 1920;
					int y = (int(transform->position.y) % 1080 + 1080) % 1080;
					transform->velocity.y = -(Game::event.button.y - y) / sqrt((Game::event.button.y - y) * (Game::event.button.y - y) + (Game::event.button.x - x) * (Game::event.button.x - x));
					transform->velocity.x = -(Game::event.button.x - x) / sqrt((Game::event.button.y - y) * (Game::event.button.y - y) + (Game::event.button.x - x) * (Game::event.button.x - x));
					ammunition--;
					
					std::cout << "Ammo: " << ammunition << "\n";
				}
			}


			break;
		default:
			transform->velocity.y += 0.015;
			if (transform->velocity.y > 2.5)
			{
				isPaused = true;
				std::cout << "Speed: " << (int)sqrt(transform->velocity.x * transform->velocity.x + transform->velocity.y * transform->velocity.y) << "\n";
			}
			break;
		}

	}
};