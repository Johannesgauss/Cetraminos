#include "randomGenerator.h"
static int previousNumber[RANDOM_BUFFER] = {1, 31, 51, 101, 37, 29, 19, 202, 81, 53, 12, 73, 16, 195, 92};
int *numberGenerator()
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

int nextPiece()
{
	int result;
	int *randomGeneratedNumber = numberGenerator();
	for (int i = 0; i < 4; i++){
		result = result ^ randomGeneratedNumber[i]; 		
	};
	result = result % 7;
	return result;
}
