#include "ships.h"

/*
0-carrier
1-battleShip
2-cruiser
3-sub
4-destroyer
*/
/*
0-0 180 degrees
1-90 270 degrees
*/

//get ship struct
void getShip(struct ship* ship, int type, int rotation) {
	int i, j;
	switch (type) {
	case 0:
		//0-carrier
		switch (rotation) {
		case 1:
			//90 deg 270
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (i == 0) {
						ship->values[5 * i + j] = 'C';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		default:
			//0 deg 180 deg
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (j == 0) {
						ship->values[5 * i + j] = 'C';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		}
		break;
	case 1:
		//1-battleShip
		switch (rotation) {
			//90 270
		case 1:
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (i == 0 && j != 4) {
						ship->values[5 * i + j] = 'B';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		default:
			//0 90
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (j == 0 && i != 4) {
						ship->values[5 * i + j] = 'B';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		}

		break;
	case 2:
		//2-cruiser
		switch (rotation) {
		case 1:
			//90 270 deg
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (i == 0 && j < 3) {
						ship->values[5 * i + j] = 'c';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		default:
			//0 deg 90 deg
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (j == 0 && i < 3) {
						ship->values[5 * i + j] = 'c';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		}

		break;
	case 3:
		//3 - sub
		switch (rotation) {
		case 1:
			//90 deg 270 deg
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (i == 0 && j < 3) {
						ship->values[5 * i + j] = 'S';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		
		default:
			//0 180 deg
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (j == 0 && i < 3) {
						ship->values[5 * i + j] = 'S';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		}
		break;
	case 4:
		//4-destroyer
		switch (rotation) {
		case 1:
			//90 deg
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (i == 0 && j < 2) {
						ship->values[5 * i + j] = 'D';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		default:
			//0 180 deg
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (j == 0 && i < 2) {
						ship->values[5 * i + j] = 'D';
					}
					else {
						ship->values[5 * i + j] = '~';
					}
				}
			}
			break;
		}
	}
}
