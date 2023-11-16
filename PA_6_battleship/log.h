#ifndef LOG_H
#define LOG_H

#define _CRT_SECURE_NO_WARNINGS

#define LOGFILE "LogFile.xls"

#include<stdio.h>
#include <time.h>
#include<string.h>

//struct for stats at end of log
struct stats {
	int player;
	char timeStarted[20];
	char timeEnded[20];
	double hits;
	double misses;
	double shots;
	double ratio;
	int win;
};

//init stats struct
void initStats(struct stats* stats,int player);

//convert to grid letter
char convertRow(int yCord);

//log a hit
void logHit(int x, int y, int player);

//log a miss
void logMiss(int x, int y, int player);

//log sunk ship
void logSink(int player, char shipType);

//End session log
void logEnd(struct stats stats);


#endif // !LOG_H

