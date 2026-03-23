#include "frontendPieces.h"
#include "error.h"
#define WINDOW_TITLE "Cetraminos"
#define MUSIC_FILE "./CetraminosMusic2.mp3"
#define FONT_COLOR (SDL_Color){255, 0, 0, 255}

struct GE_Data{
	SDL_Window *Window;
	TTF_Font *font;
};

GE GE__Init()
{
	GE self;
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	initMusic(MUSIC_FILE);
	self.data = malloc(sizeof(*(self.data)));
	self.data->Window = SDL_CreateWindow(WINDOW_TITLE, 0, 0, HEIGHT_WINDOW_RESOLUTION, LENGTH_WINDOW_RESOLUTION, WINDOW_FLAGS); get_error(self.data->Window);
	self.Renderer = SDL_CreateRenderer(self.data->Window, -1, 0); get_error(self.Renderer);

	return self;
}

GE *GE__Create()
{
	GE *self = malloc(sizeof(*self)); get_error(self);
	*self = GE__Init();
	return self;
}


void GE__Destroy(GE self)
{
	TTF_CloseFont(self.data->font);
	SDL_DestroyRenderer(self.Renderer);
	SDL_DestroyWindow(self.data->Window);
	free(self.data);
}


SDL_Texture *createTextTexture(GE self, char *text)
{
	TTF_Font *font = TTF_OpenFont(DEFAULT_FONT, DEFAULT_FONT_SIZE); get_error(font);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, FONT_COLOR); get_error(textSurface);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(self.Renderer, textSurface); get_error(textTexture);
	return textTexture;
}

