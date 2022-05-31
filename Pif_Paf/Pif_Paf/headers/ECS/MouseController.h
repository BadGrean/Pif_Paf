#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include <math.h>

class MouseController : public Component
{
public:
	TransformComponent* transform;

	void init()override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		switch (Game::event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (Game::event.button.button == SDL_BUTTON_LEFT)
			{
				transform->velocity.y = 0;
				int x = ( int(transform->position.x) % 1920 + 1920) % 1920;
				int y = ( int(transform->position.y) % 1080 + 1080) % 1080;
				transform->velocity.y = -(Game::event.button.y - y) / sqrt((Game::event.button.y - y) * (Game::event.button.y - y) + (Game::event.button.x - x) * (Game::event.button.x - x));
				transform->velocity.x = -(Game::event.button.x - x) / sqrt((Game::event.button.y - y) * (Game::event.button.y - y) + (Game::event.button.x - x) * (Game::event.button.x - x));
				//assets->CreateBullet(Vector2D(500, 600), Vector2D(0.1, -0.1), 200, 2, "bullet"); //cant get to assets
			}

			break;
		default:
			if (transform->velocity.y < 5) //velocity is always between values of -1 and 1 so this is pointless
			{
				transform->velocity.y += 0.005;
			}
			break;
		}

	}
};