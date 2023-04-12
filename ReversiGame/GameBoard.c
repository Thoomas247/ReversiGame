/*
* Thomas Amiouny (107527)
* Gonçalo Paiva	(106888)
*/

#include "GameBoard.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GameOptions.h"
#include "GameState.h"

#include "ValidMove.h"

#define MAX_VALID_MOVES BOARD_WIDTH * BOARD_WIDTH

#define BIT(n) 1 << n

/* we want access to these variables to be restricted to GameBoard.c, so we declare them static */
static char s_Board[BOARD_WIDTH][BOARD_WIDTH];
static char s_CurrentTurn;
static ValidMoveList s_ValidMoves;

/* directions in clockwise order, starting from up */
const Vec2 DIRECTIONS[8] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };

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
* Helper function to get the currently-not-playing player's piece.
*/
static char getOpponentPiece()
{
	if (s_CurrentTurn == WHITE_PIECE)
		return BLACK_PIECE;
	else
		return WHITE_PIECE;
}

/*
* Helper function to calculate how many captures would occur from playing this move.
* Used by GameBoard_calculateValidMoves().
*/
static void calculateCaptureStrength(ValidMove* pValidMove)
{
	const char opponentPiece = getOpponentPiece();

	pValidMove->strength = 0;
	pValidMove->directions = 0;

	int currentStrength;
	Vec2 adjacentCoord;
	char currentPiece;

	/* check every direction for opposing pieces */
	int i;
	for (i = 0; i < 8; i++)
	{
		currentStrength = 0;
		adjacentCoord = pValidMove->coord;
		currentPiece = opponentPiece;

		/* continue in this direction to find how many points it would earn */
		while (isInBounds(adjacentCoord) && currentPiece != s_CurrentTurn && currentPiece != EMPTY_MARKER)
		{
			adjacentCoord = Vec2_add(adjacentCoord, DIRECTIONS[i]);

			currentPiece = s_Board[adjacentCoord.x][adjacentCoord.y];

			if (currentPiece == opponentPiece)
				currentStrength++;
		}

		/* if the line ends in one of the current player's pieces, the move is valid */
		if (currentPiece == s_CurrentTurn && currentStrength > 0)
		{
			pValidMove->strength += currentStrength;
			pValidMove->directions |= BIT(i);	/* mark this direction as valid */
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

int GameBoard_getPieceCount(char piece)
{
	/* no need to count if it is not a valid piece */
	if (piece != WHITE_PIECE && piece != BLACK_PIECE)
		return 0;

	int count = 0;

	int x;
	int y;
	for (x = 0; x < BOARD_WIDTH; x++)
	{
		for (y = 0; y < BOARD_WIDTH; y++)
		{
			if (s_Board[x][y] == piece)
			{
				++count;
			}
		}
	}

	return count;
}

void GameBoard_print(BOOL showValidMoves)
{
	/* change valid positions to VALID_MARKER */
	if (showValidMoves)
	{
		ValidMoveNode* it = s_ValidMoves.pFirst;

		while (it != NULL)
		{
			s_Board[it->data.coord.x][it->data.coord.y] = VALID_MARKER;
			it = it->pNext;
		}
	}

	/* print column numbers */
	printf("  ");

	int i;
	for (i = 0; i < BOARD_WIDTH; i++)
	{
		printf(" %d", i);
	}

	printf("\n");

	/* print grid */
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

	/* change valid positions back to EMPTY_MARKER */
	if (showValidMoves)
	{
		ValidMoveNode* it = s_ValidMoves.pFirst;

		while (it != NULL)
		{
			s_Board[it->data.coord.x][it->data.coord.y] = EMPTY_MARKER;
			it = it->pNext;
		}
	}
}

void GameBoard_calculateValidMoves()
{
	const char opponentPiece = getOpponentPiece();

	/* array to keep track of moves which have been calculated */
	/* static so that it doesn't have to be reallocated every time */
	static BOOL calculatedMoves[BOARD_WIDTH][BOARD_WIDTH];

	/* clear calculated moves */
	memset(calculatedMoves, FALSE, sizeof(calculatedMoves));

	ValidMoveList_clear(&s_ValidMoves);

	Vec2 coord;
	ValidMove validMove;

	int i;
	for (coord.x = 0; coord.x < BOARD_WIDTH; coord.x++)
	{
		for (coord.y = 0; coord.y < BOARD_WIDTH; coord.y++)
		{
			/* if an opponent's piece is found, check for empty squares around it */
			if (s_Board[coord.x][coord.y] == opponentPiece)
			{
				for (i = 0; i < 8; i++)
				{
					validMove.coord = Vec2_add(coord, DIRECTIONS[i]);

					/* if the adjacent square is in bounds and empty, check if move would result in captures */
					if (isInBounds(validMove.coord) && s_Board[validMove.coord.x][validMove.coord.y] == EMPTY_MARKER)
					{
						/* skip move if it has already been calculated */
						if (!calculatedMoves[validMove.coord.x][validMove.coord.y])
						{
							calculatedMoves[validMove.coord.x][validMove.coord.y] = TRUE;

							calculateCaptureStrength(&validMove);

							/* add move to list if it results in captures */
							if (validMove.strength > 0)
							{
								ValidMoveList_add(&s_ValidMoves, validMove);
							}
						}
					}
				}
			}
		}
	}
}

BOOL GameBoard_hasValidMoves()
{
	if (s_ValidMoves.count > 0)
		return TRUE;

	return FALSE;
}

Vec2 GameBoard_getBestMove()
{
	ValidMoveNode* it = s_ValidMoves.pFirst;
	ValidMove* pBestMove = &it->data;

	while (it != NULL)
	{
		/* if the current move is stronger, replace best move */
		if (it->data.strength > pBestMove->strength)
		{
			pBestMove = &it->data;
		}

		/* if current move has the same strength, but is closer to the top-left, replace best move */
		else if (it->data.strength == pBestMove->strength && Vec2_componentSum(it->data.coord) < Vec2_componentSum(pBestMove->coord))
		{
			pBestMove = &it->data;
		}

		it = it->pNext;
	}

	return pBestMove->coord;
}

BOOL GameBoard_isValidMove(Vec2 coords)
{
	/* if move is outside of bounds, return early */
	if (!isInBounds(coords))
		return FALSE;

	/* look for move in valid moves: if found, move is valid */
	ValidMoveNode* it = s_ValidMoves.pFirst;
	while (it != NULL)
	{
		if (Vec2_equal(coords, it->data.coord))
			return TRUE;

		it = it->pNext;
	}

	return FALSE;
}

void GameBoard_playMove(Vec2 coords)
{
	const char opponentPiece = getOpponentPiece();

	/* get valid move corresponding to these coords */
	ValidMove* pValidMove = NULL;

	ValidMoveNode* it = s_ValidMoves.pFirst;
	while (it != NULL)
	{
		if (Vec2_equal(coords, it->data.coord))
		{
			pValidMove = &it->data;

			/* stop the loop */
			it = NULL;
		}
		else
		{
			it = it->pNext;
		}
	}

	if (pValidMove)
	{
		Vec2 currentCoord;
		char currentPiece;

		s_Board[coords.x][coords.y] = s_CurrentTurn;

		/* loop through every valid direction */
		int i;
		for (i = 0; i < 8; i++)
		{
			if (pValidMove->directions & BIT(i))
			{
				currentCoord = pValidMove->coord;
				currentPiece = opponentPiece;

				/* flip all opponents pieces in that direction */
				while (currentPiece != s_CurrentTurn)
				{
					currentCoord = Vec2_add(currentCoord, DIRECTIONS[i]);
					currentPiece = s_Board[currentCoord.x][currentCoord.y];

					s_Board[currentCoord.x][currentCoord.y] = s_CurrentTurn;
				}
			}
		}
	}
}

void GameBoard_save(Vec2 move)
{
	GameState_save(s_CurrentTurn, &s_Board[0][0], move);
}

void GameBoard_undo()
{
	GameState_loadPrevious(&s_CurrentTurn, &s_Board[0][0]);
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
