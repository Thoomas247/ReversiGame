#include "Game.h"

#include <stdio.h>

#include "GameOptions.h"
#include "GameState.h"
#include "GameBoard.h"

static void handlePlayerTurn()
{
	GameBoard_print(FALSE);

	Vec2 coords;
	BOOL validMove = FALSE;
	while (!validMove)
	{
		/* get player input */
		printf("Jogador H (%c) (linha e coluna) = ", GameBoard_getTurn());

		/* check for valid input and move */
		if (scanf("%d %d", &coords.y, &coords.x) == 2 && GameBoard_isValidMove(coords))
			validMove = TRUE;

		else
			printf("\nMovimento invalido, tente novamente...\n");

		/* if too many characters are written, scanf will not clear the input buffer properly, so we do it manually */
		while (getchar() != '\n');
	}

	GameBoard_playMove(coords);
}

static void handleComputerTurn()
{
	Vec2 move;

	GameBoard_print(TRUE);
	printf("Jogador IA (%c) esta a jogar\n", GameBoard_getTurn());

	move = GameBoard_getBestMove();

	GameBoard_playMove(move);
	printf("Jogador IA jogou %d %d\n", move.y, move.x);
}

void Game_start(int argc, char* argv[])
{
	GameOptions_parse(argc, argv);

	GameBoard_create();

	BOOL playing = TRUE;
	while (playing)
	{
		GameBoard_calculateValidMoves();

		/* check if game has ended */
		if (!GameBoard_hasValidMoves())
		{
			/* TODO: count pieces */
		}

		if (GameBoard_getTurn() == GameOptions_get()->playerPiece)
		{
			handlePlayerTurn();
		}
		else
		{
			handleComputerTurn();
		}

		printf("\n");

		GameBoard_swapTurn();
	}

	GameState_freeAll();
}