#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

void printHeader() 
{
    printf("      << Football Standings Program >>\n\n");
}

void mainMenu() 
{
    printHeader("Main Menu");
    /*
    Calculate standings of a new competition
    See previous competitions' standings
    See previous competitions' match history
    Help
    Exit
    */
    puts(">> Main Menu <<");
    puts("1. Calculate standings of a new competition");
    puts("2. See previous competitions' standings");
    puts("3. See previous competitions' match history");
    puts("4. Help");
    puts("5. Exit");
    printf("Enter the desired menu: ");
    int choice = getch();
    switch(choice) 
    {
        case '1':
            // calcStandings();
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
    }

}

void calcStandings() {
    /*
    "Enter the tournament name: {tournament_name}"
    "How many matches are there? {num_of_matches}"
    (show every possible matchup and ask for data)
    "Number of goals: {num_of_goals}"
    "Who scored and at what time? {input}"
    (loop for every possible matchup)
    */
    printf("Enter the tournament name: ");
    printf("How many teams participated? ");
    
}