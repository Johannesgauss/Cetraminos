#include "Cetraminos.h"
#include "menu.h"

#include <time.h>

Game *mainGame;
static inline int Piece__movementHandler(const unsigned char *keys, unsigned char *falling_delay, unsigned char level)
{
	// playerMovement
	int playerMovement = (keys[SDL_SCANCODE_RIGHT]) ? 1 : (keys[SDL_SCANCODE_LEFT]) ? -1 : 0;
	// Spinning?
	if (keys[SDL_SCANCODE_UP])
		Piece__spin(mainGame->piece, mainGame->Map);
	// Dropping?
	bool isDropping = false;
	if (keys[SDL_SCANCODE_LCTRL])
		isDropping = true;
	// Timer for falling
	static bool isFalling = true; 
	static unsigned char willFallNow = 0;
	*falling_delay = (keys[SDL_SCANCODE_DOWN]) ? 1 : 4;
	if (willFallNow >= *falling_delay) {
		isFalling = true;
		willFallNow = willFallNow % *falling_delay;
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
	unsigned char falling_delay = 4;
	bool gameOver = false;
// --------------------------------------------
	bool game_over_happened = false;
	GString game_over_gstr;
	Fontman game_over_font;
// --------------------------------------------
	mainGame = Game__Create();	
//	fill_random();
//--------</hardcoded>
RETURN_TO_MENU:
	mainGame->scoresys.score = 0;

	mainGame->scoresys.level = 1;
	snprintf(mainGame->scoresys.score_gstr.string, mainGame->scoresys.score_gstr.buffer, "Score: %i", mainGame->scoresys.score);
	snprintf(mainGame->scoresys.level_gstr.string, mainGame->scoresys.level_gstr.buffer, "Level: %d", mainGame->scoresys.level);
	for (int j = 0; j < MAP_Y-1; j++){
		for (int i = 1; i < MAP_X-1; i++)
			mainGame->Map[j][i] = 0;
	};


	menu(mainGame->GE, mainGame->masterPieces, mainGame->piece, &gameQuit, keys);
//-------------<music>
	extern Mix_Music *gMusic;
	if (!gameQuit){
		Mix_PlayMusic(gMusic, -1);
		SDL_Delay(7*1000);
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
		if (deltaTime * pow(1.05, mainGame->scoresys.level - 1) > frameRate(falling_delay)) {
			if (!gameOver){
				moreScore = Piece__movementHandler(keys, &falling_delay, mainGame->scoresys.level);
				if (moreScore == GAME_OVER_ID) {
					gameOver = true;


					FILE *register_file = fopen("total_score.txt", "a"); 
					if (!register_file) {
						printf("Error opening file\n");
						return;
					};

					time_t now = time(NULL);
					struct tm *t = localtime(&now);

					char time_buffer[50];
					strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", t);

					char line_buffer[sizeof(time_buffer) + sizeof(mainGame->scoresys.score) + 4];
					snprintf(line_buffer, sizeof(line_buffer), "%s : %d, level: %d\n", time_buffer, mainGame->scoresys.score, mainGame->scoresys.level);
					fprintf(register_file, "\n%s", line_buffer);

					fclose(register_file);
				}
			};
			if (keys[SDL_SCANCODE_ESCAPE]){
				gameOver = false;
				goto RETURN_TO_MENU;
			};
			SDL_SetRenderDrawColor(mainGame->GE.Renderer, 0, 0, 0, 255);
			SDL_RenderClear(mainGame->GE.Renderer);
			scoreHandler(&mainGame->scoresys, moreScore); 
			GE__Renderer(mainGame->GE, mainGame->Map);

			if (gameOver) {
				if (!game_over_happened){
					// I don't need to remove them because OS will handle this memory after the game closes, but I want to do it myself anyway!
					// So, it's yet to be implemented this manual cleaning.
					// Updated: I've already done that!
					game_over_font = Fontman__Init(mainGame->GE, "./fonts/unifont-17.0.03.otf", 200, 0.5, (SDL_Color) {255, 0, 0, 255});
					game_over_gstr = GString__Create(mainGame->GE, game_over_font, 300, 400, "GAME OVER!", 20);
					game_over_happened = true;
				};
				GString__RenderCopy(game_over_gstr);
			};

				/*gameOverTexture = gameOverHandler(mainGame->GE);*/
			SDL_RenderPresent(mainGame->GE.Renderer);
			
			lastFrameTime = SDL_GetTicks(); 
			deltaTime = 0;
		} else {
			SDL_Delay(20);
		};
	};	
	if (game_over_happened) {
		GString__Destroy(game_over_gstr);
		Fontman__Destroy(game_over_font);
	}
	/*if (gameOverTexture)
		SDL_DestroyTexture(gameOverTexture);*/
	Game__Destroy(mainGame);
	Mix_FreeMusic(gMusic);
}

int main(int argc, char *argv[])
{
	mainGAME();

	return 0;
}
