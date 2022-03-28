#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

int inputArrowKey()
{
    int input = getch();
    if (input == 0 || input == 0xE0)
    {
        input = getch();
    }
        switch(input)
        {
            case 72: 
                return 1; // Arrow Up
                break;
            case 75:
                return 2; // Arrow Right
                break;
            case 80:
                return 3; // Arrow Down
                break;
            case 77:
                return 4; // Arrow Left
                break;
            default:
                return inputArrowKey();
                break;
        }
}

void anyKey()
{
    printf("Press any key to continue...");
    getch();
    system("cls");
}

void clearAndPrintHeader(char* str) 
{
    system("cls");
    printf("<< Football Standings Program >>\n");
    printf("    << Some sub heading! >>");
    printf("\n\n >>> %s <<<\n", str);
}

void mainMenu(Tour* ptr, int n) 
{
    clearAndPrintHeader("Main Menu");
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
    int i, j, k;
    int match_num = 0;
    int invalid = 1;
    // add new space
    ptr = (Tour*) realloc (ptr, (n+1) * sizeof(Tour));
    // asking for tournament name
    clearAndPrintHeader("Input tournament's data");
    printf("Enter the tournament name:\n");
    printf(">> ");
    scanf("%[^\n]s", ptr[n].name);
    fflush(stdin);
    // asking for number of teams that are participating in that tourney
    while (invalid == 1) 
    {   
        clearAndPrintHeader("Input tournament's data");
        puts("How many teams participated?");
        printf(">> ");
        scanf("%d", &ptr[n].num_teams);
        fflush(stdin);
        if (ptr[n].num_teams > 10 || ptr[n].num_teams < 2)
        {
            puts("\nThe number you entered was invalid!");
            puts("Enter a minimum of 2 teams and a maximum of 10 teams!");
            anyKey();
            continue;
        }
        invalid = 0;
    }
    ptr[n].num_matches = ptr[n].num_teams * (ptr[n].num_teams - 1)/2;
    // asking for the names of those teams
    clearAndPrintHeader("Input tournament's data");
    printf("Enter the name of the teams that participated:\n");
    for (i = 0; i < ptr[n].num_teams; i++) 
    {
        printf("Team %d:\n", i+1);
        printf(">> ");
        scanf("%[^\n]s", ptr[n].name_teams[i]);
        fflush(stdin);
    }

    for (i = 0; i < ptr[n].num_teams; i++)
    {
        for (j = i+1; j < ptr[n].num_teams; j++) 
        {
            clearAndPrintHeader("Input tournament's data");
            // print match overview
            printf("\nMatch %d:\n", match_num+1);
            strcpy(ptr[n].matches[match_num].teamA_name, ptr[n].name_teams[i]);
            strcpy(ptr[n].matches[match_num].teamB_name, ptr[n].name_teams[j]);
            printf(
                ">> %s VS %s <<\n",
                ptr[n].matches[match_num].teamA_name,
                ptr[n].matches[match_num].teamB_name
            );
            // ask for details of goals
            printf("How many goals did %s score?\n", ptr[n].matches[match_num].teamA_name);
            printf(">> ");
            scanf("%d", &ptr[n].matches[match_num].teamA_score);
            printf("How many goals did %s score?\n", ptr[n].matches[match_num].teamB_name);
            printf(">> ");
            scanf("%d", &ptr[n].matches[match_num].teamB_score);
            fflush(stdin);
            // keep track of total goals in the match
            ptr[n].matches[match_num].total_goals =
            ptr[n].matches[match_num].teamB_score + ptr[n].matches[match_num].teamA_score;
            // clear screen and ask for details of each goal (or skip)
            clearAndPrintHeader("Input tournament's data");
            printf("Do you want to input the details of the goals?\n");
            printf("1. Yes, the scorer only\n");
            printf("2. Yes, the time only\n");
            printf("3. Yes, both the scorer and the time\n");
            printf("4. No\n");
            printf(">> ");
            switch (getch())
            {
                case '1':
                    ptr[n].matches[match_num].input_status = 1;
                    break;
                case '2':
                    ptr[n].matches[match_num].input_status = 2;
                    break;
                case '3':
                    ptr[n].matches[match_num].input_status = 3;
                    break;
                case '4':
                    ptr[n].matches[match_num].input_status = 4;
                    break;
                default:
                    ptr[n].matches[match_num].input_status = 4;
                    break;
            }
            // asking for goals' details
            for (k = 0; k < ptr[n].matches[match_num].total_goals; k++) 
            {
                clearAndPrintHeader("Input tournament's data");
                printf("\nMatch %d:\n", match_num+1);
                printf(
                    ">> %s VS %s <<\n",
                    ptr[n].matches[match_num].teamA_name,
                    ptr[n].matches[match_num].teamB_name
                );
                printf("Goal No-%d:\n", k+1);
                strcpy(ptr[n].matches[match_num].scorer[k], "Unknown");
                ptr[n].matches[match_num].goal_time[k] = -1;
                if (ptr[n].matches[match_num].input_status == 1 ||
                    ptr[n].matches[match_num].input_status == 3)
                {
                    printf("Scorer's name:\n");
                    printf(">> ");
                    scanf("%[^\n]s", ptr[n].matches[match_num].scorer[k]);
                    fflush(stdin);
                }
                if (ptr[n].matches[match_num].input_status == 2 ||
                    ptr[n].matches[match_num].input_status == 3)
                {
                    printf("When was the goal scored? (minutes into the game):\n");
                    printf(">> ");
                    scanf("%d", &ptr[n].matches[match_num].goal_time[k]);
                    fflush(stdin);
                }                
            }
            // increment match number
            match_num++;
        }
    }

}

void showTournamentDetails(Tour* ptr, int n) 
{
    int i;
    clearAndPrintHeader("Tournament Details");
    printf(">> %s <<\n", ptr[n].name);
    printf("Number of teams: %d\n", ptr[n].num_teams);
    puts("Teams that participated:");
    for (i = 0; i < ptr[n].num_teams; i++) 
    {
        printf(" - %s\n", ptr[n].name_teams[i]);
    }
    printf("Number of matches: %d\n", ptr[n].num_matches);
}

void showMatchDetails(Tour* ptr, int n, int match_num)
{
    int i;
    // print the header
    clearAndPrintHeader("Match Details");
    printf("Tournament: %s\n", ptr[n].name);
    printf(
        ">> %s VS %s <<\n",
        ptr[n].matches[match_num].teamA_name,
        ptr[n].matches[match_num].teamB_name
    );
    // add 2 extra space
    printf("  ");
    // print as long as team A's name above
    for (i = 0; i < strlen(ptr[n].matches[match_num].teamA_name); i++)
    {
        printf(" ");
    }
    printf("%d - %d", 
        ptr[n].matches[match_num].teamA_score,
        ptr[n].matches[match_num].teamB_score
    );
    printf("\n\nGoal Details:\n");
    for (i = 0; i < ptr[n].matches[match_num].total_goals; i++)
    {   
        if (ptr[n].matches[match_num].input_status != 4)
        {
            printf(" - %s ", ptr[n].matches[match_num].scorer[i]);
            if (ptr[n].matches[match_num].goal_time[i] != -1)
            {
                printf("(%d')", ptr[n].matches[match_num].goal_time[i]);
            }
            printf("\n");
        } 
        else
        {
            printf("-");
            break;
        }
    }
}
