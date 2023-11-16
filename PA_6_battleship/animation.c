#include "animation.h"

//print menu option
void printMenu(char* option, char* text) {
	printf("(%s) %s\n", option, text);
}

//print ship name
void printShipName(int shiptype) {

	switch (shiptype) {
	case 0:
		printf("[Carrier]");
		break;
	case 1:
		printf("[Battleship]");
		break;
	case 2:
		printf("[Cruiser]");
		break;
	case 3:
		printf("[Sub]");
		break;
	case 4:
		printf("[Destroyer]");
		break;
	}
}

//print ship
void printShip(struct ship* ship) {
	int i, j;

	for (i = 0; i < 5; i++) {
		printf("\n");
		for (j = 0; j < 5; j++) {
			printf("%c", ship->values[5 * i + j]);
		}
	}
}

//print title screen
void printTitle() {
	printf("                                     |__\n");
	printf("                                     |\\/\n");
	printf("                                     ---\n");
	printf("                                     / | [\n");
	printf("                              !      | |||\n");
	printf("                            _/|     _/|-++'\n");
	printf("                        +  +--|    |--|--|_ |-\n");
	printf("                     { /|__|  |/\\__|  |--- |||__/\n");
	printf("                    +---------------___[}-_===_.'____                 /\\\n");
	printf("                ____`-' ||___-{]_| _[}-  |     |_[___\\==--            \\/   _\n");
	printf(" __..._____--==/___]_|__|_____________________________[___\\==--____,------' .7\n");
	printf("|                                                                     BB-61/\n");
	printf(" \\\\_________________________________________________________________________|\n");
	printf("  Matthew Bace\n");
	printf(" ______   _______ __________________ _        _______  _______          _________ _______\n");
	printf("(  ___ \\ (  ___  )\\__   __/\\__   __/( \\      (  ____ \\(  ____ \\|\\     /|\\__   __/(  ____ )\n");
	printf("| (   ) )| (   ) |   ) (      ) (   | (      | (    \\/| (    \\/| )   ( |   ) (   | (    )|\n");
	printf("| (__/ / | (___) |   | |      | |   | |      | (__    | (_____ | (___) |   | |   | (____)|\n");
	printf("|  __ (  |  ___  |   | |      | |   | |      |  __)   (_____  )|  ___  |   | |   |  _____)\n");
	printf("| (  \\ \\ | (   ) |   | |      | |   | |      | (            ) || (   ) |   | |   | (\n");
	printf("| )___) )| )   ( |   | |      | |   | (____/\\| (____/\\/\\____) || )   ( |___) (___| )\n");
	printf("|/ \\___/ |/     \\|   )_(      )_(   (_______/(_______/\\_______)|/     \\|\\_______/|/\n");
}

//print rules screen
void printRules() {
	printf("Rules for BattleShip\n");
	printf("\n");
	printf("Game Objective\n");
	printf("\n");
	printf("The object of Battleship is to try and sink all of the other player's before they sink all of your ships. All of the other player's ships are somewhere on his/her board.\n");
	printf("You try and hit them by calling out the coordinates of one of the squares on the board.  The other player also tries to hit your ships by calling out coordinates.\n");
	printf("Neither you nor the other player can see the other's board so you must try to guess where they are.  Each board in the physical game has two grids:  the lower (horizontal)\n");
	printf("section for the player's ships and the upper part (vertical during play) for recording the player's guesses.\n");
	printf("\n");
	printf("Starting a New Game");
	printf("\n");
	printf("Each player places the 5 ships somewhere on their board.  The ships can only be placed vertically or horizontally. Diagonal placement is not allowed.\n");
	printf("No part of a ship may hang off the edge of the board.  Ships may not overlap each other.  No ships may be placed on another ship.\n");
	printf("Once the guessing begins, the players may not move the ships.\n");
	printf("\n");
	printf("The 5 ships are:  Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).\n");
	printf("\n");
	printf("Playing the Game\n");
	printf("\n");
	printf("Player's take turns guessing by calling out the coordinates. The opponent responds with 'hit' or 'miss' as appropriate.\n");
	printf("Both players should mark their board with pegs:  red for hit, white for miss.\n");
	printf("When all of the squares that one your ships occupies have been hit, the ship will be sunk. \n");
	printf("As soon as all of one player's ships have been sunk, the game ends.\n");
}

//print player grids
void printPlayer(struct player* player) {
	int i, j;

	//print hits top labels
	printf("Player %d\n", player->playerNumber);
	printf("         HITS/MISSES\n");
	printf(" ");
	for (i = 0; i < COLUMNS; i++) {
		printf("%3d", (i + 1));
	}
	printf("\n");

	//print hits board
	for (i = 0; i < ROWS; i++) {

		printf("%c", (i + 65));

		for (j = 0; j < COLUMNS; j++) {
			printf("%3c", player->shots.field[COLUMNS * j + i].piece);
		}

		printf("\n");
	}

	//print ships top labels
	printf("         PLAYER SHIPS\n");
	printf(" ");
	for (i = 0; i < COLUMNS; i++) {
		printf("%3d", (i + 1));
	}
	printf("\n");

	//print ships board
	for (i = 0; i < ROWS; i++) {

		printf("%c", (i + 65));

		for (j = 0; j < COLUMNS; j++) {
			printf("%3c", player->ships.field[COLUMNS * j + i].piece);
		}

		printf("\n");
	}
}

//print end grids
void printEndGrids(struct player* P1, struct player* P2) {
	int i, j;

	//print hits top labels
	printf("         PLAYER 1\n");
	printf(" ");
	for (i = 0; i < COLUMNS; i++) {
		printf("%3d", (i + 1));
	}
	printf("\n");

	//print ships board
	for (i = 0; i < ROWS; i++) {

		printf("%c", (i + 65));

		for (j = 0; j < COLUMNS; j++) {
			printf("%3c", P1->ships.field[COLUMNS * j + i].piece);
		}

		printf("\n");
	}

	//print ships top labels
	printf("         PLAYER 2\n");
	printf(" ");
	for (i = 0; i < COLUMNS; i++) {
		printf("%3d", (i + 1));
	}
	printf("\n");

	//print ships board
	for (i = 0; i < ROWS; i++) {

		printf("%c", (i + 65));

		for (j = 0; j < COLUMNS; j++) {
			printf("%3c", P2->ships.field[COLUMNS * j + i].piece);
		}

		printf("\n");
	}
}