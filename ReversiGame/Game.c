#include "Game.h"

#include <stdio.h>
#include <ctype.h>

#include "GameOptions.h"
#include "GameState.h"
#include "GameBoard.h"

/*
* Reads stdin until '\n' or EOF is reached.
* Used to get rid of any extra characters left in the buffer after a read.
*/
static void clearInputBuffer()
{
	char clearChar;
	while ((clearChar = getchar()) != '\n' && clearChar != EOF);
}

/*
* Returns the move which the player wants to play.
* Handles undo operations as well, and will always return a valid move given that one exists.
*/
static Vec2 getPlayerMove()
{
	GameBoard_print(FALSE);

	char undoChar;

	Vec2 move;
	BOOL validMove = FALSE;
	do
	{
		/* get player input */
		printf("Jogador H (%c) (linha e coluna) = ", GameBoard_getTurn());

		/* check for a successful move read */
		if (scanf("%d %d", &move.y, &move.x) == 2 && GameBoard_isValidMove(move))
		{
			validMove = TRUE;

			/* if too many characters are written, fgets will not clear the input buffer properly, so we do it manually */
			clearInputBuffer();
		}

		/* check for a successful undo read */
		else if (GameOptions_get()->allowUndo && scanf("%c", &undoChar) == 1 && tolower(undoChar) == UNDO_CHAR)
		{
			printf("\n");
			GameBoard_undo();
			GameBoard_calculateValidMoves();
			GameBoard_print(FALSE);

			clearInputBuffer();
		}

		/* handle invalid input */
		else
		{
			printf("\nMovimento invalido, tente novamente...\n");
		}
	} 
	while (!validMove);

	return move;
}

/*
* Returns the move which the AI wants to play.
* Will always return a valid move given that one exists.
*/
static Vec2 getComputerMove()
{
	Vec2 move;

	GameBoard_print(TRUE);
	printf("Jogador IA (%c) esta a jogar\n", GameBoard_getTurn());

	move = GameBoard_getBestMove();

	printf("Jogador IA jogou %d %d\n", move.y, move.x);

	return move;
}

void Game_start(int argc, char* argv[])
{
	GameOptions_parse(argc, argv);

	GameBoard_create();

	Vec2 move;
	BOOL playing = TRUE;
	while (playing)
	{
		GameBoard_calculateValidMoves();

		/* check if game has ended */
		if (!GameBoard_hasValidMoves())
		{
			/* TODO: count pieces and end game */
		}

		else
		{
			/* handle the current turn */
			if (GameBoard_getTurn() == GameOptions_get()->playerPiece)
			{
				/* save the game state if undo is allowed */
				if (GameOptions_get()->allowUndo)
				{
					GameBoard_save();
				}

				move = getPlayerMove();
			}
			else
			{
				move = getComputerMove();
			}

			printf("\n");

			GameBoard_playMove(move);
			GameBoard_swapTurn();
		}
	}

	GameState_freeAll();
}