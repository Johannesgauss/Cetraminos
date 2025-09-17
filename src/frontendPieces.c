#include "menu.h"
SDL_Texture *createTextTexture(GE *mainGE, char *text)
{
	mainGE->font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuMathTeXGyre.ttf", 24);
	if (mainGE->font == NULL) printf("oops");;
	SDL_Surface *textSurface = TTF_RenderText_Solid(mainGE->font, text, strlen(text), (SDL_Color){255, 0, 0, 255});
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(mainGE->Renderer, textSurface);
	if (!textTexture) printf("oops");
	SDL_DestroySurface(textSurface);
	return textTexture;
	//SDL_SetTextureScaleMode(graphicEnvironment->textTexture, SDL_SCALEMODE_LINEAR);
}
	//SDL_RenderTexture(mainGE->Renderer, textTexture, NULL, textRect);
GE *createGraphicEnvironment()
{
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	GE *graphicEnvironment = (GE *) malloc(sizeof(GE));
	graphicEnvironment->Window = SDL_CreateWindow(WINDOW_TITLE, HEIGHT_WINDOW_RESOLUTION, LENGTH_WINDOW_RESOLUTION, WINDOW_FLAGS);
	if (graphicEnvironment->Window == NULL){
		SDL_GetError();
		SDL_Quit();
	};
	graphicEnvironment->Renderer = SDL_CreateRenderer(graphicEnvironment->Window, NULL);
	if (graphicEnvironment->Renderer == NULL) {
		SDL_GetError();
	SDL_Quit();
	};

	return graphicEnvironment;
}
void destroyGraphicEnvironment(GE *mainGE)
{
	TTF_CloseFont(mainGE->font);
	SDL_DestroyRenderer(mainGE->Renderer);
	SDL_DestroyWindow(mainGE->Window);
	free(mainGE);
}

