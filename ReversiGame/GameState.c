#include "GameState.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static GameState* s_pCurrentGameState = NULL;

/*
* Helper function used by freeGameStates() to recursively free game states.
*/
static void freeGameStatesRecursive(GameState* state)
{
	if (!state)
		return;

	/* free all previous states first */
	freeGameStatesRecursive(state->pLastState);

	free(state);
}

/*
* Helper function used to copy game boards.
*/
static void copyBoard(char* dst, const char* src)
{
	memcpy(dst, src, sizeof(char) * BOARD_WIDTH * BOARD_WIDTH);
}

void saveGameState(char turn, const char* pBoard)
{
	/* early return if board is NULL */
	if (!pBoard)
		return;

	/* allocate space for the game state */
	GameState* lastState = s_pCurrentGameState;
	s_pCurrentGameState = (GameState*)calloc(1, sizeof(GameState));

	/* check for allocation success */
	if (!s_pCurrentGameState)
	{
		printf("An error occured: Failed to allocate memory!");
		s_pCurrentGameState = lastState;
	}

	/* save the board */
	else
	{
		s_pCurrentGameState->turn = turn;
		copyBoard(&s_pCurrentGameState->board[0][0], pBoard);
		s_pCurrentGameState->pLastState = lastState;
	}
}

void freeGameStates()
{
	freeGameStatesRecursive(s_pCurrentGameState);
}

void loadLastGameState(char* pTurn, char* pBoard)
{
	GameState* pLastState = s_pCurrentGameState->pLastState;

	/* if there is no last state, do not modify turn or board */
	if (!pLastState)
		return;

	*pTurn = pLastState->turn;
	copyBoard(pBoard, &pLastState->board[0][0]);

	/* free the current state and assign the last state as the new current state */
	free(s_pCurrentGameState);
	s_pCurrentGameState = pLastState;
}
