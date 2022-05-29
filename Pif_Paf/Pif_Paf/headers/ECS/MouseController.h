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
				//transform->velocity.y = -(Game::event.button.y - transform->position.y) / sqrt(Game::event.button.y * Game::event.button.y + transform->position.y * transform->position.y);//change for normalized vector cuz math is hard
				//transform->velocity.x = -(Game::event.button.x - transform->position.x) / sqrt(Game::event.button.x * Game::event.button.x + transform->position.x * transform->position.x);//same here
				transform->velocity.y = -(Game::event.button.y - transform->position.y) / sqrt((Game::event.button.y - transform->position.y) * (Game::event.button.y - transform->position.y) + (Game::event.button.x - transform->position.x) * (Game::event.button.x - transform->position.x));
				transform->velocity.x = -(Game::event.button.x - transform->position.x) / sqrt((Game::event.button.y - transform->position.y) * (Game::event.button.y - transform->position.y) + (Game::event.button.x - transform->position.x) * (Game::event.button.x - transform->position.x));
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