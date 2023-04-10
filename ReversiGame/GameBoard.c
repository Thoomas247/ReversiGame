#include "GameBoard.h"

#include <stdio.h>
#include <string.h>

#include "GameOptions.h"
#include "GameState.h"

#define MAX_VALID_MOVES BOARD_WIDTH * BOARD_WIDTH

#define BIT(n) 1 << n

typedef unsigned int DirectionField;

/*
* Struct representing a single valid move and the number of points it would give.
* Only visible within GameBoard.c.
*/
typedef struct ValidMove
{
	Vec2 coord;
	int strength;
	DirectionField directions;
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
	int i;

	if (showValidMoves)
	{
		for (i = 0; i < s_ValidMoves.count; i++)
		{
			s_Board[s_ValidMoves.moves[i].coord.x][s_ValidMoves.moves[i].coord.y] = VALID_MARKER;
		}
	}

	/* print column numbers */
	printf("  ");

	//int i;
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

	if (showValidMoves)
	{
		for (i = 0; i < s_ValidMoves.count; i++)
		{
			s_Board[s_ValidMoves.moves[i].coord.x][s_ValidMoves.moves[i].coord.y] = EMPTY_MARKER;
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

	s_ValidMoves.count = 0;

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
							if (validMove.strength > 0)
							{
								s_ValidMoves.moves[s_ValidMoves.count] = validMove;
								s_ValidMoves.count++;
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
	int maxStrength = 0;
	int maxIndex = 0;

	int i;
	for (i = 0; i < s_ValidMoves.count; i++)
	{
		if (s_ValidMoves.moves[i].strength > maxStrength)
		{
			maxStrength = s_ValidMoves.moves[i].strength;
			maxIndex = i;
		}
	}

	return s_ValidMoves.moves[maxIndex].coord;
}

BOOL GameBoard_isValidMove(Vec2 coords)
{
	/* if move is outside of bounds, return early */
	if (!isInBounds(coords))
		return FALSE;

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
	const char opponentPiece = getOpponentPiece();

	/* get valid move corresponding to these coords */
	ValidMove* pValidMove = NULL;
	ValidMove* pMove;
	int i;
	for (i = 0; i < s_ValidMoves.count; i++)
	{
		pMove = &s_ValidMoves.moves[i];
		if (Vec2_equal(coords, pMove->coord))
		{
			pValidMove = pMove;
			break;
		}
	}

	if (pValidMove)
	{
		Vec2 currentCoord;
		char currentPiece;

		s_Board[coords.x][coords.y] = s_CurrentTurn;

		/* loop through every valid direction */
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
