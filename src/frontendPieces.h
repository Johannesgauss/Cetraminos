#ifndef GE_H
#define GE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "backendPieces.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "music.h"
#define HEIGHT_WINDOW_RESOLUTION 1540
#define LENGTH_WINDOW_RESOLUTION 1040
#define WINDOW_FLAGS SDL_WINDOW_FULLSCREEN
#define GE_EXTENDS_CONTENT \
	SDL_Renderer *Renderer; \
	SDL_Event Event;

/*typedef struct GE_EXTENDS {
	GE_EXTENDS_CONTENT;
} GE_EXTENDS;*/

typedef struct GE_Data GE_Data;
typedef struct GraphicEnvironment{
	GE_Data *data;
	GE_EXTENDS_CONTENT;
} GE;


#define DEFAULT_FONT "./fonts/DejaVuMathTeXGyre.ttf"
#define DEFAULT_FONT_SIZE 24

GE GE__Init();
GE *GE__Create();
void GE__Destroy(GE self);


SDL_Texture *createTextTexture(GE self, char *text);
#endif // GE_H
