/*
* Thomas Amiouny (107527)
* Gonçalo Paiva	(106888)
*/

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MAX_FILE_NAME_SIZE 64

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