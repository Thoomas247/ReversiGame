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
void saveGameState(char turn, const char* board);

/*
* Deletes all saved game states.
*/
void freeGameStates();

/*
* Loads the previous game state and deletes the current one.
* Used by undo functionality.
*/
void loadLastGameState(char* turn, char* board);