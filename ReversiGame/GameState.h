#pragma once

#include "GameOptions.h"

typedef struct GameState
{
	char turn;
	char board[BOARD_WIDTH][BOARD_WIDTH];
	struct GameState* pLastState;
} GameState;

/*
* Saves the current board state.
* Used by undo functionality.
*/
void GameState_save(char turn, const char* pBoard);

/*
* Deletes all saved game states.
*/
void GameState_freeAll();

/*
* Loads the previous game state and deletes the current one.
* Used by undo functionality.
*/
void GameState_loadPrevious(char* turn, char* pBoard);