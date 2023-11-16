#include "battleship.h"

//delay time
void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
}

//init grid
void initGrid(struct grid* field) {
	int i;
	for (i = 0; i < (COLUMNS * ROWS); i++) {
		field->field[i].preview = '~';
		field->field[i].piece = '~';
		field->field[i].entrop = 1;
	}
}

//init player struct
void initPlayer(struct player* player, int playerNum) {
	initGrid(&player->ships);
	initGrid(&player->shots);
	initStats(&player->stats, playerNum);
	player->shipHealth[0] = 5;
	player->shipHealth[1] = 4;
	player->shipHealth[2] = 3;
	player->shipHealth[3] = 3;
	player->shipHealth[4] = 2;
	player->playerNumber = playerNum;
}

//get random cordinate
int getRand() {
	int randCord = rand() % 10;

	return randCord;
}

//get coordinates based on entropy
struct cord getRandCords(struct grid* grid) {
	int i, j;
	int max = 0;
	struct cord newCord = { (rand()%10),(rand() % 10) };

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLUMNS; j++) {
			if (grid->field[COLUMNS * i + j].entrop > max) {
				max = grid->field[i].entrop;
				newCord.x = i;
				newCord.y = j;
			}
		}
		
	}
	if (max <= 0) {
		while (grid->field[COLUMNS * newCord.x + newCord.y].piece != '~') {
			newCord.x = getRand();
			newCord.y = getRand();
		}
		
	}

	printf("returning: %d,%d\n", newCord.x, newCord.y);

	return newCord;
	
}

//check cell
char checkCell(int x, int y, struct grid* grid) {
	char cellValue = '0';

	if (x > 9 || y > 9) {
		printf("greater than");
		cellValue = '0';
	}
	else if (x < 0 || y < 0) {
		printf("less than");
		cellValue = '0';
	}
	else {
		cellValue = grid->field[COLUMNS * x + y].piece;
	}

	return cellValue;
}

//update damage
int updateDamage(char cellValue, struct player* player) {
	char result = cellValue;
	int sunk = 6;

	switch (result) {
	case 'C':
		player->shipHealth[0] -= 1;
		if (player->shipHealth[0] == 0) {
			sunk = 0;
			logSink(player->playerNumber, 'C');
		}
		break;
	case 'B':
		player->shipHealth[1] -= 1;
		if (player->shipHealth[1] == 0) {
			sunk = 1;
			logSink(player->playerNumber, 'B');
		}
		break;
	case 'c':
		player->shipHealth[2] -= 1;
		if (player->shipHealth[2] == 0) {
			sunk = 2;
			logSink(player->playerNumber, 'c');
		}
		break;
	case 'S':
		player->shipHealth[3] -= 1;
		if (player->shipHealth[3] == 0) {
			sunk = 3;
			logSink(player->playerNumber, 'S');
		}
		break;
	case 'D':
		player->shipHealth[4] -= 1;
		if (player->shipHealth[4] == 0) {
			sunk = 4;
			logSink(player->playerNumber, 'D');
		}
		break;
	default:
		break;
	}

	return sunk;

}

//update entropy
void updateEnt(int x, int y, int hit, struct grid* grid) {
	if (hit == 0) {
		//make entropy never choose a miss again
		grid->field[COLUMNS * x + y].entrop -= 99;
		//dont choose directly next to miss
		if (x - 1 > 0) {
			grid->field[COLUMNS * (x - 1) + y].entrop -= 1;
		}
		if (x + 1 < 9) {
			grid->field[COLUMNS * (x + 1) + y].entrop -= 1;
		}
		if (y - 1 > 0) {
			grid->field[COLUMNS * x  + (y - 1)].entrop -= 1;
		}
		if (y + 1 < 9) {
			grid->field[COLUMNS * x + (y + 1)].entrop -= 1;
		}
	}
	else {
		//dont choose hit again
		grid->field[COLUMNS * x + y].entrop -= 99;

		//if next to hit increase entropy
		if (x - 1 > 0) {
			grid->field[COLUMNS * (x - 1) + y].entrop += 4;
		}
		if (x + 1 < 9) {
			grid->field[COLUMNS * (x + 1) + y].entrop += 4;
		}
		if (y - 1 > 0) {
			grid->field[COLUMNS * x + (y - 1)].entrop += 4;
		}
		if (y + 1 < 9) {
			grid->field[COLUMNS * x + (y + 1)].entrop += 4;
		}
	}
}

