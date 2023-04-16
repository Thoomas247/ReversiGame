#makefile trab2_107527_106888

all: flipflop

Game.o: Game.c Game.h
	gcc -g -Wall -pedantic -ansi -c Game.c

GameBoard.o: GameBoard.c GameBoard.h
	gcc -g -Wall -pedantic -ansi -c GameBoard.c

GameOptions.o: GameOptions.c GameOptions.h
	gcc -g -Wall -pedantic -ansi -c GameOptions.c

GameState.o: GameState.c GameState.h
	gcc -g -Wall -pedantic -ansi -c GameState.c

ValidMove.o: ValidMove.c ValidMove.h
	gcc -g -Wall -pedantic -ansi -c ValidMove.c

Vec2.o: Vec2.c Vec2.h
	gcc -g -Wall -pedantic -ansi -c Vec2.c

main.o: main.c
	gcc -g -Wall -pedantic -ansi -c main.c

flipflop: main.o Vec2.o ValidMove.o GameState.o GameOptions.o GameBoard.o Game.o
	gcc -g -Wall -pedantic -ansi main.o Vec2.o ValidMove.o GameState.o GameOptions.o GameBoard.o Game.o -o flipflop

clean:
	rm main.o Vec2.o ValidMove.o GameState.o GameOptions.o GameBoard.o Game.o


