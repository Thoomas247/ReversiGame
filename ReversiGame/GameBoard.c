#include "GameBoard.h"

#include <stdio.h>

#include "GameOptions.h"
#include "GameState.h"

static char s_Board[BOARD_WIDTH][BOARD_WIDTH];
static char s_CurrentTurn;

void GameBoard_create()
{
	/* clear board */
	int x;
	int y;
	for (x = 0; x < BOARD_WIDTH; x++)
	{
		for (y = 0; y < BOARD_WIDTH; y++)
		{
			s_Board[x][y] = EMPTY_MARKER;
		}
	}

	/* add starting pieces */
	const int halfBoardWidth = BOARD_WIDTH / 2;
	s_Board[halfBoardWidth - 1][halfBoardWidth - 1] = WHITE_PIECE;
	s_Board[halfBoardWidth][halfBoardWidth - 1] = BLACK_PIECE;
	s_Board[halfBoardWidth - 1][halfBoardWidth] = BLACK_PIECE;
	s_Board[halfBoardWidth][halfBoardWidth] = WHITE_PIECE;

	/* set white to start first */
	s_CurrentTurn = WHITE_PIECE;
}

void GameBoard_print()
{
	/* print column numbers */
	printf(" ");

	int i;
	for (i = 0; i < BOARD_WIDTH; i++)
	{
		printf(" %d", i);
	}

	printf("\n");

	int x;
	int y;
	for (y = 0; y < BOARD_WIDTH; y++)
	{
		printf("%d ", y);
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			printf("%c ", s_Board[x][y]);
		}
		printf("\n");
	}
}

BOOL GameBoard_isValidMove(MoveCoords coords)
{
	/* if move is outside of bounds, return early*/
	if (coords.x < 0 || coords.x >= BOARD_WIDTH || coords.y < 0 || coords.y >= BOARD_WIDTH)
		return FALSE;

	return TRUE;
}

void GameBoard_playMove(MoveCoords coords)
{
	s_Board[coords.x][coords.y] = s_CurrentTurn;
}

void GameBoard_save()
{
	GameState_save(s_CurrentTurn, &s_Board[0][0]);
}

void GameBoard_undo()
{
	GameState_loadPrevious(&s_CurrentTurn, &s_Board[0][0]);
}

void GameBoard_swapTurn()
{
	if (s_CurrentTurn == WHITE_PIECE)
		s_CurrentTurn = BLACK_PIECE;
	else
		s_CurrentTurn = WHITE_PIECE;
}

char GameBoard_getTurn()
{
	return s_CurrentTurn;
}
