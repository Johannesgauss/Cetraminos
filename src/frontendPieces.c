#include "frontendPieces.h"
#include "error.h"
SDL_Texture *createTextTexture(GE *self, char *text)
{
	self->font = TTF_OpenFont(FONT, FONT_SIZE); get_error(self->font);
	SDL_Surface *textSurface = TTF_RenderText_Solid(self->font, text, FONT_COLOR); get_error(textSurface);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(self->Renderer, textSurface); get_error(textTexture);
	return textTexture;
}

GE GE__Init()
{
	GE self;
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	initMusic(MUSIC_FILE);
	self.Window = SDL_CreateWindow(WINDOW_TITLE, 0, 0, HEIGHT_WINDOW_RESOLUTION, LENGTH_WINDOW_RESOLUTION, WINDOW_FLAGS); get_error(self.Window);
	self.Renderer = SDL_CreateRenderer(self.Window, -1, 0); get_error(self.Renderer);

	return self;
}

GE *GE__Create()
{
	GE *self = malloc(sizeof(*self)); get_error(self);
	*self = GE__Init();
	return self;
}


void GE__Destroy(GE *self)
{
	TTF_CloseFont(self->font);
	SDL_DestroyRenderer(self->Renderer);
	SDL_DestroyWindow(self->Window);
	free(self);
}

