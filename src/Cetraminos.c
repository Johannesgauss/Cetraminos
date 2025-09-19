#include "menu.h"
int main(int argc, char *argv[])
{
RETURN_TO_MENU:

//-------------<hardcoded>
	Piece *masterPieces = (Piece *)malloc(sizeof(Piece)*5); 
	masterPieces[0].typeOfPiece = PIECE_L_ID;
	masterPieces[0].AllVectors[0] = (Vector) {0, 0};
	masterPieces[0].AllVectors[1] = (Vector) {-1, 0};
	masterPieces[0].AllVectors[2] = (Vector) {0, -1};
	masterPieces[0].AllVectors[3] = (Vector) {0, -2};

	masterPieces[1].typeOfPiece = PIECE_S_ID;
	masterPieces[1].AllVectors[0] = (Vector) {0, 0};
	masterPieces[1].AllVectors[1] = (Vector) {0, -1};
	masterPieces[1].AllVectors[2] = (Vector) {1, -1};
	masterPieces[1].AllVectors[3] = (Vector) {-1, 0};


	masterPieces[2].typeOfPiece = PIECE_I_ID;
	masterPieces[2].AllVectors[0] = (Vector) {0, 0};
	masterPieces[2].AllVectors[1] = (Vector) {0, -1};
	masterPieces[2].AllVectors[2] = (Vector) {0, 1};
	masterPieces[2].AllVectors[3] = (Vector) {0, 2};


	masterPieces[3].typeOfPiece = PIECE_T_ID;
	masterPieces[3].AllVectors[0] = (Vector) {0, 0};
	masterPieces[3].AllVectors[1] = (Vector) {-1, 0};
	masterPieces[3].AllVectors[2] = (Vector) {1, 0};
	masterPieces[3].AllVectors[3] = (Vector) {0, 1};


	masterPieces[4].typeOfPiece = PIECE_O_ID;
	masterPieces[4].AllVectors[0] = (Vector) {0, 0};
	masterPieces[4].AllVectors[1] = (Vector) {0, 1};
	masterPieces[4].AllVectors[2] = (Vector) {1, 0};
	masterPieces[4].AllVectors[3] = (Vector) {1, 1};

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
	GE *mainGE = createGraphicEnvironment();
	
	SDL_FRect greenSquare[MAP_Y][MAP_X];

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
	const bool *keys = SDL_GetKeyboardState(NULL);
	bool isFalling = false;
	int willFallNow = 0;
	int score = 0;
	bool isFallingFast = false;
	int moreScore = 0;
	int randomNumber[RANDOM_BUFFER] = {1, 31, 51, 101, 37, 29, 19, 202, 81, 53, 12, 73, 16, 195, 92};



	bool gameOver = false;
	char *scoreText = (char *) malloc(40);
	sprintf(scoreText, "Score: %d", score);
	SDL_FRect scoreRect =  (SDL_FRect) {100,100,200,100};
//-------------</hardcoded>

//-------------<menu>
	menu(mainGE, masterPieces, piece, &gameQuit, keys, randomNumber);
//-------------</menu>
//----------------------------<Text Texture creation>
	SDL_Texture *gameOverTexture = createTextTexture(mainGE, "GAME OVER!");
	SDL_Texture *scoreTexture = createTextTexture(mainGE, scoreText);
//----------------------------</Text Texture creation>
//-------------<Main loop beginning>
	int fallingVelocity = 4;
	while (!gameQuit) {
		while (SDL_PollEvent(&mainGE->Event)){
			if(mainGE->Event.type == SDL_EVENT_QUIT) 
		gameQuit = true;
		}
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastFrameTime;


//----------------------------- <Random Number Generator>
		nextPiece(randomNumber);
//----------------------------- </Random Number Generator>
//----------------------------- <Keys handling>

		if (keys[SDL_SCANCODE_L])
			playerMovement = 1;
		else if (keys[SDL_SCANCODE_H] == true)
			playerMovement = -1;
		else
			playerMovement = 0;
		if (deltaTime > (20 + 80 * (1 - (fallingVelocity % 4)))) {
			//nextPiece(randomNumber);

		if (keys[SDL_SCANCODE_L]) playerMovement = 1; else if (keys[SDL_SCANCODE_H] == true) playerMovement = -1; else playerMovement = 0;

			if(keys[SDL_SCANCODE_J])
				spinPiece(Map, masterPieces, piece);
			if(keys[SDL_SCANCODE_K]) 
				isFallingFast = true;
			if (willFallNow >= fallingVelocity){
				isFalling = 1;
				willFallNow = willFallNow % fallingVelocity;
				playerMovement = 0;
			} else {
				isFalling = false;
				 willFallNow++;
			};
			if (keys[SDL_SCANCODE_M])
				fallingVelocity = 1;
			else
				fallingVelocity = 4;

			// I need a better solution!
			//if (keys[SDL_SCANCODE_ESCAPE])
			//	goto RETURN_TO_MENU;
//----------------------------</Keys handling>
//----------------------------<Score system and PieceMovement>
			
			moreScore = pieceMovement(Map, masterPieces, piece, playerMovement, isFalling, isFallingFast, randomNumber);
			if (moreScore == GAME_OVER_ID) 
				gameOver = true;
			if (gameOver){
					SDL_FRect gameOverRect =  (SDL_FRect) {100,100,HEIGHT_WINDOW_RESOLUTION-500,LENGTH_WINDOW_RESOLUTION-500};
					SDL_RenderTexture(mainGE->Renderer, gameOverTexture, NULL, &gameOverRect);
			} else if (moreScore > 0){
				score += moreScore;
				sprintf(scoreText, "Score: %d", score);
				scoreTexture = createTextTexture(mainGE, scoreText);
			};
//----------------------------</Score system and PieceMovement>
			isFallingFast = false; // I gotta change this name later, this name is so counterintuitive!
//----------------------------Rendering loop
			SDL_SetRenderDrawColor(mainGE->Renderer, 0, 0, 0, 255);
			SDL_RenderClear(mainGE->Renderer);

			SDL_RenderTexture(mainGE->Renderer, scoreTexture, NULL, &scoreRect);
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
					case PIECE_L_ID + 2:
						SDL_SetRenderDrawColor(mainGE->Renderer, 100, 0, 100, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_L_ID + 3:
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
					case PIECE_S_ID + 2:
						SDL_SetRenderDrawColor(mainGE->Renderer, 255, 255, 255, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_S_ID + 3:
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
					case PIECE_I_ID + 2:
						SDL_SetRenderDrawColor(mainGE->Renderer, 0, 0, 255, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_I_ID + 3:
						SDL_SetRenderDrawColor(mainGE->Renderer, 0, 0, 255, 255);
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
					case PIECE_T_ID + 2:
						SDL_SetRenderDrawColor(mainGE->Renderer, 0, 255, 0, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_T_ID + 3:
						SDL_SetRenderDrawColor(mainGE->Renderer, 0, 255, 0, 100);
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
					case PIECE_O_ID + 2:
						SDL_SetRenderDrawColor(mainGE->Renderer, 100, 100, 150, 255);
						SDL_RenderFillRect(mainGE->Renderer, &greenSquare[j][i]);
						break;
					case PIECE_O_ID + 3:
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
	free(scoreText);
	free(piece);
	free(masterPieces);
	destroyGraphicEnvironment(mainGE);
	return 0;
}
