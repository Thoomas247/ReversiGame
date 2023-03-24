#include "GameBoard.h"

#include <stdio.h>

#include "GameOptions.h"
#include "GameState.h"

#define MAX_VALID_MOVES BOARD_WIDTH * BOARD_WIDTH

/*
* Struct representing a single valid move and the number of points it would give.
* Only visible within GameBoard.c.
*/
typedef struct ValidMove
{
	Vec2 coord;
	int points;
} ValidMove;

/*
* A list representing all valid moves for this turn.
* Only visible within GameBoard.c.
*/
typedef struct ValidMoveList
{
	ValidMove moves[MAX_VALID_MOVES];
	int count;
} ValidMoveList;

/* we want access to these variables to be restricted to GameBoard.c, so we declare them static */
static char s_Board[BOARD_WIDTH][BOARD_WIDTH];
static char s_CurrentTurn;
static ValidMoveList s_ValidMoves;

/*
* Helper function to check whether a coordinate is within the board.
*/
static BOOL isInBounds(Vec2 coords)
{
	if (coords.x < 0 || coords.x >= BOARD_WIDTH || coords.y < 0 || coords.y >= BOARD_WIDTH)
		return FALSE;

	return TRUE;
}

/*
* Helper function used by GameBoard_isValidMove() to retrieve all valid moves.
*/
static void calculateValidMoves()
{
	/* directions in clockwise order, starting from up */
	static const Vec2 directions[8] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };

	/* find opponent's pieces */
	char opponentPiece;
	if (s_CurrentTurn == WHITE_PIECE)
		opponentPiece = BLACK_PIECE;
	else
		opponentPiece = WHITE_PIECE;

	Vec2 coord;
	Vec2 adjacentCoord;
	int i;
	for (coord.x = 0; coord.x < BOARD_WIDTH; coord.x++)
	{
		for (coord.y = 0; coord.y < BOARD_WIDTH; coord.y++)
		{
			for (i = 0; i < 8; i++)
			{
				if (s_Board[coord.x][coord.y] == opponentPiece)
				{
					adjacentCoord = Vec2_add(coord, directions[i]);
					if (isInBounds(adjacentCoord) && s_Board[coord.x][coord.y] == EMPTY_MARKER)
					{

					}
				}
			}
		}
	}
}

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
	printf("  ");

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
		printf(" %d ", y);
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			printf("%c ", s_Board[x][y]);
		}
		printf("\n");
	}
}

BOOL GameBoard_isValidMove(Vec2 coords)
{
	/* if move is outside of bounds, return early */
	if (!isInBounds(coords))
		return FALSE;

	/* if valid moves haven't been calculated yet, calculate them */
	if (s_ValidMoves.count == 0)
		calculateValidMoves();

	/* look for move in valid moves, if found, move is valid */
	int i;
	Vec2 moveCoords;
	for (i = 0; i < s_ValidMoves.count; i++)
	{
		moveCoords = s_ValidMoves.moves[i].coord;
		if (Vec2_equal(coords, moveCoords))
			return TRUE;
	}

	return FALSE;
}

void GameBoard_playMove(Vec2 coords)
{
	s_Board[coords.x][coords.y] = s_CurrentTurn;

	/* now that move has been played, valid moves will need to be recalculated */
	s_ValidMoves.count = 0;
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
