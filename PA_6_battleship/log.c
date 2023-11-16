#include "log.h"

//init stats struct
void initStats(struct stats* stats, int player) {
    char buff[20];
    struct tm* sTm;

    time_t now = time(0);
    sTm = gmtime(&now);

    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    stats->player = player;
    
    strcpy(stats->timeStarted, buff);
    stats->hits = 0;
    stats->misses = 0;
    stats->shots = 0;
    stats->ratio = 0;
    stats->win = 0;
}

//convert to grid letter
char convertRow(int yCord) {
    char converted = yCord + 65;
    return converted;
}

//log a hit
void logHit(int x, int y, int player) {
    FILE* log;
    log = fopen(LOGFILE, "a");
    if (log == NULL) {
        log = fopen(LOGFILE, "a");
        if (log == NULL) {
            printf("error opening log file\n");
        }
    }
    else {
        char buff[20];
        struct tm* sTm;

        time_t now = time(0);
        sTm = gmtime(&now);

        strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
        fprintf(log, "[%s], %d, %6c, %2d, HIT\n", buff, player, convertRow(y), x);

        fclose(log);
    }

    
}

//log a miss
void logMiss(int x, int y, int player) {
    FILE* log;
    log = fopen(LOGFILE, "a");
    if (log == NULL) {
        log = fopen(LOGFILE, "a");
        if (log == NULL) {
            printf("error opening log file\n");
        }
    }
    else {
        char buff[20];
        struct tm* sTm;

        time_t now = time(0);
        sTm = gmtime(&now);

        strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
        fprintf(log, "[%s], %d, %6c, %2d, MISS\n", buff, player, convertRow(y), x);

        fclose(log);
    }

    
}

//log sunk ship
void logSink(int player, char shipType) {

    char shipname[20] = "";

    switch (shipType) {
    case 'C':
        strcpy(shipname, "Carrier");
        break;
    case 'B':
        strcpy(shipname, "BattleShip");
        break;
    case 'c':
        strcpy(shipname, "Cruiser");
        break;
    case 'S':
        strcpy(shipname, "Submarine");
        break;
    case 'D':
        strcpy(shipname, "Destroyer");
        break;
    }

    FILE* log;
    log = fopen(LOGFILE, "a");
    if (log == NULL) {
        log = fopen(LOGFILE, "a");
        if (log == NULL) {
            printf("error opening log file\n");
        }
    }
    else {
        char buff[20];
        struct tm* sTm;

        time_t now = time(0);
        sTm = gmtime(&now);

        strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
        fprintf(log, "[%s], %d, %6s, SUNK\n", buff, player, shipname);

        fclose(log);
    }

    
}

//End session log
void logEnd(struct stats stats) {

    FILE* log;
    log = fopen(LOGFILE, "a");
    if (log == NULL) {
        log = fopen(LOGFILE, "a");
        if (log == NULL) {
            printf("error opening log file\n");
        }
    }
    else {
        char buff[20];
        struct tm* sTm;

        time_t now = time(0);
        sTm = gmtime(&now);

        strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

        double ratio = (stats.hits / stats.misses) * 100;

        fprintf(log, "Start,End,Player,Hits,Miss,Ratio,Win\n");
        fprintf(log, "[%s],[%s], %d, %.0lf, %.0lf, %.2lf%%,  %d\n", stats.timeStarted, buff, stats.player, stats.hits, stats.shots, ratio, stats.win);

        fclose(log);
    }

    

}