#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


void my_audio_callback(void* userdata, Uint8* stream, int len);

void playMusic(const char* musicPath);

void stopMusic();
