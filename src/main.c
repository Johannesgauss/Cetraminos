#include "Cetraminos.h"
#include "menu.h"

Game *mainGame;
static inline int Piece__movementHandler(const unsigned char *keys, unsigned char *stepsToFall)
{
	// playerMovement
	int playerMovement = (keys[SDL_SCANCODE_L]) ? 1 : (keys[SDL_SCANCODE_H]) ? -1 : 0;
	// Spinning?
	if (keys[SDL_SCANCODE_J])
		Piece__spin(mainGame->piece, mainGame->Map);
	// Dropping?
	bool isDropping = false;
	if (keys[SDL_SCANCODE_K]){ 
		isDropping = true;
	};
	// Timer for falling
	static bool isFalling = true; 
	static unsigned char willFallNow = 0;
	*stepsToFall = (keys[SDL_SCANCODE_M]) ? 1 : 4;
	if (willFallNow >= *stepsToFall){
		isFalling = true;
		willFallNow = willFallNow % *stepsToFall;
	} else {
		isFalling = false;
		willFallNow++;
	};
	return Piece__movement(mainGame->piece, mainGame->Map, mainGame->masterPieces, playerMovement, isFalling, isDropping, &SDL_Delay);
}

void mainGAME()
{
//--------<hardcoded>
//-------------<Frame rate>
	unsigned int lastFrameTime = SDL_GetTicks();
	unsigned int deltaTime = 0;
	unsigned int currentTime;
//-------------</Frame rate>
	bool gameQuit = false;
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
//-------------<score>
	int moreScore = 0;
//-------------</score>
	unsigned char stepsToFall = 4;
	bool gameOver = false;


// --------------------------------------------
	mainGame = Game__Create();	

	SDL_Texture *gameOverTexture = NULL;
//--------</hardcoded>
RETURN_TO_MENU:
	mainGame->scoresys.score = 0;
	snprintf(mainGame->scoresys.text, mainGame->scoresys.text_length, "Score: %d", mainGame->scoresys.score);
	mainGame->scoresys.texture = createTextTexture(&(mainGame->GE), mainGame->scoresys.text);
	for (int j = 0; j < MAP_Y-1; j++){
		for (int i = 1; i < MAP_X-1; i++)
			mainGame->Map[j][i] = 0;
	};


	menu(&mainGame->GE, mainGame->masterPieces, mainGame->piece, &gameQuit, keys);
//-------------<music>
	extern Mix_Music *gMusic;
	if (!gameQuit){
		Mix_PlayMusic(gMusic, -1);
		//SDL_Delay(7*1000);
	};
//-------------</music>
	while (!gameQuit) {
		while (SDL_PollEvent(&mainGame->GE.Event)){
			if(mainGame->GE.Event.type == SDL_QUIT) 
				gameQuit = true;
		};
		currentTime = SDL_GetTicks(); 
		deltaTime = currentTime - lastFrameTime;
		nextPiece();
		if (deltaTime > frameRate(stepsToFall)) {
			if (!gameOver){
				moreScore = Piece__movementHandler(keys, &stepsToFall);
				if (moreScore == GAME_OVER_ID) 
					gameOver = true;
			};
			if (keys[SDL_SCANCODE_ESCAPE]){
				gameOver = false;
				goto RETURN_TO_MENU;
			};
			SDL_SetRenderDrawColor(mainGame->GE.Renderer, 0, 0, 0, 255);
			SDL_RenderClear(mainGame->GE.Renderer);
			scoreHandler(&mainGame->scoresys, &mainGame->GE, moreScore); 
			GE__Renderer(&mainGame->GE, mainGame->Map);

			if (gameOver)
				gameOverTexture = gameOverHandler(&mainGame->GE);
			SDL_RenderPresent(mainGame->GE.Renderer);
			
			lastFrameTime = SDL_GetTicks(); 
			deltaTime = 0;
		} else {
			SDL_Delay(20);
		};
	};	
	if (gameOverTexture)
		SDL_DestroyTexture(gameOverTexture);
	Game__Destroy(mainGame);
	Mix_FreeMusic(gMusic);
}

int main(int argc, char *argv[])
{
	mainGAME();
	return 0;
}
