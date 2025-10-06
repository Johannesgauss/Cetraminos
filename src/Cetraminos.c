#include "menu.h"
int main(int argc, char *argv[])
{

//-------------<hardcoded>
	Piece *masterPieces = (Piece *)malloc(sizeof(Piece)*7); 
	masterPieces[0].typeOfPiece = PIECE_J_ID;
	masterPieces[0].AllVectors[0] = (Vector) {0, 0};
	masterPieces[0].AllVectors[1] = (Vector) {-1, 1};
	masterPieces[0].AllVectors[2] = (Vector) {0, -1};
	masterPieces[0].AllVectors[3] = (Vector) {0, 1};

	masterPieces[1].typeOfPiece = PIECE_L_ID;
	masterPieces[1].AllVectors[0] = (Vector) {0, 0};
	masterPieces[1].AllVectors[1] = (Vector) {1, 1};
	masterPieces[1].AllVectors[2] = (Vector) {0, -1};
	masterPieces[1].AllVectors[3] = (Vector) {0, 1};

	masterPieces[2].typeOfPiece = PIECE_S_ID;
	masterPieces[2].AllVectors[0] = (Vector) {0, 0};
	masterPieces[2].AllVectors[1] = (Vector) {0, -1};
	masterPieces[2].AllVectors[2] = (Vector) {-1, -1};
	masterPieces[2].AllVectors[3] = (Vector) {1, 0};

	masterPieces[3].typeOfPiece = PIECE_Z_ID;
	masterPieces[3].AllVectors[0] = (Vector) {0, 0};
	masterPieces[3].AllVectors[1] = (Vector) {0, -1};
	masterPieces[3].AllVectors[2] = (Vector) {1, -1};
	masterPieces[3].AllVectors[3] = (Vector) {-1, 0};

	masterPieces[4].typeOfPiece = PIECE_I_ID;
	masterPieces[4].AllVectors[0] = (Vector) {0, 0};
	masterPieces[4].AllVectors[1] = (Vector) {0, -1};
	masterPieces[4].AllVectors[2] = (Vector) {0, 1};
	masterPieces[4].AllVectors[3] = (Vector) {0, 2};

	masterPieces[5].typeOfPiece = PIECE_T_ID;
	masterPieces[5].AllVectors[0] = (Vector) {0, 0};
	masterPieces[5].AllVectors[1] = (Vector) {-1, 0};
	masterPieces[5].AllVectors[2] = (Vector) {1, 0};
	masterPieces[5].AllVectors[3] = (Vector) {0, 1};


	masterPieces[6].typeOfPiece = PIECE_O_ID;
	masterPieces[6].AllVectors[0] = (Vector) {0, 0};
	masterPieces[6].AllVectors[1] = (Vector) {0, 1};
	masterPieces[6].AllVectors[2] = (Vector) {1, 0};
	masterPieces[6].AllVectors[3] = (Vector) {1, 1};

	int Map[MAP_Y][MAP_X] = {
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

;
	GE *mainGE = createGraphicEnvironment();
	
	SDL_Rect greenSquare[MAP_Y][MAP_X];

	for (int j = 0; j < MAP_Y; j++){
		for (int i = 0; i < MAP_X; i++){
			greenSquare[j][i].x = 600 + 35 * i;
			greenSquare[j][i].y = 100 + 35 * j;
			greenSquare[j][i].w = 35;
			greenSquare[j][i].h = 35;
		}
	};
	Piece *piece = (Piece *) malloc(sizeof(Piece));
	changePiece(masterPieces, piece, 0);
	bool gameQuit = false;
	unsigned int lastFrameTime = SDL_GetTicks();
	unsigned int deltaTime = 0;
	unsigned int currentTime;
	int playerMovement;
	int Validness = VALID;
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	bool isFalling = false;
	int willFallNow = 0;
	int score = 0;
	bool isFallingFast = false;
	int moreScore = 0;
	int randomNumber[RANDOM_BUFFER] = {1, 31, 51, 101, 37, 29, 19, 202, 81, 53, 12, 73, 16, 195, 92};



	bool gameOver = false;
	size_t scoreText_buffer;
       	char *scoreText = (char *) malloc(40);
	sprintf(scoreText, "Score: %d", score);
	SDL_Rect scoreRect =  (SDL_Rect) {100,100,200,100};
RETURN_TO_MENU:
	score = 0;
	sprintf(scoreText, "Score: %d", score);
	for (int j = 0; j < MAP_Y-1; j++){
		for (int i = 1; i < MAP_X-1; i++)
			Map[j][i] = 0;
	};
//-------------</hardcoded>
//-------------<menu>
	menu(mainGE, masterPieces, piece, &gameQuit, keys, randomNumber);
//-------------</menu>
//----------------------------<Text Texture creation>
	SDL_Texture *gameOverTexture = createTextTexture(mainGE, "GAME OVER!");
	SDL_Texture *scoreTexture = createTextTexture(mainGE, scoreText);
//----------------------------</Text Texture creation>
//-------------<Music system>
extern Mix_Music *gMusic;
	if (!gameQuit){
		Mix_PlayMusic( gMusic, -1 );
	//	SDL_Delay(7*1000);
	};
//-------------</Music system>
//-------------<Main loop beginning>
	int fallingVelocity = 4;
	while (!gameQuit) {
		while (SDL_PollEvent(&mainGE->Event)){
			if(mainGE->Event.type == SDL_QUIT) 
		gameQuit = true;
		};
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastFrameTime;


//----------------------------- <Random Number Generator>
		nextPiece(randomNumber);
//----------------------------- </Random Number Generator>
//----------------------------- <Keys handling>	
		if (!gameOver){
			if (keys[SDL_SCANCODE_L])
				playerMovement = 1;
			else if (keys[SDL_SCANCODE_H] == true)
				playerMovement = -1;
			else
				playerMovement = 0;
		};
		if (gameOver){
			SDL_Rect gameOverRect =  (SDL_Rect) {100,100,HEIGHT_WINDOW_RESOLUTION-500,LENGTH_WINDOW_RESOLUTION-500};
			SDL_RenderCopy(mainGE->Renderer, gameOverTexture, NULL, &gameOverRect);
			SDL_RenderPresent(mainGE->Renderer);
		};
		if (deltaTime > (20 + 80 * (1 - (fallingVelocity % 4)))) {
			//nextPiece(randomNumber);
			if (!gameOver){
					if (keys[SDL_SCANCODE_L]) playerMovement = 1; else if (keys[SDL_SCANCODE_H] == true) playerMovement = -1; else playerMovement = 0;
				if(keys[SDL_SCANCODE_J])
					spinPiece(Map, masterPieces, piece);
				if(keys[SDL_SCANCODE_K]) 
					isFallingFast = true;
				if (willFallNow >= fallingVelocity && !keys[SDL_SCANCODE_J] && !keys[SDL_SCANCODE_K]){
					isFalling = 1;
					willFallNow = willFallNow % fallingVelocity;
				} else {
					isFalling = false;
					 willFallNow++;
				};

			};
				// I need a better solution!
				if (keys[SDL_SCANCODE_ESCAPE]){
					gameOver = false;
					goto RETURN_TO_MENU;
				};
//----------------------------</Keys handling>
//----------------------------<Score system and PieceMovement>
			
			moreScore = pieceMovement(Map, masterPieces, piece, playerMovement, isFalling, isFallingFast, randomNumber);
			if (moreScore == GAME_OVER_ID) 
				gameOver = true;
			if (moreScore > 0){
				score += moreScore;
				// Unecessary, but if I can, I do
				scoreText_buffer = snprintf(NULL, 0, "Score: %d", score); if (scoreText_buffer <= 40) snprintf(scoreText, scoreText_buffer, "Score: %d", score);
				scoreTexture = createTextTexture(mainGE, scoreText);
			};
//----------------------------</Score system and PieceMovement>
			isFallingFast = false; // I gotta change this name later, this name is so counterintuitive!
//----------------------------Rendering loop
			SDL_SetRenderDrawColor(mainGE->Renderer, 0, 0, 0, 255);
			SDL_RenderClear(mainGE->Renderer);

			SDL_RenderCopy(mainGE->Renderer, scoreTexture, NULL, &scoreRect);
			for (int j = 0; j < MAP_Y; j++){
				for (int i = 0; i < MAP_X; i++){
					switch (Map[j][i]){
					case PIECE_L_ID:
						SDL_SetRenderDrawColor(mainGE->Renderer, 200, 100, 100, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_L_ID + 1:
						SDL_SetRenderDrawColor(mainGE->Renderer, 200, 100, 100, 100);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_J_ID:
						SDL_SetRenderDrawColor(mainGE->Renderer, 100, 0, 100, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_J_ID + 1:
						SDL_SetRenderDrawColor(mainGE->Renderer, 100, 0, 100, 100);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_S_ID:
						SDL_SetRenderDrawColor(mainGE->Renderer, 0, 255, 50, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_S_ID + 1:
						SDL_SetRenderDrawColor(mainGE->Renderer, 0, 255, 50, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_Z_ID:
						SDL_SetRenderDrawColor(mainGE->Renderer, 255, 255, 255, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_Z_ID + 1:
						SDL_SetRenderDrawColor(mainGE->Renderer, 255, 255, 255, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_I_ID:
						SDL_SetRenderDrawColor(mainGE->Renderer, 154, 137, 200, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_I_ID + 1:
						SDL_SetRenderDrawColor(mainGE->Renderer, 154, 137, 200, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_T_ID:
						SDL_SetRenderDrawColor(mainGE->Renderer, 255, 0, 0, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_T_ID + 1:
						SDL_SetRenderDrawColor(mainGE->Renderer, 255, 0, 0, 100);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_O_ID:
						SDL_SetRenderDrawColor(mainGE->Renderer, 100, 100, 150, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_O_ID + 1:
						SDL_SetRenderDrawColor(mainGE->Renderer, 100, 100, 150, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case 1:
						SDL_SetRenderDrawColor(mainGE->Renderer, 100, 100, 50, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					};
				}
			}
			lastFrameTime = SDL_GetTicks();
			deltaTime = 0;
			SDL_RenderPresent(mainGE->Renderer);
		} else {
			SDL_Delay(20);
		};
	};
	SDL_DestroyTexture(gameOverTexture);
	SDL_DestroyTexture(scoreTexture);
	free(scoreText);
	free(piece);
	free(masterPieces);
	Mix_FreeMusic(gMusic);
	destroyGraphicEnvironment(mainGE);
	return 0;
}