//check win
int checkWin(struct player* P1, struct player* P2) {
	int win1 = 5;
	int win2 = 5;
	int i;

	for (i = 0; i < 5; i++) {
		if (P1->shipHealth[i] == 0) {
			win1 -= 1;
		}
		if (P2->shipHealth[i] == 0) {
			win2 -= 1;
		}
	}
	if (win1 <= 0) {
		P1->stats.win += 1;
		return 2;
	}
	else if (win2 <= 0) {
		P2->stats.win += 1;
		return 1;
	}
	else {
		return 0;
	}
}

//change cell value
void changeCell(int x, int y, char value, struct grid* grid) {
	grid->field[COLUMNS * x + y].piece = value;
}

//check placement
int checkPlacement(struct grid* grid, struct ship* ship, int x, int y) {
	int i, j;
	int fx, fy;
	int collision = 0;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			fx = x + j;
			fy = y + i;

			//check bounds
			if (ship->values[5 * i + j] != '~') {
				//check ship overlap
				if (grid->field[COLUMNS * fx + fy].piece != '~') {
					collision += 1;
				}
				else if (fx >= ROWS) {
					collision += 1;
				}
				else if (fy >= COLUMNS) {
					collision += 1;
				}
				else if (fx < 0 || fy < 0) {
					collision += 1;
				}
			}
		}
	}

	return collision;
}

//place ship
void placeShip(struct grid* grid, struct ship* ship, int x, int y) {
	int i, j;
	int fx, fy;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			fx = x + j;
			fy = y + i;

			if (ship->values[5 * i + j] != '~') {
				grid->field[COLUMNS * fx + fy].piece = ship->values[5 * i + j];
			}
			
		}
	}
}

//remove specific ship type
void removeShip(struct grid* grid, int shipType) {
	int i, j;
	char ship = '~';

	switch (shipType) {
	case 0:
		ship = 'C';
		break;
	case 1:
		ship = 'B';
		break;
	case 2:
		ship = 'c';
		break;
	case 3:
		ship = 'S';
		break;
	case 4:
		ship = 'D';
		break;
	default:
		break;
	}
	
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLUMNS; j++) {

			if (grid->field[COLUMNS * i + j].piece == ship) {
				grid->field[COLUMNS * i + j].piece = '~';
			}

		}
	}
}

//place ships randomly
void randPlaceShips(struct player* player) {
	//clear board if filled
	initPlayer(player, player->playerNumber);

	int randX = rand() % 10;
	int randY = rand() % 10;
	int randRot = rand() % 1;

	int placed = 0;

	struct ship ship;
	getShip(&ship, placed, randRot);
	
	
	while (placed != 5) {
		//get random coordinates
		randX = rand() % 10;
		randY = rand() % 10;
		randRot = rand() % 2;
		//get ship at rotation
		getShip(&ship, placed, randRot);

		//check for valid placement
		if (checkPlacement(&player->ships, &ship, randX, randY) == 0) {
			
			//place ship on board
			placeShip(&player->ships, &ship, randX, randY);
			printf("placed ship type:%d, x:%d, y:%d, rot:%d\n", placed, randX,randY,randRot);
			placed += 1;
		}

	}
	
}

