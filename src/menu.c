#include "menu.h"
#define select_toStart_ButtonXPosition 300
#define select_toEnd_ButtonXPosition 800
void menu(GE *mainGE, Piece* masterPieces, Piece *piece, bool *gameQuit, const Uint8* keys, int randomNumber[RANDOM_BUFFER]){
	unsigned int deltaTime, currentTime = 0, lastFrameTime = SDL_GetTicks();
	bool endMenu = false; 

	SDL_Rect selectRect = (SDL_Rect) {300, 500, select_toStart_ButtonXPosition, 200};
	SDL_Rect startButton = (SDL_Rect) {325, 525, 250, 150};
	SDL_Rect exitButton = (SDL_Rect) {select_toEnd_ButtonXPosition + 25, 525, 250, 150};
	SDL_Rect textRect = (SDL_Rect) {325, 525, 250, 150};
	SDL_Texture *startTextTexture = createTextTexture(mainGE, "Start Game");
	SDL_Texture *exitTextTexture = createTextTexture(mainGE, "Exit");
	while (!endMenu){
		nextPiece(randomNumber);
		while (SDL_PollEvent(&mainGE->Event)){
			if(mainGE->Event.type == SDL_QUIT){
				*gameQuit = true;	
			};
		};

		SDL_SetRenderDrawColor(mainGE->Renderer, 0, 0, 0, 255);
		SDL_RenderClear(mainGE->Renderer);


		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastFrameTime;
		if (deltaTime > 1000) {
			for (int i = 0; i < 100; i++)
				nextPiece(randomNumber);

			SDL_RenderClear(mainGE->Renderer);
			SDL_SetRenderDrawColor(mainGE->Renderer, 100, 100, 100, 100);
			SDL_RenderFillRect(mainGE->Renderer, &selectRect);
			SDL_SetRenderDrawColor(mainGE->Renderer, 255, 255, 255, 100);
			SDL_RenderFillRect(mainGE->Renderer, &startButton);
			SDL_RenderFillRect(mainGE->Renderer, &exitButton);
			SDL_RenderCopy(mainGE->Renderer, startTextTexture, NULL, &startButton);
			SDL_RenderCopy(mainGE->Renderer, exitTextTexture, NULL, &exitButton);
			SDL_RenderPresent(mainGE->Renderer);
		} else {
			nextPiece(randomNumber);
			SDL_Delay(10);
		};
		if (keys[SDL_SCANCODE_L]){
			selectRect.x = select_toEnd_ButtonXPosition;
		};
		if (keys[SDL_SCANCODE_H]){
			selectRect.x = select_toStart_ButtonXPosition;
		};
		if (keys[SDL_SCANCODE_RETURN] && selectRect.x == select_toStart_ButtonXPosition){
			endMenu == true;

			SDL_DestroyTexture(startTextTexture);
			SDL_DestroyTexture(exitTextTexture);
			*piece = masterPieces[nextPiece(randomNumber) % 5];
			piece->xVector = (Vector) {1 - 2 * (nextPiece(randomNumber) % 2), 0};
			piece->yVector = (Vector) {0, 1};
			piece->bendPoint = (Point) {6, 5};

			break;
		} else if (keys[SDL_SCANCODE_RETURN] && selectRect.x == 800){
			*gameQuit = true;
			endMenu = true;
		};
	};
}
