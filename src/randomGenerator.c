#include "randomGenerator.h"
#include <stdlib.h>
#include <stdio.h>
int *numberGenerator(int previousNumber[RANDOM_BUFFER])
{
	int midNumber[17];
	for (int i = 15; i> -1; i--){
		midNumber[i+1] = previousNumber[i];
	};
	midNumber[0] = midNumber[9] ^ midNumber[7];
	for (int i = 0; i < 16; i++){
		previousNumber[i] = midNumber[i];
	}; 
	return previousNumber;
}
int nextPiece(int previousNumber[RANDOM_BUFFER])
{
	int result;
	int *randomGeneratedNumber = numberGenerator(previousNumber);
	for (int i = 0; i < 4; i++){
		result = result ^ randomGeneratedNumber[i]; 		
	};
	return result;
}
