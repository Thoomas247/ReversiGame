#pragma once

#include "GameOptions.h"
#include "Vec2.h"

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
* Calls GameBoard_calculateValidMoves() if it has not been called since last move.
*/
BOOL GameBoard_isValidMove(Vec2 coords);

/*
* Applies the given move to the board.
* Does not check for validity (call GameBoard_isValidMove() first)
*/
void GameBoard_playMove(Vec2 coords);

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