#include "music.h"
Mix_Music *gMusic;
void initMusic(char *filename, int m_volume){

	Mix_Init(MIX_INIT_MP3);
	SDL_AudioSpec spec = (SDL_AudioSpec){MIX_DEFAULT_FORMAT, 2, 255};
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		printf("SDL_mixer could not initialize!", SDL_GetError());

	//setVolume(80);


	gMusic = Mix_LoadMUS(filename);
	if (!gMusic) printf("eita gMusic: %s\n", SDL_GetError());
	/*int volume = (MIX_MAX_VOLUME * m_volume) / 100;
	if (Mix_PlayingMusic() == 0){
		Mix_Volume(1, volume);
		Mix_PlayMusic(gMusic, -1);
	}; */ 
}
void togglePlay(){
	if (Mix_PausedMusic() == 1){
		Mix_ResumeMusic();
	} else {
		Mix_PauseMusic();
	};
}
