#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct matchDetails {
    // teams[0] -> first team; teams[1] -> second team
    char teamA_name[35];
    char teamB_name[35];
    int teamA_score;
    int teamB_score;
    // all three arrays bellow correspond to each others' indexes
    char scorer[20][20];
    char scorer_id[20];
    int scorer_time[20];
} Match;

typedef struct tournaments {
    char name[35];
    int num_teams;
    char name_teams[10][35];
    int num_matches;
    Match matches[100];
} Tour;

void anyKey();
void printHeader();
void mainMenu(Tour* ptr, int n);
void calcStandings(Tour* ptr, int n);
void showTournamentDetails(Tour* ptr, int n);
void showPrevStandings(Tour* ptr, int n);
void showPrevMatchHistory(Tour* ptr, int n);
void helpMenu(Tour* ptr, int n);
void exitProgram(Tour* ptr, int n);

#endif