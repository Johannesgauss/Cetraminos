#include "Cetraminos.h"
#define SCORE_RECT (SDL_Rect){20, 100, 200, 100}
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

SDL_Texture *gameOverHandler(GE mainGE)
{
	SDL_Texture *gameOverTexture = createTextTexture(mainGE, "GAME OVER!");
	SDL_Rect gameOverRect =  (SDL_Rect) {100,100,HEIGHT_WINDOW_RESOLUTION-500,LENGTH_WINDOW_RESOLUTION-500};
	SDL_RenderCopy(mainGE.Renderer, gameOverTexture, NULL, &gameOverRect); 
	return gameOverTexture;
}

static inline struct score_sys scoreinit(GE mainGE, unsigned long text_buffer_size, SDL_Rect score_rect, Fontman font)
{
	struct score_sys scoresys;

	scoresys.score = 0;
	scoresys.level = 12;
	scoresys.score_gstr = GString__Create(mainGE, font, score_rect.x, score_rect.y, "sc", text_buffer_size);
	scoresys.level_gstr = GString__Create(mainGE, font, score_rect.x, score_rect.y + font.font_size, "level: 18", text_buffer_size);

	return scoresys;
}

void score_sys_destroy(struct score_sys *scoresys)
{
	GString__Destroy(scoresys->score_gstr);
}

void scoreHandler(struct score_sys *scoresys, int moreScore)
{
	if (moreScore > 0){
		scoresys->score += moreScore;
		// Unecessary, but if I can, I do
		snprintf(scoresys->score_gstr.string, scoresys->score_gstr.buffer, "Score: %d", scoresys->score);
		snprintf(scoresys->level_gstr.string, scoresys->level_gstr.buffer, "Level: %d", scoresys->level);
		if (scoresys->score / 500 > scoresys->level)
			scoresys->level++;
			// FIXME: MAGIC NUMBER!
	};
	GString__RenderCopy(scoresys->score_gstr);
	GString__RenderCopy(scoresys->level_gstr);
}

static SDL_Rect greenSquare[MAP_Y][MAP_X];
void GE__Renderer(GE mainGE, int Map[MAP_Y][MAP_X])
{
	int Render[8][4] = { RENDER_ARRAY };
	for (int j = 0; j < MAP_Y; j++){
		for (int i = 0; i < MAP_X; i++){
			if (Map[j][i] != 0){
				int MapPointNum = (Map[j][i] == 1) ? 0 : (Map[j][i] - Map[j][i] % 2 - 2) / 2 + 1;
				SDL_SetRenderDrawColor(mainGE.Renderer, 
				Render[MapPointNum][0],
				Render[MapPointNum][1], 
				Render[MapPointNum][2], 
				Render[MapPointNum][3]);
				SDL_RenderFillRect(mainGE.Renderer, &greenSquare[j][i]);
			}
		}
	}
}

Game Game__Init()
{
	Game self;
	for (int j = 0; j < MAP_Y; j++){
		for (int i = 0; i < MAP_X; i++){
			greenSquare[j][i].x = 600 + 35 * i;
			greenSquare[j][i].y = 100 + 35 * j;
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
		/*{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1}, */
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
	self.font = Fontman__Init(self.GE, "./fonts/unifont-17.0.03.otf", 80, 0.5, (SDL_Color) {255, 0, 0, 255});
	self.scoresys = scoreinit(self.GE, TEXT_BUFFER_SIZE, SCORE_RECT, self.font);

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
	Fontman__Destroy(self->font);
	free(self->piece);
	free(self->masterPieces);
	free(self->Map);
	GE__Destroy(self->GE);
	score_sys_destroy(&self->scoresys);
}
