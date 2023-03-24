#include <stdio.h>

#include "GameOptions.h"
#include "GameState.h"

typedef char Board[BOARD_WIDTH][BOARD_WIDTH];

void createGameBoard(Board* board)
{
	/* clear board */
	int x;
	int y;
	for (x = 0; x < BOARD_WIDTH; x++)
	{
		for (y = 0; y < BOARD_WIDTH; y++)
		{
			(*board)[x][y] = EMPTY_MARKER;
		}
	}

	/* add starting pieces */
	const int halfBoardWidth = BOARD_WIDTH / 2;
	(*board)[halfBoardWidth - 1][halfBoardWidth - 1] = WHITE_PIECE;
	(*board)[halfBoardWidth][halfBoardWidth - 1] = BLACK_PIECE;
	(*board)[halfBoardWidth - 1][halfBoardWidth] = BLACK_PIECE;
	(*board)[halfBoardWidth][halfBoardWidth] = WHITE_PIECE;
}

void printGameBoard(const Board* board)
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
			printf("%c ", (*board)[x][y]);
		}
		printf("\n");
	}
}

BOOL isInBounds(int x, int y)
{
	if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_WIDTH)
		return FALSE;

	return TRUE;
}

int main(int argc, char* argv[])
{
	Board board;
	char turn = WHITE_PIECE;

	parseGameOptions(argc, argv);
	printGameOptions();

	createGameBoard(&board);

	while (TRUE)
	{
		printGameBoard(&board);

		if (turn == getGameOptions()->playerPiece)
		{
			printf("Jogador H (%c) (linha e coluna) = ", turn);

			/* get player input */
			int x;
			int y;
			BOOL validMove = FALSE;
			while (!validMove)
			{
				if (scanf("%d %d", &y, &x) == 2 && isInBounds(x, y))
				{
					validMove = TRUE;
				}
				else
				{
					printf("\nPor favor entra dois numeros entre 0 e %d", BOARD_WIDTH - 1);
				}
			}

			board[x][y] = turn;
		}
		else
		{
			printf("Jogador IA (%c) esta a jogar\n", turn);
		}

		printf("\n");

		if (turn == WHITE_PIECE)
			turn = BLACK_PIECE;
		else
			turn = WHITE_PIECE;
	}

	saveGameState(turn, &board[0][0]);
	loadLastGameState(&turn, &board[0][0]);
	freeGameStates();

	return 0;
}