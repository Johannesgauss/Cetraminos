#ifndef GSTRING_H
#define GSTRING_H
#include "frontendPieces.h"
typedef struct Font_Manager_Data  {
	TTF_Font 	*font;
	SDL_Texture 	*texture; // I gotta change this name, it doesn't make sense anymore
	SDL_Color color;
} Fontman_Data;
typedef struct Font_Manager {
	Fontman_Data 	*data;
	size_t 		font_size;
	SDL_Rect 	char_rect; 
	double 		ratio;
} Fontman;
typedef struct GString_Data GString_Data;
typedef struct GString {
	GE 		GE;
	Fontman 	fontman;

	GString_Data 	*data;

	char 		*string;
	size_t 		buffer;
} GString;
Fontman Fontman__Init(GE mainGE, char *font_path, size_t font_size, double ratio, SDL_Color color);
void Fontman__Destroy(Fontman self);

GString GString__Create(GE mainGE, Fontman fontman, int x, int y, char *string, size_t buffer);
void GString__Destroy(GString self);
void GString__RenderCopy(GString self);
#endif //GSTRING_H
