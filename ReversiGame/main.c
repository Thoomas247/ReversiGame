#include <stdio.h>

#include "GameOptions.h"
#include "GameState.h"
#include "GameBoard.h"

void handlePlayerMove()
{
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

void handleComputerMove()
{
	printf("Jogador IA (%c) esta a jogar\n", GameBoard_getTurn());
}

int main(int argc, char* argv[])
{
	GameOptions_parse(argc, argv);
	//GameOptions_print();

	GameBoard_create();

	while (TRUE)
	{
		GameBoard_print();

		if (GameBoard_getTurn() == GameOptions_get()->playerPiece)
		{
			handlePlayerMove();
		}
		else
		{
			handleComputerMove();
		}

		printf("\n");

		GameBoard_swapTurn();
	}

	//GameBoard_save();
	//GameBoard_undo();
	GameState_freeAll();

	return 0;
}