//manually place ships
int manPlaceShips(struct player* player, int randMode) {
	
	int placed = 0;
	int mode = randMode;
	int i;
	

	for (i = 0; i < 5; i++) {
		int x;
		char cY;
		int rot = 0;

		struct ship ship;
		getShip(&ship, i, rot);
		
		int spot = 0;

		int choice = 0;

		system("cls");
		printPlayer(player);
		printf("\n");
		printShipName(i);
		printShip(&ship);
		printf("\n");
		printMenu("1", "change rotation");
		printMenu("2", "enter coordinates");
		printMenu("3", "confirm");
		printf("\n");

		while (choice != 4) {
			choice = 0;

			scanf("%d", &choice);

			switch (choice) {
			case 1:
				//change rotation reprint
				if (rot == 0) {
					rot = 1;
				}
				else {
					rot = 0;
				}
				getShip(&ship, i, rot);
				system("cls");
				printPlayer(player);
				printf("\n");
				printShipName(i);
				printShip(&ship);
				printf("\n");
				printMenu("1", "change rotation");
				printMenu("2", "enter coordinates");
				printMenu("3", "confirm");
				break;
			case 2:
				//prompt for cordinates check valid placment reprint
				system("cls");
				printPlayer(player);
				printf("\n");
				printShipName(i);
				printShip(&ship);
				printf("\n");
				printf("enter coordinates (i.e. A,6)\n");
				removeShip(&player->ships, i);
				spot = 0;
				while (spot == 0) {
					scanf(" %c,%d", &cY, &x);

					if (checkPlacement(&player->ships, &ship, (x-1), (cY-65)) == 0) {
						placeShip(&player->ships, &ship, (x-1), (cY - 65));
						spot = 1;
						system("cls");
						printPlayer(player);
						printf("\n");
						printShipName(i);
						printShip(&ship);
						printf("\n");
						printMenu("1", "change rotation");
						printMenu("2", "enter coordinates");
						printMenu("3", "confirm");
					}
					else {
						
						system("cls");
						printPlayer(player);
						printf("\n");
						printShipName(i);
						printShip(&ship);
						printf("\n");
						printf("[invalid placement]");
						printf("\n");
						printf("enter coordinates (i.e. A,6):");
						printf("\n");
					}
				}
				break;
			case 3:
				//check if ship has been placed before exit
				if (spot > 0) {
					placed += 1;
					choice = 4;
				}
				else if (mode == 1) {
					placed += 1;
					choice = 4;
				}
				else {
					system("cls");
					printPlayer(player);
					printf("\n");
					printShipName(i);
					printShip(&ship);
					printf("\n");
					printf("[invalid placement]");
					printf("\n");
					printMenu("1", "change rotation");
					printMenu("2", "enter coordinates");
					printMenu("3", "confirm");
				}
				break;
			default:
				break;
			}

		}
	}
	return placed;

}

//ship placement menu
int menuShips(struct player* P1, struct player* P2) {
	int choice = 0;
	int mode = 0;
	int placed = 0;

	//populate computer ships
	randPlaceShips(P2);

	system("cls");
	printPlayer(P1);
	printf("\n");
	printMenu("1", "Place Ships Randomly");
	printMenu("2", "Place Ships Manually");
	printMenu("3", "Start Game");

	//redo menu printed until exit
	while (choice != 3) {
		choice = 0;
		scanf("%d", &choice);
		
		switch (choice) {
		case 1:
			//place ships randomly 
			randPlaceShips(P1);
			placed = 5;
			mode = 1;
			system("cls");
			printPlayer(P1);
			printf("\n");
			printMenu("1", "Redo");
			printMenu("2", "Move ships");
			printMenu("3", "Start Game");
			break;

		case 2:
			//manual placement
			placed = manPlaceShips(P1, mode);
			system("cls");
			printPlayer(P1);
			printf("\n");
			printMenu("1", "Place Ships Randomly");
			printMenu("2", "Place Ships Manually");
			printMenu("3", "Start Game");
			break;
		case 3:
			//exit
			break;
			
		}
	}

	return placed;
}

