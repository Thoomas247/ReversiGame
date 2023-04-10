#include "GameOptions.h"

#include <stdlib.h>
#include <stdio.h>

#define FILE_ARG 'f'
#define UNDO_ARG 'u'
#define PIECE_ARG 'p'

/*
* We want access to this variable to be restricted to GameOptions.c, so we declare it static.
*/
static GameOptions s_GameOptions;

void GameOptions_parse(int argc, char* argv[])
{
	/* reset game options */
	s_GameOptions.saveFileName[0] = '\0';
	s_GameOptions.allowUndo = FALSE;
	s_GameOptions.playerPiece = WHITE_PIECE;

	/* find valid command line arguments */
	char arg;
	int i;
	for (i = 0; i < argc; i++)
	{
		if (sscanf(argv[i], "-%c", &arg))
		{
			if (arg == FILE_ARG)
			{
				/* read the next argument, which should be the file name */
				if (sscanf(argv[i + 1], "%s", &s_GameOptions.saveFileName) && s_GameOptions.saveFileName[0] != '-')
				{
					i++;
				}

				/* if file name could not be read or is invalid, make sure we reset s_GameOptions.saveFileName */
				else
				{
					s_GameOptions.saveFileName[0] = '\0';
				}
			}

			else if (arg == UNDO_ARG)
			{
				s_GameOptions.allowUndo = TRUE;
			}

			else if (arg == PIECE_ARG)
			{
				/* read the next argument, which should be a character (WHITE_PIECE or BLACK_PIECE) */
				if (sscanf(argv[i + 1], "%c", &arg) && (arg == WHITE_PIECE || arg == BLACK_PIECE))
				{
					s_GameOptions.playerPiece = arg;
					i++;
				}
			}
		}
	}
}

void GameOptions_print()
{
	printf("Save File: %s\n", s_GameOptions.saveFileName);
	printf("Allow Undo: %d\n", s_GameOptions.allowUndo);
	printf("Player Piece: %c\n", s_GameOptions.playerPiece);
}

BOOL GameOptions_allowUndo()
{
	return s_GameOptions.allowUndo;
}

char GameOptions_getPlayerPiece()
{
	return s_GameOptions.playerPiece;
}

char GameOptions_getComputerPiece()
{
	if (s_GameOptions.playerPiece == WHITE_PIECE)
		return BLACK_PIECE;

	return WHITE_PIECE;
}
