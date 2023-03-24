#include <stdio.h>

#include "GameOptions.h"
#include "GameState.h"

char board[BOARD_WIDTH][BOARD_WIDTH];
char turn;

int main(int argc, char* argv[])
{
	parseGameOptions(argc, argv);
	printGameOptions();

	saveGameState(turn, &board[0][0]);
	loadLastGameState(&turn, &board[0][0]);
	freeGameStates();

	return 0;
}