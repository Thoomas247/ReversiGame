#pragma once

#include "GameOptions.h"
#include "Vec2.h"

/*
* Creates the initial game board.
*/
void GameBoard_create();

/*
* Prints the board to the output window.
* Must call GameBoard_calculateValidMoves() first if valid moves should be shown.
*/
void GameBoard_print(BOOL showValidMoves);

/*
* Calculates all valid moves for this board configuration.
* Must be called before GameBoard_print(TRUE), GameBoard_getBestMove(), GameBoard_isValidMove() and GameBoard_playMove().
*/
void GameBoard_calculateValidMoves();

/*
* Returns the valid move with the highest strength.
* Must call GameBoard_calculateValidMoves() first.
*/
Vec2 GameBoard_getBestMove();

/*
* Returns whether the given move is a valid move.
* Must call GameBoard_calculateValidMoves() first.
*/
BOOL GameBoard_isValidMove(Vec2 coords);

/*
* Applies the given move to the board.
* Must call GameBoard_calculateValidMoves() first.
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