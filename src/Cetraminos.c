#pragma once
#include "Cetraminos.h"
SDL_Texture *gameOverHandler(GE *mainGE)
{
	SDL_Texture *gameOverTexture = createTextTexture(mainGE, "GAME OVER!");
	SDL_Rect gameOverRect =  (SDL_Rect) {100,100,HEIGHT_WINDOW_RESOLUTION-500,LENGTH_WINDOW_RESOLUTION-500};
	SDL_RenderCopy(mainGE->Renderer, gameOverTexture, NULL, &gameOverRect); 
	return gameOverTexture;
}

static inline struct score_sys scoreinit(GE *mainGE, unsigned long text_buffer_size, SDL_Rect score_rect)
{
	struct score_sys scoresys;

	scoresys.text_length = text_buffer_size;
	scoresys.text = malloc(sizeof(*scoresys.text) * scoresys.text_length); get_error(scoresys.text);
	scoresys.score = 0;
	sprintf(scoresys.text, "Score: %d", scoresys.score);
	scoresys.rect = score_rect; 
	scoresys.texture = createTextTexture(mainGE, scoresys.text);
	return scoresys;
}

void score_sys_destroy(struct score_sys *scoresys)
{
	SDL_DestroyTexture(scoresys->texture);
	free(scoresys->text);
}

void scoreHandler(struct score_sys *scoresys, GE *mainGE, int moreScore)
{
	if (moreScore > 0){
		scoresys->score += moreScore;
		// Unecessary, but if I can, I do
		snprintf(scoresys->text, scoresys->text_length, "Score: %d", scoresys->score);
		scoresys->texture = createTextTexture(mainGE, scoresys->text);
	};
	SDL_RenderCopy(mainGE->Renderer, scoresys->texture, NULL, &(scoresys->rect));
}

static SDL_Rect greenSquare[MAP_Y][MAP_X];
void GE__Renderer(GE *mainGE, int Map[MAP_Y][MAP_X])
{
	int Render[8][4] = { RENDER_ARRAY };
	for (int j = 5; j < MAP_Y; j++){
		for (int i = 0; i < MAP_X; i++){
			if (Map[j][i] != 0){
				int MapPointNum = (Map[j][i] == 1) ? 0 : (Map[j][i] - Map[j][i] % 2 - 2) / 2 + 1;
				SDL_SetRenderDrawColor(mainGE->Renderer, 
				Render[MapPointNum][0],
				Render[MapPointNum][1], 
				Render[MapPointNum][2], 
				Render[MapPointNum][3]);
				SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
			}
		}
	}
}

Game Game__Init()
{
	Game self;
	for (int j = 5; j < MAP_Y; j++){
		for (int i = 0; i < MAP_X; i++){
			greenSquare[j][i].x = 600 + 35 * i;
			greenSquare[j][i].y = 100 + 35 * (j-5);
			greenSquare[j][i].w = 35;
			greenSquare[j][i].h = 35;
		}
	};

	self.masterPieces = malloc(sizeof(*(self.masterPieces)) * 7);
	self.piece = malloc(sizeof(*(self.piece))); 
	self.masterPieces[0].typeOfPiece = PIECE_J_ID;
	self.masterPieces[0].AllVectors[0] = (Vector) {0, 0};
	self.masterPieces[0].AllVectors[1] = (Vector) {-1, 1};
	self.masterPieces[0].AllVectors[2] = (Vector) {0, -1};
	self.masterPieces[0].AllVectors[3] = (Vector) {0, 1};

	self.masterPieces[1].typeOfPiece = PIECE_L_ID;
	self.masterPieces[1].AllVectors[0] = (Vector) {0, 0};
	self.masterPieces[1].AllVectors[1] = (Vector) {1, 1};
	self.masterPieces[1].AllVectors[2] = (Vector) {0, -1};
	self.masterPieces[1].AllVectors[3] = (Vector) {0, 1};

	self.masterPieces[2].typeOfPiece = PIECE_S_ID;
	self.masterPieces[2].AllVectors[0] = (Vector) {0, 0};
	self.masterPieces[2].AllVectors[1] = (Vector) {0, -1};
	self.masterPieces[2].AllVectors[2] = (Vector) {-1, -1};
	self.masterPieces[2].AllVectors[3] = (Vector) {1, 0};

	self.masterPieces[3].typeOfPiece = PIECE_Z_ID;
	self.masterPieces[3].AllVectors[0] = (Vector) {0, 0};
	self.masterPieces[3].AllVectors[1] = (Vector) {0, -1};
	self.masterPieces[3].AllVectors[2] = (Vector) {1, -1};
	self.masterPieces[3].AllVectors[3] = (Vector) {-1, 0};

	self.masterPieces[4].typeOfPiece = PIECE_I_ID;
	self.masterPieces[4].AllVectors[0] = (Vector) {0, 0};
	self.masterPieces[4].AllVectors[1] = (Vector) {0, -1};
	self.masterPieces[4].AllVectors[2] = (Vector) {0, 1};
	self.masterPieces[4].AllVectors[3] = (Vector) {0, 2};

	self.masterPieces[5].typeOfPiece = PIECE_T_ID;
	self.masterPieces[5].AllVectors[0] = (Vector) {0, 0};
	self.masterPieces[5].AllVectors[1] = (Vector) {-1, 0};
	self.masterPieces[5].AllVectors[2] = (Vector) {1, 0};
	self.masterPieces[5].AllVectors[3] = (Vector) {0, 1};

	self.masterPieces[6].typeOfPiece = PIECE_O_ID;
	self.masterPieces[6].AllVectors[0] = (Vector) {0, 0};
	self.masterPieces[6].AllVectors[1] = (Vector) {0, 1};
	self.masterPieces[6].AllVectors[2] = (Vector) {1, 0};
	self.masterPieces[6].AllVectors[3] = (Vector) {1, 1};

	self.Map = malloc(sizeof(int)* MAP_X * (MAP_Y));	
	int tmpMap[MAP_Y][MAP_X] = {
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},

		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1},
	}; 
	
	memmove(self.Map, tmpMap, sizeof(tmpMap));
	Piece__change(self.piece, self.masterPieces, 0);
	self.GE = GE__Init();
	self.scoresys = scoreinit(&(self.GE), TEXT_BUFFER_SIZE, SCORE_RECT);

	return self;
}

Game *Game__Create()
{
	Game *self = malloc(sizeof(*self));
	*self = Game__Init();

	return self;
}

void Game__Destroy(Game *self)
{
	free(self->piece);
	free(self->masterPieces);
	free(self->Map);
	score_sys_destroy(&self->scoresys);
}
