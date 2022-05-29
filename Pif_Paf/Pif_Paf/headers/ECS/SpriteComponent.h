#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;//pixel value (temp)
		destRect.w = destRect.h = 32;//scaling here 32 * 2
	}
	void update() override
	{
		destRect.x = (int)transform->position.x; //wee need WindowSize here    SDL_GetWindowSize works on pointers and does not return value 
		destRect.y = (int)transform->position.y;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};