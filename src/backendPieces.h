#pragma once
#define MAP_X 10
#define MAP_Y 20
#define GAME_OVER_ID -1
#define SPAWN_X_LOCATION 4
#define SPAWN_Y_LOCATION 3
#include <stdio.h>
#include <stdbool.h>
#include "randomGenerator.h"
#include "scoreSystem.h"
#include <stdlib.h>
typedef struct Point{
	int x;
	int y;
} Point, Vector;
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
} Piece;
/* masterPieces is intended to be an array of Pieces, so a piece "object" "will be one element of this array"*/
void Piece__change(Piece *self, Piece *masterPieces, int number);
// A clockwise-only spin
void Piece__spin(Piece *self, int Map[MAP_Y][MAP_X]);
// It handles basically all aspects of piece: if it can go to right or left, if it'll fall / drop. When the pieces "dies", what actually happens is that self changes from the death position to SPAWN_X_LOCATION and SPAWN_Y_LOCATION after waiting some time. That's why a delay function is needed!
int Piece__movement(Piece *self, 
	   int Map[MAP_Y][MAP_X], 
	   Piece *masterPieces,
	   int playerMovement,
	   int isFalling,
	   bool isDropping,
	   void (*delay)(unsigned int));
