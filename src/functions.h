#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct matchDetails {
    char teams[2][20]; // teams[0] -> first team; teams[1] -> second team
    // all three arrays bellow correspond to each others' indexes
    int score[2];
    char scorer[11][20];
    char scorerId[11];
    int scorerTime[11];
} Match;

typedef struct tournaments {
    char *name;
    int num_teams;
    Match matches[100];
} Tournament;


void printHeader();
void mainMenu();
void standingsMenu();
void showPrevStandings();
void showPrevMatchHistory();
void helpMenu();
void exitProgram();

#endif