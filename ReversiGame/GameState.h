/*
* Thomas Amiouny (107527)
* Gonçalo Paiva	(106888)
*/

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "GameOptions.h"
#include "Vec2.h"

typedef struct GameState
{
	char turn;
	char board[BOARD_WIDTH][BOARD_WIDTH];
	struct GameState* pLastState;
	Vec2 move;
} GameState;

/*
* Saves the current board state and the move which was played in this state.
* Used by undo and save functionalities.
*/
void GameState_save(char turn, const char* pBoard, Vec2 move);

/*
* Outputs all board states and played moves to the file.
*/
void GameState_printToFile(const char* fileName);

/*
* Deletes all saved game states.
*/
void GameState_freeAll();

/*
* Loads the previous game state and deletes the current one.
* Used by undo functionality.
*/
void GameState_loadPrevious(char* turn, char* pBoard);

#endif /* GAMESTATE_H_ */