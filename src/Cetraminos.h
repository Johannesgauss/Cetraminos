#pragma once
#include "backendPieces.h"
#include "frontendPieces.h"
#include "menu.h"
#include "music.h"
#include "randomGenerator.h"
#include "scoreSystem.h"
#include "randomGenerator.h"
#include "error.h"

#define SCORE_RECT (SDL_Rect){100, 100, 200, 100}
#define WINDOW_RECT  {100,100,HEIGHT_WINDOW_RESOLUTION-500,LENGTH_WINDOW_RESOLUTION-500}
#define RENDER_ARRAY \
		{100 ,100 ,50  ,255}, \
		{200 ,100 ,100 ,255}, \
		{100 ,0   ,100 ,255}, \
		{0   ,255 ,50  ,255}, \
		{255 ,255 ,255 ,255}, \
		{154 ,137 ,200 ,255}, \
		{255 ,0   ,0   ,255}, \
		{0   ,255 ,0   ,255}, 
#define TEXT_BUFFER_SIZE 40
#define BLOCKS_COLORS
#define frameRate(stepsToFall) 20 + 70 * (1 - (stepsToFall % 4))

struct score_sys {
	unsigned int	score;
	SDL_Rect	rect;
	SDL_Texture 	*texture;
	char 		*text;
	unsigned long	text_length; // Actually buffer size	
};

typedef struct Game {
	GE		 GE;

	struct score_sys scoresys;
	Piece 		 *piece;
	Piece  		 *masterPieces;
	int 		 (*Map)[MAP_X];
} Game;

SDL_Texture *gameOverHandler(GE *mainGE);
void scoreHandler(struct score_sys *scoresys, GE *mainGE, int moreScore);
void score_sys_destroy(struct score_sys *scoresys);
void GE__Renderer(GE *mainGE, int Map[MAP_Y][MAP_X]);
Game *Game__Create();
Game Game__Init();
void Game__Destroy(Game *self);
