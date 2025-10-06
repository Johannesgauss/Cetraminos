#include <stdio.h>
#include <stdbool.h>
#include "randomGenerator.h"
#include "scoreSystem.h"
#define NUMBER_OF_PIECES 4
#define PIECE_LIVE_ID piece->typeOfPiece+2*piece->isToRight
#define PIECE_DEATH_ID piece->typeOfPiece+2*piece->isToRight+1
#define GAME_OVER_ID -1
#define SPAWN_X_LOCATION 4
#define SPAWN_Y_LOCATION 3
typedef struct Point{
	int x;
	int y;
} Point;
typedef Point Vector;
typedef enum MOVEMENT_VALIDNESS{
	NO_MORE_VALID,
	VALID,
	FALLYES_SIDESNO,
} MOVEMENT_VALIDNESS;
typedef enum TYPE_OF_PIECES{
	PIECE_J_ID = 2,
	PIECE_L_ID = 4,
	PIECE_S_ID = 6,
	PIECE_Z_ID = 8,
	PIECE_I_ID = 10,
	PIECE_T_ID = 12,
	PIECE_O_ID = 14
} TYPE_OF_PIECES;
typedef struct Piece{
	Vector	AllVectors[4];
	int	typeOfPiece;
	Vector	xVector;
	Vector	yVector;
	Point	bendPoint;
	int	isToRight;
} Piece;
void changePiece(Piece *masterPieces, Piece *piece, int number);
void populateWithGivenNumber(int Map[MAP_Y][MAP_X], Piece *piece, int numberToPopulate);
Vector matrixMultiplication(Vector matrix[2], Vector vector);
void spinPiece(int Map[MAP_Y][MAP_X], Piece *masterPieces, Piece *piece);
int isTheMovementValid(int Map[MAP_Y][MAP_X], Piece *piece, int playerMovement, int isFalling);
int pieceMovement(int Map[MAP_Y][MAP_X], Piece *masterPiece, Piece *piece, int playerMovement, int isFalling, bool isFallingFast,int previousNumber[RANDOM_BUFFER]);

