#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define _CRT_SECURE_NO_WARNINGS

#define COLUMNS 10
#define ROWS 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "log.h"
#include "animation.h"
#include "ships.h"

//coordinate struct
struct cord {
	int x;
	int y;
};

//basic cell struct
struct cell {
	char piece;
	char preview;
	int entrop;
};

//grid struct
struct grid {
	struct cell field[COLUMNS * ROWS];
};

//player struct
/*
0-carrier
1-battleShip
2-cruiser
3-sub
4-destroyer
*/
struct player {
	struct grid ships;
	struct grid shots;
	struct stats stats;
	int shipHealth[5];
	int playerNumber;
};

//delay time
void delay(int number_of_seconds);

//init grid
void initGrid(struct grid* field);

//init player struct
void initPlayer(struct player* player, int playerNum);

//get random cordinate
int getRand();

//get coordinates based on entropy
struct cord getRandCords(struct grid* grid);

//check cell
char checkCell(int x, int y, struct grid* field);

//update damage
int updateDamage(char cellValue, struct player* player);

//update entropy
void updateEnt(int x, int y, int hit, struct grid* grid);

//check for win
int checkWin(struct player* P1, struct player* P2);

//change cell value
void changeCell(int x, int y, char value, struct grid* field);

//check placement
int checkPlacement(struct grid* grid, struct ship* ship, int x, int y);

//place ship
void placeShip(struct grid* grid, struct ship* ship, int x, int y);

//remove specific ship type
void removeShip(struct grid* grid, int shipType);

//place ships randomly
void randPlaceShips(struct player* player);

//manually place ships(randmode all ships already placed)
int manPlaceShips(struct player* player, int randMode);

//ship placement menu
int menuShips(struct player* P1, struct player* P2);

//player turn
void playerTurn(struct player* P1, struct player* P2);

//automated turn
void autoTurn(struct player* P1, struct player* P2, int delayTime, int hidden);

//game loop
void gameloop();

//simulation loop
void simLoop(int delayTime);

//main menu
void menuMain();

//rules menu
void menuRules();











#endif // !BATTLESHIP_H