//player turn
void playerTurn(struct player* P1, struct player* P2) {
	int choice = 0;
	int x = rand() % 10 + 1;
	char y = (rand() % 10) + 'A';
	int hit = 0;
	int cont = 0;
	int sunk = 6;

	char enter = '0';

	system("cls");
	printPlayer(P1);
	printf("\n");
	printf("current selection: %c,%d\n", y, x);
	printMenu("1", "Enter attack coordinates");
	printMenu("2", "Confirm");

	while (choice != 3) {

		choice = 0;
		enter = '0';

		scanf("%d", &choice);

		switch (choice) {
		case 1:
			//get coordinates
			system("cls");
			printPlayer(P1);
			printf("\n");
			printf("enter coordinates (i.e. A,6) and press enter:\n");
			while (enter != '\n') {
				scanf(" %c,%d%c", &y, &x, &enter);
				
			}
			if (checkCell((x - 1), (y - 65), &P1->shots) == '~') {
				system("cls");
				printPlayer(P1);
				printf("\n");
				printf("current selection: %c,%d\n", y, x);
				printMenu("1", "Enter attack coordinates");
				printMenu("2", "Confirm");
			}
			else {
				system("cls");
				printPlayer(P1);
				printf("\n");
				printf("[Invalid coordinates]\n");
				printMenu("1", "Enter attack coordinates");
				printMenu("2", "Confirm");
			}
			break;

		case 2:
			//check cord, change value/update damage and exit
			if (checkCell((x - 1), (y - 65), &P1->shots) == '~') {
				//check if ship
				if (checkCell((x - 1), (y - 65), &P2->ships) != '~') {
					sunk = updateDamage(checkCell((x - 1), (y - 65), &P2->ships), P2);

					changeCell((x - 1), (y - 65), 'H', &P1->shots);
					changeCell((x - 1), (y - 65), 'H', &P2->ships);
					hit = 1;
					P1->stats.hits += 1;
				}
				//else log miss
				else {
					changeCell((x - 1), (y - 65), '#', &P1->shots);
					P1->stats.misses += 1;
				}
				choice = 3;
			}
			else {
				system("cls");
				printPlayer(P1);
				printf("\n");
				printf("[Invalid coordinates]\n");
				printMenu("1", "Enter attack coordinates");
				printMenu("2", "Confirm");
			}
			break;

		default:
			break;
		}
	}
	
	if (sunk < 6) {
		//print sunk ship
		system("cls");
		printPlayer(P1);
		printf("\n");
		printf("SUNK!");
		printShipName(sunk);
		printf("\n");
		printMenu("1", "continue");
	}
	else if (hit == 1) {
		//print hit
		logHit(x, (y - 65), P1->playerNumber);
		system("cls");
		printPlayer(P1);
		printf("\n");
		printf("[HIT! %c,%d]\n", y, x);
		printMenu("1", "continue");
		
	}
	else {
		//print miss
		logMiss(x, (y - 65), P1->playerNumber);
		system("cls");
		printPlayer(P1);
		printf("\n");
		printf("[MISS %c,%d]\n", y, x);
		printMenu("1", "continue");
		
	}
	while (cont != 1) {
		scanf("%d", &cont);
	}
	
	

}

//automated turn
void autoTurn(struct player* P1, struct player* P2, int delayTime, int hidden) {
	int hit = 0;
	int sunk = 6;
	struct cord cord = {0, 0};

	system("cls");
	printPlayer(P1);
	printf("\n");
	printf("\n");
	printf("thinking...");

	char check = '0';

	cord = getRandCords(&P1->shots);

	check = checkCell(cord.x, cord.y, &P2->ships);

	if (check != '~') {

		sunk = updateDamage(check, P2);

		changeCell(cord.x, cord.y, 'H', &P1->shots);
		changeCell(cord.x, cord.y, 'H', &P2->ships);
		hit = 1;

		P1->stats.hits += 1;
	}
	else {
		changeCell(cord.x, cord.y, '#', &P1->shots);

		P2->stats.misses += 1;
	}
	updateEnt(cord.x, cord.y, hit, &P1->shots);

	if (sunk < 6) {
		//print sunk ship
		system("cls");
		if (hidden == 1) {
			printPlayer(P2);
		}
		else
		{
			printPlayer(P1);
		}
		printf("\n");
		printf("[Computer player %d]\n", P1->playerNumber);
		printf("SUNK!");
		printShipName(sunk);
		printf("\n");
	}
	else if (hit == 1) {
		logHit(cord.x, cord.y, P1->playerNumber);
		system("cls");
		if (hidden == 1) {
			printPlayer(P2);
		}
		else
		{
			printPlayer(P1);
		}
		printf("\n");
		printf("[Computer player %d]\n", P1->playerNumber);
		printf("[HIT! %c,%d]\n", cord.y+65, cord.x + 1);
	}
	else {
		logMiss(cord.x, cord.y, P1->playerNumber);
		system("cls");
		if (hidden == 1) {
			printPlayer(P2);
		}
		else
		{
			printPlayer(P1);
		}
		printf("\n");
		printf("[Computer player %d]\n", P1->playerNumber);
		printf("[MISS %c,%d]\n", cord.y+65, cord.x + 1);

	}
	delay(delayTime);

}

