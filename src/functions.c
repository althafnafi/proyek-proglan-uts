#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

void printHeader(char* string) 
{
    system("cls");
    printf("      << Football Standings Program >>\n\n");
    printf(">>> %s <<<\n", string);
}

void mainMenu(Tour* ptr, int n) 
{
    printHeader("Main Menu");
    puts("1. Calculate standings of a new competition");
    puts("2. See previous competitions' standings");
    puts("3. See previous competitions' match history");
    puts("4. Help");
    puts("5. Exit");
    puts("Enter the desired menu: ");
    printf(">> ");
    int choice = getch();
    switch(choice) 
    {
        case '1':
            calcStandings(ptr, n);
            break;
        case '2':
            // showPrevStandings();
            break;
        case '3':
            // showPrevMatchHistory();
            break;
        case '4':
            // helpMenu();
            break;
        case '5':
            // exitProgram();
            break;
        default:
            mainMenu(ptr, n);
            break;
    }

}

void calcStandings(Tour* ptr, int n) 
{
    int i;
    int invalid = 1;
    ptr = (Tour*) realloc (ptr, (n+1) * sizeof(Tour));
    /*
    "Enter the tournament name: {tournament_name}"
    "How many matches are there? {num_of_matches}"
    (show every possible matchup and ask for data)
    "Number of goals: {num_of_goals}"
    "Who scored and at what time? {input}"
    (loop for every possible matchup)
    */
   
    // asking for tournament name
    printHeader("Input tournament's data");
    printf("Enter the tournament name:\n");
    printf(">> ");
    scanf("%[^\n]s", ptr[n].name);
    fflush(stdin);
    // asking for number of teams that are participating in that tourney
    printHeader("Input tournament's data");
    while (invalid == 1) 
    {   
        puts("How many teams participated?");
        printf(">> ");
        scanf("%d", &ptr[n].num_teams);
        fflush(stdin);
        if (ptr[n].num_teams > 10 || ptr[n].num_teams < 2)
        {
            puts("The number you entered was invalid!");
            puts("Enter a minimum of 2 teams and a maximum of 10 teams!");
            continue;
        }
        invalid = 0;
    }
    ptr[n].num_matches = ptr[n].num_teams * (ptr[n].num_teams - 1)/2;
    // asking for the names of those teams
    printHeader("Input tournament's data");
    printf("Enter the name of the teams that participated:\n");
    for (i = 0; i < ptr[n].num_teams; i++) 
    {
        printf("Team %d:\n", i+1);
        printf(">> ");
        scanf("%[^\n]s", ptr[n].name_teams[i]);
        fflush(stdin);
    }
    
}

void showTournamentDetails(Tour* ptr, int n) 
{
    int i;
    printHeader("Tournament Details");
    printf("\n>> %s <<\n", ptr[n].name);
    printf("Number of teams: %d\n", ptr[n].num_teams);
    puts("Teams that participated:");
    for (i = 0; i < ptr[n].num_teams; i++) 
    {
        printf(" - %s\n", ptr[n].name_teams[i]);
    }
    printf("Number of matches: %d\n", ptr[n].num_matches);
}



