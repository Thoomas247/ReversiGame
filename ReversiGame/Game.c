/*
* Thomas Amiouny (107527)
* Gonçalo Paiva	(106888)
*/

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
static void clearInputBuffer();

/*
* Returns the move which the player wants to play.
* Handles undo operations as well, and will always return a valid move given that one exists.
*/
static Vec2 getPlayerMove();

/*
* Returns the move which the AI wants to play.
* Will always return a valid move given that one exists.
*/
static Vec2 getComputerMove();

/*
* Prints the score and winner.
*/
static void printWinner();

void Game_start(int argc, char* argv[])
{
	Vec2 move;
	BOOL playing = TRUE;
	BOOL lastPlayerPlayed = FALSE;

	GameOptions_parse(argc, argv);

	GameBoard_create();

	while (playing)
	{
		GameBoard_calculateValidMoves();

		/* play turn if possible */
		if (GameBoard_hasValidMoves())
		{
			lastPlayerPlayed = TRUE;

			/* handle the current turn */
			if (GameBoard_getTurn() == GameOptions_getPlayerPiece())
			{
				move = getPlayerMove();
			}
			else
			{
				move = getComputerMove();
			}

			printf("\n");

			/* save the game state if undo is allowed or if the game needs to be saved */
			if (GameOptions_allowUndo() || GameOptions_getSaveFileName())
			{
				GameBoard_save(move);
			}

			GameBoard_playMove(move);
		}

		/* end game if neither player can play or current player doesn't have any pieces */
		else if (lastPlayerPlayed == FALSE || GameBoard_getPieceCount(GameBoard_getTurn()) == 0)
		{
			printWinner();
			playing = FALSE;
		}

		/* otherwise, skip turn */
		else
		{
			lastPlayerPlayed = FALSE;
		}

		GameBoard_swapTurn();
	}

	/* save the game to a file if requested */
	GameState_printToFile(GameOptions_getSaveFileName());

	GameState_freeAll();
}

static void clearInputBuffer()
{
	char clearChar;
	while ((clearChar = getchar()) != '\n' && clearChar != EOF);
}

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
		if (scanf("%d %d", &move.y, &move.x) == 2)
		{
			if (GameBoard_isValidMove(move))
			{
				validMove = TRUE;
			}
			else
			{
				printf("\nPosicao invalida. Tente novamente...\n");
			}
		}

		/* check for a successful undo read */
		else if (GameOptions_allowUndo() && scanf("%c", &undoChar) == 1)
		{
			if (tolower(undoChar) == UNDO_CHAR)
			{
				printf("\n");
				GameBoard_undo();
				GameBoard_calculateValidMoves();
				GameBoard_print(FALSE);
			}
			else
			{
				printf("\nComando desconhecido. Tente novamente...\n");
			}
		}

		/* handle invalid input */
		else
		{
			printf("\nEntrada invalida. Tente novamente...\n");
		}

		/* if too many characters are written, fgets will not clear the input buffer properly, so we do it manually */
		clearInputBuffer();
	} while (!validMove);

	return move;
}

static Vec2 getComputerMove()
{
	Vec2 move;

	GameBoard_print(TRUE);
	printf("Jogador IA (%c) esta a jogar\n", GameBoard_getTurn());

	move = GameBoard_getBestMove();

	printf("Jogador IA jogou %d %d\n", move.y, move.x);

	return move;
}

static void printWinner()
{
	int playerScore;
	int computerScore;

	/* print the final board */
	GameBoard_print(FALSE);

	/* print scores and winner */
	playerScore = GameBoard_getPieceCount(GameOptions_getPlayerPiece());
	computerScore = GameBoard_getPieceCount(GameOptions_getComputerPiece());

	printf("\n");

	if (playerScore == computerScore)
	{
		printf("Jogo terminou empatado!\n");
	}

	else if (playerScore > computerScore)
	{
		printf("Jogador H ganhou!\n");
	}

	else
	{
		printf("Jogador IA ganhou!\n");
	}

	printf("Jogador H: %d\tJogador IA: %d\n", playerScore, computerScore);
}