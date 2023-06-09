/*
* Thomas Amiouny (107527)
* Gon�alo Paiva	(106888)
*/

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "GameOptions.h"
#include "Vec2.h"

/*
* Creates the initial game board.
*/
void GameBoard_create();

/*
* Returns the number of pieces of this type present on the board.
*/
int GameBoard_getPieceCount(char piece);

/*
* Prints the board to the output window.
* Must call GameBoard_calculateValidMoves() first if valid moves should be shown.
*/
void GameBoard_print(BOOL showValidMoves);

/*
* Calculates all valid moves for this board configuration.
* Must be called before GameBoard_print(TRUE), GameBoard_hasValidMoves(), GameBoard_getBestMove(), GameBoard_isValidMove() and GameBoard_playMove().
*/
void GameBoard_calculateValidMoves();

/* 
* Returns whether there are any valid moves for this turn.
* FALSE indicates that the game has ended.
*/
BOOL GameBoard_hasValidMoves();

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
* Saves the current board and the move which was played when the game was in this state.
*/
void GameBoard_save(Vec2 move);

/*
* Reverts to the last saved game board where it was the player's turn to play.
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

#endif /* GAMEBOARD_H_ */