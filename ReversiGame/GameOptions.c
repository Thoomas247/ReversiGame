/*
* Thomas Amiouny (107527)
* Gonçalo Paiva	(106888)
*/

#include "GameOptions.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_ARG "-f"
#define UNDO_ARG "-u"
#define PIECE_ARG "-p"

/*
* We want access to this variable to be restricted to GameOptions.c, so we declare it static.
*/
static GameOptions s_GameOptions;

void GameOptions_parse(int argc, char* argv[])
{
	int i;

	/* reset game options */
	s_GameOptions.saveFileName[0] = '\0';
	s_GameOptions.allowUndo = FALSE;
	s_GameOptions.playerPiece = WHITE_PIECE;

	/* find valid command line arguments */
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], FILE_ARG) == 0)
		{
			/* read the next argument, which should be the file name */
			if (sscanf(argv[i + 1], "%s", s_GameOptions.saveFileName) && s_GameOptions.saveFileName[0] != '-')
			{
				i++;
			}

			/* if file name could not be read or is invalid, make sure we reset s_GameOptions.saveFileName */
			else
			{
				s_GameOptions.saveFileName[0] = '\0';
			}
		}

		else if (strcmp(argv[i], UNDO_ARG) == 0)
		{
			s_GameOptions.allowUndo = TRUE;
		}

		else if (strcmp(argv[i], PIECE_ARG) == 0)
		{
			/* read the next argument, which should be a character (WHITE_PIECE or BLACK_PIECE) */
			char piece;
			if (sscanf(argv[i + 1], "%c", &piece) && (piece == WHITE_PIECE || piece == BLACK_PIECE))
			{
				s_GameOptions.playerPiece = piece;
				i++;
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

const char* GameOptions_getSaveFileName()
{
	return s_GameOptions.saveFileName;
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
