#ifndef CETRAMINOS_H
#define CETRAMINOS_H
#include "backendPieces.h"
#include "frontendPieces.h"
#include "menu.h"
#include "music.h"
#include "randomGenerator.h"
#include "scoreSystem.h"
#include "randomGenerator.h"
#include "error.h"
#include "GString.h"
#define frameRate(stepsToFall) 20 + 70 * (1 - (stepsToFall % 4))
struct score_sys {
	GString 	score_gstr;
	GString 	level_gstr;
	unsigned int	score;
	unsigned char 	level;
};

typedef struct Game {
	GE		 GE;
	Fontman 	 font;
	struct score_sys scoresys;
	Piece 		 *piece;
	Piece  		 *masterPieces;
	int 		 (*Map)[MAP_X];
} Game;

SDL_Texture *gameOverHandler(GE mainGE);
void scoreHandler(struct score_sys *scoresys, int moreScore);
void score_sys_destroy(struct score_sys *scoresys);
void GE__Renderer(GE mainGE, int Map[MAP_Y][MAP_X]);
Game *Game__Create();
void Game__Destroy(Game *self);
Game Game__Init();
#endif //CETRAMINOS_H
