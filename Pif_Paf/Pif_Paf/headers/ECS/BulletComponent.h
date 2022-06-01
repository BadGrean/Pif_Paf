#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"
class BulletComponent : public Component
{
public:
	BulletComponent(int rng, int sp , Vector2D vel) : range(rng), speed(sp), velocity(vel)
	{
	}
	~BulletComponent()
	{

	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;
		if (distance > range)
		{
			entity->destroy();
		}
		/*else if (transform->position.x > 1920 - 64 || transform->position.x < 0 || transform->position.y > 1080 - 64 || transform->position.y < 0)//will need fixing   
		{
			entity->destroy(); //either this statement is rewritten somehow, or the player movement will be obscurely bulky
		}*/
	}

private:

	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;

};