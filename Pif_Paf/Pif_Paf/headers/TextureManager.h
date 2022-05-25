#pragma once
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* file_name, SDL_Renderer* ren);
};

