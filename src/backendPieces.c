#include "backendPieces.h"
#define SPAWN_X_LOCATION 4
#define SPAWN_Y_LOCATION 3
#define PIECE_LIVE_ID self->typeOfPiece
#define PIECE_DEATH_ID self->typeOfPiece+1
#define MATRIX_FROM_ALL_VECTORS (Vector[2]){self->xVector,self->yVector}
#define SPINNING_MATRIX (Vector[2]){(Vector){0,1},(Vector){-1,0}}
#define RESPAWN_DELAY 0
static inline void populateWithGivenNumber(Piece *self, int Map[MAP_Y][MAP_X], int numberToPopulate);
static inline Vector matrixMultiplication(Vector matrix[2], Vector vector);
static int isTheMovementValid(Piece *self, int Map[MAP_Y][MAP_X], int playerMovement, int isFalling);

static inline void populateWithGivenNumber(Piece *self, int Map[MAP_Y][MAP_X], int numberToPopulate)
{	
	Vector resultVector;
	for (int i = 0; i < 4; i++){
		resultVector = matrixMultiplication(MATRIX_FROM_ALL_VECTORS, self->AllVectors[i]);
		Map[self->bendPoint.y + resultVector.y][self->bendPoint.x + resultVector.x] = numberToPopulate;
	};
} 

static inline Vector matrixMultiplication(Vector matrix[2], Vector vector)
{
	Vector resultVector;
	resultVector = (Vector) {matrix[0].x * vector.x + matrix[1].x * vector.y, matrix[0].y * vector.x + matrix[1].y * vector.y};

	return resultVector;
}

static int isTheMovementValid(Piece *self, int Map[MAP_Y][MAP_X], int playerMovement, int isFalling)
{ 
	int result = VALID;
	Vector resultVector;
	int i = 0; while (i < 4 && result == VALID){
		resultVector = matrixMultiplication(MATRIX_FROM_ALL_VECTORS, self->AllVectors[i]);
		if (Map[self->bendPoint.y + resultVector.y + isFalling][self->bendPoint.x + resultVector.x + playerMovement] % 2 == 1){
			if (Map[self->bendPoint.y + resultVector.y + 1][self->bendPoint.x + resultVector.x] % 2 == 1)
				result = NO_MORE_VALID;
			else 
				result = FALLYES_SIDESNO;
		};
		i++;
	};
	return result;
}

void Piece__change(Piece *self, Piece *masterPieces, int number)
{
	self->typeOfPiece = masterPieces[number].typeOfPiece;
	for (int i = 0; i < 4; i++)
		self->AllVectors[i] = masterPieces[number].AllVectors[i];
	self->xVector = (Vector) {1, 0};
	self->yVector = (Vector) {0, 1};
}

void Piece__spin(Piece *self, int Map[MAP_Y][MAP_X])
{
	// Verification step
	Vector tmpxVector;
	Vector tmpyVector;

	tmpxVector = matrixMultiplication(SPINNING_MATRIX, self->xVector);
	tmpyVector= matrixMultiplication(SPINNING_MATRIX, self->yVector);
	Vector tmp_matrixFromAllVectors[2];
       	tmp_matrixFromAllVectors[0] = tmpxVector;
       	tmp_matrixFromAllVectors[1] = tmpyVector;
	Vector resultVector;

	for (int i = 0; i < 4; i++){
		resultVector = matrixMultiplication(tmp_matrixFromAllVectors, self->AllVectors[i]);
		if (Map[self->bendPoint.y + resultVector.y][self->bendPoint.x + resultVector.x] % 2 == 1)
			return;
	}; 
	
	// If succeded
	populateWithGivenNumber(self, Map, 0);
	self->xVector = tmpxVector;
	self->yVector = tmpyVector;
	populateWithGivenNumber(self, Map, PIECE_LIVE_ID);
}

static inline int nextUnrepeteadPiece()
{
	static int bag[7] = {0,0,0,0,0,0,0};
	static unsigned char bagIndex = 0;
	int result;
	bool endLoop = false; do {
		bag[bagIndex] = nextPiece();
		int i = 0; while (i <= bagIndex-1 && bag[bagIndex] != bag[i]) i++;
		if (i >= bagIndex-1/* && (bagIndex == 0 || bag[bagIndex-1] != bag[bagIndex])*/){
			endLoop = true;
			result = bag[bagIndex];
			bagIndex = (bagIndex + 1) % 7;		
		};
	} while (!endLoop); 
       	return result;
}

int Piece__movement(Piece *self, 
		  int Map[MAP_Y][MAP_X],
		  Piece *masterPieces,
	       	  int playerMovement,
		  int isFalling,
		  bool isDropping,
		  void (*delay)(unsigned int))
{
	int score = 0;
	int isValid = isTheMovementValid(self, Map, playerMovement, isFalling);
	if (isValid == VALID){
		populateWithGivenNumber(self, Map, 0);		

		self->bendPoint.x += playerMovement;	
		self->bendPoint.y += isFalling;	

		//isValid = isTheMovementValid(self, Map, 0, 1);
		while (isDropping && isTheMovementValid(self, Map, 0, 1) != NO_MORE_VALID){
			self->bendPoint.y += 1;
			//isValid = isTheMovementValid(self, Map, 0, 1);
		};
		
		populateWithGivenNumber(self, Map, PIECE_LIVE_ID);		
	} else if (isValid == FALLYES_SIDESNO && isFalling == 1){
		populateWithGivenNumber(self, Map, 0);		
		isValid = isTheMovementValid(self, Map, 0, 1);
		if (isValid != NO_MORE_VALID) 
			self->bendPoint.y += 1;	
		populateWithGivenNumber(self, Map, PIECE_LIVE_ID);		
	};
       	if (isValid == NO_MORE_VALID){
		populateWithGivenNumber(self, Map, PIECE_DEATH_ID);		
		delay(RESPAWN_DELAY);
		self->bendPoint = (Point) {SPAWN_X_LOCATION, SPAWN_Y_LOCATION};	
		score = scoreAndCleanMatrix(Map);

		if (isTheMovementValid(self, Map, playerMovement, 0) == NO_MORE_VALID)
			return GAME_OVER_ID;

		int randomNumber; do {
			randomNumber = nextUnrepeteadPiece();
		} while(randomNumber == self->typeOfPiece / 2 -1);
		Piece__change(self, masterPieces, randomNumber);

			populateWithGivenNumber(self, Map, PIECE_LIVE_ID);		
	};
	return score;

}
