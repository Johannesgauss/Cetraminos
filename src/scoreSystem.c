#include "scoreSystem.h"
int scoreAndCleanMatrix(int Map[MAP_Y][MAP_X])
{
	int score = 0;
	int willRemoveLowerLayer = 0;
	for (int l = 0; l < 4; l++){
		for (int j = MAP_Y-2; j > 1; j--){
			for (int i = 1; i < MAP_X-1; i++){
				//printf("i: %i && ", i);
				//printf("MAP %i ", Map[j][i]);
				if (Map[j][i] == 0)
					continue;
				else
					willRemoveLowerLayer++;
			};
			//printf("\n");
			if(willRemoveLowerLayer == MAP_X-2){
				for (int k = j; k > 1; k--){
					for (int i = 1; i < MAP_X-1; i++){
						//if (Map[j][i] == 1)
						Map[k][i] = Map[k-1][i];
					/*	printf("i: %i && ", i);
						printf("MAP %i ", Map[k][i]);
						printf("NEW %i ", Map[k-1][i]); */
						score++;
					};
				};
			};
			willRemoveLowerLayer = 0;
		};
	};
	return score;
};
