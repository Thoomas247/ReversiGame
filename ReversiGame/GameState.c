/*
* Thomas Amiouny (107527)
* Gonçalo Paiva	(106888)
*/

#include "GameState.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* we want access to this variable to be restricted to GameState.c, so we declare it static */
static GameState* s_pCurrentGameState = NULL;

/*
* Helper function used by GameState_freeAll() to recursively free game states.
*/
static void freeGameStatesRecursive(GameState* pState)
{
	if (!pState)
		return;

	/* free all previous states first */
	freeGameStatesRecursive(pState->pLastState);

	free(pState);
}

/*
* Helper function used to copy game boards.
*/
static void copyBoard(char* pDst, const char* pSrc)
{
	memcpy(pDst, pSrc, sizeof(char) * BOARD_WIDTH * BOARD_WIDTH);
}

void GameState_save(char turn, const char* pBoard, Vec2 move)
{
	GameState* lastState;

	/* early return if board is NULL */
	if (!pBoard)
		return;

	/* allocate space for the game state */
	lastState = s_pCurrentGameState;
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
		s_pCurrentGameState->move = move;
	}
}

/*
* Recursively prints all game states to the file in order.
*/
static void printRecursive(GameState* pState, FILE* pFile)
{
	int x;
	int y;

	if (!pState) return;

	printRecursive(pState->pLastState, pFile);

	/* print column numbers */
	fprintf(pFile, "  ");

	for (x = 0; x < BOARD_WIDTH; x++)
	{
		fprintf(pFile, " %d", x);
	}

	fprintf(pFile, "\n");

	/* print grid */
	for (y = 0; y < BOARD_WIDTH; y++)
	{
		fprintf(pFile, " %d ", y);
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			fprintf(pFile, "%c ", pState->board[x][y]);
		}
		fprintf(pFile, "\n");
	}

	/* print the played move */
	fprintf(pFile, "(%d, %d)\n\n", pState->move.y, pState->move.x);
}

void GameState_printToFile(const char* fileName)
{
	FILE* pFile;

	if (!fileName) return;

	pFile = fopen(fileName, "w");

	/* exit if could not open the file */
	if (!pFile)
	{
		printf("Ocorreu um erro ao guardar o jogo!");
		return;
	}

	printRecursive(s_pCurrentGameState, pFile);

	fclose(pFile);
}

void GameState_freeAll()
{
	freeGameStatesRecursive(s_pCurrentGameState);
}

void GameState_loadPrevious(char* pTurn, char* pBoard)
{
	if (!s_pCurrentGameState)
		return;

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
