#include "Music.h"

// variable declarations
static Uint8* audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play
static Uint8* wav_buffer; // buffer containing our audio file

void my_audio_callback(void* userdata, Uint8* stream, int len) {

	if (audio_len == 0)
		return;

	len = (len > audio_len ? audio_len : len);
	SDL_memcpy(stream, audio_pos, len); 					// simply copy from one buffer into the other
	//SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}

void playMusic(const char* musicPath)
{
	static Uint32 wav_length; // length of our sample
	static SDL_AudioSpec wav_spec; // the specs of our piece of music



	// the specs, length and buffer of our wav are filled
	if (SDL_LoadWAV(musicPath, &wav_spec, &wav_buffer, &wav_length) == NULL) {
		std::cout << "Music not loaded\n";
	}
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length


	SDL_OpenAudio(&wav_spec, NULL);


	SDL_PauseAudio(0);
}

void stopMusic()
{
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);
}