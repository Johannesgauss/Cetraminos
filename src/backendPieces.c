#include "backendPieces.h"
#define PIECE_LIVE_ID piece->typeOfPiece
#define PIECE_DEATH_ID piece->typeOfPiece+1
#define MATRIX_FROM_ALL_VECTORS (Vector[2]){piece->xVector,piece->yVector}
#define SPINNING_MATRIX (Vector[2]){(Vector){0,1},(Vector){-1,0}}
#define RESPAWN_DELAY 0
static inline void populateWithGivenNumber(Piece *piece, int Map[MAP_Y][MAP_X], int numberToPopulate);
static inline Vector matrixMultiplication(Vector matrix[2], Vector vector);
static int isTheMovementValid(Piece *piece, int Map[MAP_Y][MAP_X], int playerMovement, int isFalling);

static inline void populateWithGivenNumber(Piece *piece, int Map[MAP_Y][MAP_X], int numberToPopulate)
{	
	Vector resultVector;
	for (int i = 0; i < 4; i++){
		resultVector = matrixMultiplication(MATRIX_FROM_ALL_VECTORS, piece->AllVectors[i]);
		Map[piece->bendPoint.y + resultVector.y][piece->bendPoint.x + resultVector.x] = numberToPopulate;
	};
} 

static inline Vector matrixMultiplication(Vector matrix[2], Vector vector)
{
	Vector resultVector;
	resultVector = (Vector) {matrix[0].x * vector.x + matrix[1].x * vector.y, matrix[0].y * vector.x + matrix[1].y * vector.y};

	return resultVector;
}

static int isTheMovementValid(Piece *piece, int Map[MAP_Y][MAP_X], int playerMovement, int isFalling)
{ 
	int result = VALID;
	Vector resultVector;
	int i = 0; while (i < 4 && result == VALID){
		resultVector = matrixMultiplication(MATRIX_FROM_ALL_VECTORS, piece->AllVectors[i]);
		if (Map[piece->bendPoint.y + resultVector.y + isFalling][piece->bendPoint.x + resultVector.x + playerMovement] % 2 == 1){
			if (Map[piece->bendPoint.y + resultVector.y + 1][piece->bendPoint.x + resultVector.x] % 2 == 1)
				result = NO_MORE_VALID;
			else 
				result = FALLYES_SIDESNO;
		};
		i++;
	};
	return result;
}

void Piece__change(Piece *piece, Piece *masterPieces, int number)
{
	piece->typeOfPiece = masterPieces[number].typeOfPiece;
	for (int i = 0; i < 4; i++)
		piece->AllVectors[i] = masterPieces[number].AllVectors[i];
	piece->xVector = (Vector) {1, 0};
	piece->yVector = (Vector) {0, 1};
}

void Piece__spin(Piece *piece, int Map[MAP_Y][MAP_X])
{
	// Verification step
	Vector tmpxVector;
	Vector tmpyVector;

	tmpxVector = matrixMultiplication(SPINNING_MATRIX, piece->xVector);
	tmpyVector= matrixMultiplication(SPINNING_MATRIX, piece->yVector);
	Vector tmp_matrixFromAllVectors[2];
       	tmp_matrixFromAllVectors[0] = tmpxVector;
       	tmp_matrixFromAllVectors[1] = tmpyVector;
	Vector resultVector;

	for (int i = 0; i < 4; i++){
		resultVector = matrixMultiplication(tmp_matrixFromAllVectors, piece->AllVectors[i]);
		if (Map[piece->bendPoint.y + resultVector.y][piece->bendPoint.x + resultVector.x] % 2 == 1)
			return;
	}; 
	
	// If succeded
	populateWithGivenNumber(piece, Map, 0);
	piece->xVector = tmpxVector;
	piece->yVector = tmpyVector;
	populateWithGivenNumber(piece, Map, PIECE_LIVE_ID);
}

// Piece__movement

static inline int nextUnrepeteadPiece(int *previousNumber)
{
	static int bag[7] = {0,0,0,0,0,0,0};
	static unsigned char bagIndex = 0;
	int result;
	bool endLoop = false; do {
		bag[bagIndex] = nextPiece(previousNumber);
		int i = 0; while (i < bagIndex-1 && bag[bagIndex] != bag[i]) i++;
		if (i >= bagIndex-1 && (bagIndex == 0 || bag[bagIndex-1] != bag[bagIndex])){
			endLoop = true;
			result = bag[bagIndex];
			bagIndex = (bagIndex + 1) % 7;		
		};
	/*	i = 0; do {
			printf("%i ", bag[i]);
			i++;
		} while (i < bagIndex); puts("");*/
	} while (!endLoop); 
	//printf("result is: %i\n", result);
       	return result;
}

int Piece__movement(Piece *piece, 
		  int Map[MAP_Y][MAP_X],
		  Piece *masterPieces,
	       	  int playerMovement,
		  int isFalling,
		  bool isDropping,
		  int previousNumber[RANDOM_BUFFER],
		  void (*delay)(unsigned int))
{
	int score = 0;
	int isValid = isTheMovementValid(piece, Map, playerMovement, isFalling);
	if (isValid == VALID){
		populateWithGivenNumber(piece, Map, 0);		

		piece->bendPoint.x += playerMovement;	
		piece->bendPoint.y += isFalling;	

		//isValid = isTheMovementValid(piece, Map, 0, 1);
		while (isDropping && isTheMovementValid(piece, Map, 0, 1) != NO_MORE_VALID){
			piece->bendPoint.y += 1;
			//isValid = isTheMovementValid(piece, Map, 0, 1);
		};
		
		populateWithGivenNumber(piece, Map, PIECE_LIVE_ID);		
	} else if (isValid == FALLYES_SIDESNO && isFalling == 1){
		populateWithGivenNumber(piece, Map, 0);		
		isValid = isTheMovementValid(piece, Map, 0, 1);
		if (isValid != NO_MORE_VALID) 
			piece->bendPoint.y += 1;	
		populateWithGivenNumber(piece, Map, PIECE_LIVE_ID);		
	};
       	if (isValid == NO_MORE_VALID){
		populateWithGivenNumber(piece, Map, PIECE_DEATH_ID);		
		delay(RESPAWN_DELAY);
		piece->bendPoint = (Point) {SPAWN_X_LOCATION, SPAWN_Y_LOCATION};	
		score = scoreAndCleanMatrix(Map);

		if (isTheMovementValid(piece, Map, playerMovement, 0) == NO_MORE_VALID)
			return GAME_OVER_ID;

		int randomNumber; do{
			randomNumber = nextUnrepeteadPiece(previousNumber);
		} while(randomNumber == piece->typeOfPiece / 2 -1);
		printf("randomNumber is: %i\n", randomNumber);
		Piece__change(piece, masterPieces, randomNumber);

		populateWithGivenNumber(piece, Map, PIECE_LIVE_ID);		
	};
	return score;

}
