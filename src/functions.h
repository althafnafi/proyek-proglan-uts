#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct matchDetails 
{
    // teams[0] -> first team; teams[1] -> second team
    char teamA_name[35];
    char teamB_name[35];
    int teamA_score;
    int teamB_score;
    int total_goals;
    // all three arrays bellow correspond to each others' indexes
    char scorer[20][35];
    char scorer_id[20]; // show which the team scorer is from
    int goal_time[20];
    // input status;
    int input_status;
} Match;

typedef struct teams 
{
    char name[35];
    int games_played; // increment
    int wins; // if 
    int draws; // if 
    int losses; // if
    int goals_for; // increment
    int goals_against; // increment
    int goal_difference; // goals_for - goals_against
    int points;
    int rank;
} Team;

typedef struct tournaments 
{
    char name[35];
    int num_teams;
    char name_teams[10][35];
    int num_matches;
    Match matches[50];
    Team teams[10];
} Tour;

// function prototypes

// return the max length of an array of strings
int maxLength(char arr[][35]);
// return an int based on the arrow keys pressed
int inputArrowKey();
// when user presses any key the screen will be cleared
void anyKey();
// clear and print program header + menu header based on the str passed
void clearAndPrintHeader(char* str);
// to dipslay the main menu of the program
void mainMenu(Tour* ptr, int n);
// ask the details of a tournament and calculate the standings
void calcStandings(Tour* ptr, int n);
// print the standings table of a tournament
void showStandingsTable(Tour* ptr, int n);
// to display the standings menu
void standingsMenu(Tour* ptr, int n);

void showTeamDetails(Tour* ptr, int n, int team_index);
//searching algorithm used
void search(char arr[][35], char target[], int return_index[11], int size);
// to print the details of a tournament
void showTournamentDetails(Tour* ptr, int n);
// to print the details of a match
void showMatchDetails(Tour* ptr, int n, int match_num, char* mode);

void showPrevMatchHistory(Tour* ptr, int n);

void showPrevStandings(Tour* ptr, int n);

int searchAndPickTeam(Tour* ptr, int n);

int getIndexFromRank(Tour* ptr, int n, int team_rank);

void sortTeamsByRank(Tour* ptr, int n, char* mode);

void helpMainMenu(Tour* ptr, int n);

void exitMenu();

#endif