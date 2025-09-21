#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "backendPieces.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "music.h"
#define WINDOW_TITLE "Cetraminos"
#define HEIGHT_WINDOW_RESOLUTION 1540
#define LENGTH_WINDOW_RESOLUTION 1040
#define WINDOW_FLAGS 0 
typedef struct GraphicEnvironment {
	SDL_Window *Window;
	SDL_Renderer *Renderer;
	SDL_Event Event;
	TTF_Font *font;
} GE;
SDL_Texture *createTextTexture(GE *mainGE, char *text);
GE *createGraphicEnvironment();
void destroyGraphicEnvironment(GE *mainGE);
