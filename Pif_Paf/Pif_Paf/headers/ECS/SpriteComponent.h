#pragma once
#include "Components.h"
#include "SDL.h"
#include "../AssetManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}
	SpriteComponent(std::string msg, std::string fontType, int fontSize, std::string id)
	{
		setTex(id); //make text image
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;//pixel value (temp)
		destRect.w = destRect.h = 64;//scaling here 32 * 2

	}
	void update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}
	void draw() override
	{

		TextureManager gradnient;
		SDL_Rect gd, zer;
		gd.x = entity->getComponent<TransformComponent>().position.x - 64;
		gd.y = entity->getComponent<TransformComponent>().position.y - 64;
		gd.w = gd.h = 192;
		zer.x = zer.y = zer.w = zer.h = 0;
		gradnient.Draw(gradnient.LoadTexture("assets/fade.png"), zer, gd);
		TextureManager::Draw(texture, srcRect, destRect);
	}
};