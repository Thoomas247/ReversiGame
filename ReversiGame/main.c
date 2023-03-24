#include <stdio.h>

#include "GameOptions.h"
#include "GameState.h"
#include "GameBoard.h"

int main(int argc, char* argv[])
{
	GameOptions_parse(argc, argv);
	GameOptions_print();

	GameBoard_create();

	MoveCoords coords;
	while (TRUE)
	{
		GameBoard_print();

		if (GameBoard_getTurn() == GameOptions_get()->playerPiece)
		{
			printf("Jogador H (%c) (linha e coluna) = ", GameBoard_getTurn());

			/* get player input */
			BOOL validMove = FALSE;
			while (!validMove)
			{
				if (scanf("%d %d", &coords.y, &coords.y) == 2 && GameBoard_isValidMove(coords))
				{
					validMove = TRUE;
				}
				else
				{
					printf("\nPor favor entra dois numeros entre 0 e %d", BOARD_WIDTH - 1);
				}
			}

			GameBoard_playMove(coords);
		}
		else
		{
			printf("Jogador IA (%c) esta a jogar\n", GameBoard_getTurn());
		}

		printf("\n");

		GameBoard_swapTurn();
	}

	GameBoard_save();
	GameBoard_undo();
	GameState_freeAll();

	return 0;
}