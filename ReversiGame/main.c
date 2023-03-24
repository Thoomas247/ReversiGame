#include <stdio.h>

#include "GameOptions.h"

int main(int argc, char* argv[])
{
	parseGameOptions(argc, argv);
	printGameOptions();

	return 0;
}