//game loop
void gameloop() {
	struct player P1;
	struct player P2;

	initPlayer(&P1, 1);
	initPlayer(&P2, 2);

	int win = 0;
	int placed = 0;

	while (win == 0) {
		if (placed < 5) {
			placed = menuShips(&P1, &P2);
		}
		else {
			//player turn
			playerTurn(&P1, &P2);
			//check win
			win = checkWin(&P1, &P2);
			if (win == 0) {
				//computer turn
				autoTurn(&P2, &P1, 5, 1);
				//check win
				win = checkWin(&P1, &P2);
			}
			
		}

	}
	
	//print endboard here
	system("cls");
	printf("\n");
	printEndGrids(&P1, &P2);
	printf("\n");
	printf("Player %d wins\n", win);
	printMenu("1", "Exit");

	while (placed == 5) {
		scanf("%d", &placed);
	}
}

//simulation loop
void simLoop(int delayTime) {
	struct player P1;
	struct player P2;

	initPlayer(&P1, 1);
	initPlayer(&P2, 2);

	int win = 0;
	int placed = 0;

	while (win == 0) {
		if (placed < 5) {
			randPlaceShips(&P1);
			randPlaceShips(&P2);
			placed = 5;
		}
		else {
			//computer turn P1
			autoTurn(&P1, &P2, delayTime, 0);
			//check win
			win = checkWin(&P1, &P2);
			if (win == 0) {
				//computer turn P2
				autoTurn(&P2, &P1, delayTime, 0);
				//check win
				win = checkWin(&P1, &P2);
			}

		}

	}
	//end log file
	logEnd(P1.stats);
	logEnd(P2.stats);

	//print endboard here
	system("cls");
	printf("\n");
	printEndGrids(&P1, &P2);
	printf("\n");
	printf("Player %d wins\n", win);
	printMenu("1", "Exit");

	while (placed == 5) {
		scanf("%d", &placed);
	}

}


//main menu
void menuMain() {
	system("cls");
	printTitle();
	printf("\n");
	printMenu("1", "Start Game");
	printMenu("2", "Simulation");
	printMenu("3", "Rules");
	printMenu("4", "Exit");

	int choice = 0;
	int delay = -1;

	while (choice != 4) {
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			//start game
			gameloop();
			system("cls");
			printTitle();
			printf("\n");
			printMenu("1", "Start Game");
			printMenu("2", "Simulation");
			printMenu("3", "Rules");
			printMenu("4", "Exit");
			break;
		case 2:
			//automation loop
			system("cls");
			printTitle();
			printf("\n");
			printf("please enter an int >=0 for delay between turns\n");
			while (delay < 0) {
				scanf("%d", &delay);
			}
			simLoop(delay);
			delay = -1;
			system("cls");
			printTitle();
			printf("\n");
			printMenu("1", "Start Game");
			printMenu("2", "Simulation");
			printMenu("3", "Rules");
			printMenu("4", "Exit");
			break;
		case 3:
			//print rules
			menuRules();
			//reprint main
			system("cls");
			printTitle();
			printf("\n");
			printMenu("1", "Start Game");
			printMenu("2", "Rules");
			printMenu("3", "Exit");
			break;
		case 4:
			//exit
			break;
		default:
			break;
		}
	}
}

//rules menu
void menuRules() {
	system("cls");
	printRules();
	printf("\n");
	printMenu("1", "Exit");

	int choice = 0;

	while (choice != 1) {
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			//exit
			break;
		default:
			break;
		}
	}
}