#include "randomGenerator.h"
static int previousNumber[RANDOM_BUFFER] = {1, 31, 51, 101, 37, 29, 19, 202, 81, 53, 12, 73, 16, 195, 92};
void fill_random() {
	/*puts("A0");
	FILE *f = fopen("/dev/urandom", "rb");  // use urandom instead of random

	if (!f) {
		perror("Failed to open random source");
		exit(1);
	}

#include <stdlib.h>
#include <stdio.h>

	puts("A1");
	size_t read = fread(previousNumber, sizeof(unsigned int), RANDOM_BUFFER, f);

	if (read != RANDOM_BUFFER) {
		perror("Failed to read enough random data");
		fclose(f);
		exit(1);
	}

	puts("A2");
	fclose(f);

	for (unsigned char i = 0; i < RANDOM_BUFFER; i++) {
		printf("B%i\n", i);
		printf("%i\n", previousNumber[i]);
	}
	puts("A3");
	*/
}
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
