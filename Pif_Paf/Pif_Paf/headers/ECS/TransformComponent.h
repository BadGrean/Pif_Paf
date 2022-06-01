#pragma once
#include "Components.h"
#include "../Vector2D.h"
class TransformComponent : public Component //we can use struct here
{
public:

	Vector2D position;
	Vector2D velocity;

	int speed = 16;


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
		position.x = (int(position.x) % 1920 + 1920) % 1920;// +position.x - floor(int(position.x)) - abs(position.x) / position.x * 1920 / 2 + 1920 / 2; //big chunk, but better than if statements
		position.y = (int(position.y) % 1080 + 1080) % 1080;// +position.y - floor(int(position.y)) - abs(position.y) / position.y * 1080 / 2 + 1080 / 2;
	}
};
