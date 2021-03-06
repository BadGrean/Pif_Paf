#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::CreateBullet(Vector2D pos,Vector2D vel, int range, int speed, std::string id)
{
	auto& bullet(manager->addEntity());
	bullet.addComponent<TransformComponent>(pos.x, pos.y);
	bullet.addComponent<SpriteComponent>(id);
	bullet.addComponent<BulletComponent>(range, speed, vel);
	bullet.addGroup(Game::groupBullets);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::CreateTarget(Vector2D pos, std::string id)
{
	auto& target(manager->addEntity());
	target.addComponent<TransformComponent>(pos.x, pos.y);
	target.addComponent<SpriteComponent>(id);
	target.addGroup(Game::groupTargets);
}

void AssetManager::CreateAmmo(Vector2D pos, std::string id)
{
	auto& ammo(manager->addEntity());
	ammo.addComponent<TransformComponent>(pos.x, pos.y);
	ammo.addComponent<SpriteComponent>(id);
	ammo.addGroup(Game::groupAmmo);

}

void AssetManager::CreatePlayer(Vector2D pos, std::string id)
{
	auto& player(manager->addEntity());
	player.addComponent<TransformComponent>(pos.x, pos.y);
	player.addComponent<SpriteComponent>(id);
	player.addGroup(Game::groupPlayers);
}

void AssetManager::CreateText(Vector2D pos, std::string msg, std::string fontType, int fontSize, std::string id)
{
	auto& text(manager->addEntity());
	text.addComponent<TransformComponent>(pos.x, pos.y);
	text.addComponent<SpriteComponent>(msg, fontType, fontSize, id);
	text.addGroup(Game::groupTexts);
}
