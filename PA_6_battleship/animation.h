#ifndef ANIMATION_H
#define ANIMATION_H

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <time.h>

#include "battleship.h"

//print menu option
void printMenu(char* option, char* text);

//print ship name
void printShipName(int shiptype);

//print ship
void printShip(struct ship* ship);

//print title screen
void printTitle();

//print rules screen
void printRules();

//print player grids
void printPlayer(struct player* player);

//print end grids
void printEndGrids(struct player* P1, struct player* P2);



#endif // !ANIMATION_H
