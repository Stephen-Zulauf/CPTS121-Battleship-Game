#ifndef SHIPS_H
#define SHIPS_H

/*
0-carrier
1-battleShip
2-cruiser
3-sub
4-destroyer
*/

//ship struct
struct ship {
	char values[25];
};

//get ship struct
void getShip(struct ship* ship, int type, int rotation);


#endif // !SHIPS_H