#pragma once

#include "GameOptions.h"

typedef struct MoveCoords
{
	int x;
	int y;
} MoveCoords;

/*
* Creates the initial game board.
*/
void GameBoard_create();

/*
* Prints the board to the output window.
*/
void GameBoard_print();

/*
* Returns whether the given move is a valid move.
*/
BOOL GameBoard_isValidMove(MoveCoords coords);

/*
* Applies the given move to the board.
* Does not check for validity (call GameBoard_isValidMove() first)
*/
void GameBoard_playMove(MoveCoords coords);

/*
* Saves the current board.
*/
void GameBoard_save();

/*
* Reverts to the last saved game board.
*/
void GameBoard_undo();

/*
* Changes who's turn it is.
*/
void GameBoard_swapTurn();

/*
* Returns either WHITE_PIECE or BLACK_PIECE to indicate who's turn it is.
*/
char GameBoard_getTurn();