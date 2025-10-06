#include "backendPieces.h"
#define MATRIX_FROM_ALL_VECTORS (Vector[2]){piece->xVector,piece->yVector}
#define SPINNING_MATRIX (Vector[2]){(Vector){0,1},(Vector){-1,0}}
void changePiece(Piece *masterPieces, Piece *piece, int number)
{
	piece->typeOfPiece = masterPieces[number].typeOfPiece;
	for (int i = 0; i < 3; i++)
		piece->AllVectors[i] = masterPieces[number].AllVectors[i];
	piece->xVector = (Vector) {1, 0};
	piece->yVector = (Vector) {0, 1};

}
void populateWithGivenNumber(int Map[MAP_Y][MAP_X], Piece *piece, int numberToPopulate)
{	
	Vector resultVector;
	for (int i = 0; i < 4; i++){
		resultVector = matrixMultiplication(MATRIX_FROM_ALL_VECTORS, piece->AllVectors[i]);
		Map[piece->bendPoint.y + resultVector.y][piece->bendPoint.x + resultVector.x] = numberToPopulate;
	};
} 
Vector matrixMultiplication(Vector matrix[2], Vector vector)
{
	Vector resultVector;
	resultVector = (Vector) {matrix[0].x * vector.x + matrix[1].x * vector.y, matrix[0].y * vector.x + matrix[1].y * vector.y};

	return resultVector;
};
void spinPiece(int Map[MAP_Y][MAP_X], Piece *masterPieces, Piece *piece)
{
	populateWithGivenNumber(Map, piece, 0);

	Vector tmpxVector;
	Vector tmpyVector;

	// Verification step
	tmpxVector = matrixMultiplication(SPINNING_MATRIX, piece->xVector);
	tmpyVector= matrixMultiplication(SPINNING_MATRIX, piece->yVector);
	Vector tmp_matrixFromAllVectors[2];
       	tmp_matrixFromAllVectors[0] = tmpxVector;
       	tmp_matrixFromAllVectors[1] = tmpyVector;
	Vector resultVector;

	for (int i = 0; i < 4; i++){
		resultVector = matrixMultiplication(tmp_matrixFromAllVectors, piece->AllVectors[i]);
		if (Map[piece->bendPoint.y + resultVector.y][piece->bendPoint.x + resultVector.x] % 2 == 1){
			//piece->xVector = tmpxVector;
			//piece->yVector = tmpyVector;
			return;
		}
	} 
	// If succeded
	piece->xVector = tmpxVector;
	piece->yVector = tmpyVector;
	populateWithGivenNumber(Map, piece, PIECE_LIVE_ID);
}

int isTheMovementValid(int Map[MAP_Y][MAP_X], Piece *piece, int playerMovement, int isFalling)
{
	Vector resultVector;
	for (int i = 0; i < 4; i++){
		resultVector = matrixMultiplication(MATRIX_FROM_ALL_VECTORS, piece->AllVectors[i]);
		if (Map[piece->bendPoint.y + resultVector.y + isFalling][piece->bendPoint.x + resultVector.x + playerMovement] % 2 == 1){	
			if (Map[piece->bendPoint.y + resultVector.y + isFalling][piece->bendPoint.x + resultVector.x] % 2 == 1)
				return NO_MORE_VALID;
			else 
				return FALLYES_SIDESNO;
		};
	};
	return VALID;
}
int pieceMovement(int Map[MAP_Y][MAP_X], Piece *masterPieces, Piece *piece, int playerMovement, int isFalling, bool isFallingFast, int previousNumber[RANDOM_BUFFER])
{
	int score = 0;
	int isValid = isTheMovementValid(Map, piece, playerMovement, isFalling);
	if (isValid == VALID || (isValid == FALLYES_SIDESNO && isFalling == 1)){
		populateWithGivenNumber(Map, piece, 0);		
			if (isFallingFast) {
				while (isTheMovementValid(Map, piece, playerMovement, 1) != NO_MORE_VALID){
					piece->bendPoint.y += 1;	
				};
			} else if (isFalling) {
					piece->bendPoint.y += 1;	
			};
		if (isValid == VALID)
			piece->bendPoint.x += playerMovement;	
		populateWithGivenNumber(Map, piece, PIECE_LIVE_ID);		
	} else if (isValid == NO_MORE_VALID){
		populateWithGivenNumber(Map, piece, PIECE_DEATH_ID);		
		score = scoreAndCleanMatrix(Map);
		piece->bendPoint = (Point) {SPAWN_X_LOCATION, SPAWN_Y_LOCATION};	
		if (isTheMovementValid(Map, piece, playerMovement, isFalling) == NO_MORE_VALID)
			return GAME_OVER_ID;
		int randomNumber = nextPiece(previousNumber);
		changePiece(masterPieces, piece, (randomNumber % 5));
		randomNumber = nextPiece(previousNumber);
		piece->isToRight = randomNumber % 2;
		piece->xVector = (Vector) {1 - 2 * piece->isToRight, 0};
		piece->yVector = (Vector) {0, 1};
		populateWithGivenNumber(Map, piece, PIECE_LIVE_ID);		
	};
	return score;

}
