#include "menu.h"
SDL_Texture *createTextTexture(GE *graphicEnvironment, char *text)
{
	graphicEnvironment->font = TTF_OpenFont("fonts/DejaVuMathTeXGyre.ttf", 24);
	if (graphicEnvironment->font == NULL) printf("oops");
	SDL_Surface *textSurface = TTF_RenderText_Solid(graphicEnvironment->font, text, (SDL_Color){255, 0, 0, 255});
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(graphicEnvironment->Renderer, textSurface);
	if (!textTexture) printf("oops");
	//SDL_DestroySurface(textSurface);
	return textTexture;
}
GE *createGraphicEnvironment()
{
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	GE *graphicEnvironment = (GE *) malloc(sizeof(GE));
	initMusic("./CetraminosMusic.mp3", 80);
	graphicEnvironment->Window = SDL_CreateWindow(WINDOW_TITLE, 0, 0, HEIGHT_WINDOW_RESOLUTION, LENGTH_WINDOW_RESOLUTION, WINDOW_FLAGS);
	if (graphicEnvironment->Window == NULL){
		SDL_GetError();
		SDL_Quit();
	};
	graphicEnvironment->Renderer = SDL_CreateRenderer(graphicEnvironment->Window, -1, 0);
	if (graphicEnvironment->Renderer == NULL) {
		SDL_GetError();
	SDL_Quit();
	};

	return graphicEnvironment;
}
void destroyGraphicEnvironment(GE *graphicEnvironment)
{
	TTF_CloseFont(graphicEnvironment->font);
	SDL_DestroyRenderer(graphicEnvironment->Renderer);
	SDL_DestroyWindow(graphicEnvironment->Window);
	free(graphicEnvironment);
}

