#pragma once

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MAX_FILE_NAME_SIZE 64

#define WHITE_PIECE 'O'
#define BLACK_PIECE 'X'

typedef struct GameOptions
{
	char saveFileName[MAX_FILE_NAME_SIZE];
	BOOL allowUndo;
	char playerPiece;
} GameOptions;

/*
* Initializes the game options given the command line arguments.
*/
void parseGameOptions(int argc, char* argv[]);

/*
* Prints the current game options to the output window.
* Used for debugging.
*/
void printGameOptions();

/*
* Provides read-only access to the GameOptions instance.
*/
const GameOptions* getGameOptions();