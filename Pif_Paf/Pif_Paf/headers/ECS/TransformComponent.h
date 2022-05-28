#pragma once
#include "Components.h"
#include "../Vector2D.h"
class TransformComponent : public Component //we can use struct here
{
public:

	Vector2D position;
	Vector2D velocity;

	int speed = 20;


	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void init()override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
