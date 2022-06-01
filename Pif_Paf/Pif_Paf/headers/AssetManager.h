#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();
	void CreateTarget(Vector2D pos, std::string id);
	//game objects

	void CreateBullet(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	void CreateAmmo(Vector2D pos, std::string id);

	void CreateText(Vector2D pos, std::string text, std::string fontType, int fontSize, std::string id);

	//textures
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};