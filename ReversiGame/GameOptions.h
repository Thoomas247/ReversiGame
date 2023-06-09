/*
* Thomas Amiouny (107527)
* Gon�alo Paiva	(106888)
*/

#ifndef GAMEOPTIONS_H_
#define GAMEOPTIONS_H_

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MAX_FILE_NAME_SIZE 128

#define BOARD_WIDTH 8

#define UNDO_CHAR 'u'

#define WHITE_PIECE 'O'
#define BLACK_PIECE 'X'
#define EMPTY_MARKER '.'
#define VALID_MARKER 'P'

typedef struct GameOptions
{
	char saveFileName[MAX_FILE_NAME_SIZE];
	BOOL allowUndo;
	char playerPiece;
} GameOptions;

/*
* Initializes the game options given the command line arguments.
*/
void GameOptions_parse(int argc, char* argv[]);

/*
* Prints the current game options to the output window.
* Used for debugging.
*/
void GameOptions_print();

/*
* Returns the name of the file to save the game state to.
* NULL if saving is disabled.
*/
const char* GameOptions_getSaveFileName();

/*
* Returns whether the undo operation is allowed.
*/
BOOL GameOptions_allowUndo();

/*
* Returns the player's piece.
*/
char GameOptions_getPlayerPiece();

/*
* Returns the computer's piece.
*/
char GameOptions_getComputerPiece();

#endif /* GAMEOPTIONS_H_ */