#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// struct definitions

// struct to store the details of a match
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

// struct to store the details of a team
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

// struct to store the details of a tournament
// with nested structs inside
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

// print the welcome screen of the program
void welcomeScreen();
// print loading bar
void showLoadingBar();
// return the max length of an array of strings
int maxLength(char arr[][35]);
// return an integer based on the arrow keys pressed
int inputArrowKey();
// when user presses any key the screen will be cleared
void anyKey();
// clear and print program header + menu header based on the string passed
void clearAndPrintHeader(char* str);
// to dipslay the main menu of the program
void mainMenu(Tour* ptr, int n);
// get the details of a tournament and calculate standings
void calcStandings(Tour* ptr, int n);
// print the standings table of a tournament
void showStandingsTable(Tour* ptr, int n);
// to display the standings menu
void standingsMenu(Tour* ptr, int n, int tour_index);
// print the details of a team in a tournament
void showTeamDetails(Tour* ptr, int n, int team_index);
// searcrh teams using a substring and return the index of the teams
void search(char arr[][35], char target[], int return_index[11], int size);
// to print the details of a tournament
void showTournamentDetails(Tour* ptr, int n);
// to print the details of a match
void showMatchDetails(Tour* ptr, int n, int match_num, char* mode);
// print the menu to show previous tournaments' standings
void showPrevStandings(Tour* ptr, int n);
// function that calls the search algorithm and get search suggestions based on that
int searchAndPickTeam(Tour* ptr, int n);
// get team index from team rankings inputted by the user
int getIndexFromRank(Tour* ptr, int n, int team_rank);
// swap two adjacent team structs used in bubble sort
void swapAdjacentTeams(Tour* ptr, int n, int j);
// sort teams based on points and goal difference
void sortTeamsByRank(Tour* ptr, int n, int size, char* mode);
// function to set the rankings of teams based on their sorted index
void setRankings(Tour* ptr, int n, char* mode);
// print the help menu in main
void helpMainMenu(Tour* ptr, int n);
// print the help menu in standings
void helpStandingsMenu();
// print the about menu in main menu
void aboutMenu(Tour* ptr, int n);
// print the exit menu in main menu
void exitMenu();

#endif