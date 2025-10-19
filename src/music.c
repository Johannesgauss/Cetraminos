#include "music.h"
Mix_Music *gMusic;
void initMusic(char *filename){

	Mix_Init(MIX_INIT_MP3);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		printf("SDL_mixer could not initialize: %s\n", SDL_GetError());
	gMusic = Mix_LoadMUS(filename);
