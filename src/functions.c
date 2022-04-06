#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"

int maxLength(char arr[][35]) // to call this function, array must be 35 in length
{   
    int i;
    int maxL = 0;
    int tempL = 0;
    int size = 20; // size -> is the max element of the arrays in the struct
    // check maxL (maxLength)
    for (i = 0; i < size; i++)
    {
        tempL  = strlen(arr[i]);
        if (maxL < tempL)
        {
            maxL = tempL;
        }
    }
    // return the max length of the array
    return maxL;
}

int inputArrowKey()
{
    int input = getch();
    // arrow keys will return these these two values
    if (input == 0 || input == 0xE0)
    {
        input = getch();
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
                break;
        } 
    }
    // if use presses q, then return -1
    else if (input == 113) // 'q' to quit
    {
        return (-1);
    }
    // if user presses other key then callback the function
    else
    {
        return inputArrowKey();
    }
}

void anyKey()
{
    // if a user presses any key -> clear the screen
    printf("Press any key to continue...");
    system("pause");
    system("cls");
}

void clearAndPrintHeader(char* str) 
{
    system("cls");
    printf(" =======================================\n");
    printf("       Football Standings Program\n");
    printf("            Some sub heading!\n");
    printf(" =======================================\n\n");
    // printf("<< Football Standings Program >>\n");
    // printf("    << Some sub heading! >>\n\n");

    // the string passed will get printed
    // if the user passes "" as a string, then the program will not print anything
    if (strcmp("", str) != 0)
        printf(" >>> %s <<<\n", str);
}

void mainMenu(Tour* ptr, int n) 
{
    // print the main menu
    clearAndPrintHeader("Main Menu");
    puts("1. Calculate standings of a new competition");
    puts("2. See previous competitions' standings");
    puts("3. See previous competitions' match history");
    puts("4. Help");
    puts("5. Exit");

    // get the input from the user
    puts("Enter the desired menu: ");
    printf(">> ");
    int choice = getch();
    // 
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
            exitMenu();
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

    // calculate number of matches that are going to be played in that tourney
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

    // for loop to zero every thing out in the struct
    for (i = 0; i < ptr[n].num_teams; i++) 
    {
        ptr[n].teams[i].games_played = 0;
        ptr[n].teams[i].wins = 0;
        ptr[n].teams[i].losses = 0;
        ptr[n].teams[i].draws = 0;
        ptr[n].teams[i].goals_for = 0;
        ptr[n].teams[i].goals_against = 0;
        ptr[n].teams[i].points = 0;
    }

    // for loops to ask for the scores of each match
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        for (j = i+1; j < ptr[n].num_teams; j++) 
        {
            // print header
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

            // INPUT details of goals
            // from team A
            printf("How many goals did %s score?\n", ptr[n].matches[match_num].teamA_name);
            printf(">> ");
            scanf("%d", &ptr[n].matches[match_num].teamA_score);
            // from team B
            printf("How many goals did %s score?\n", ptr[n].matches[match_num].teamB_name);
            printf(">> ");
            scanf("%d", &ptr[n].matches[match_num].teamB_score);
            fflush(stdin);

            // calculate the details for each category and points
            // for team A
            ptr[n].teams[i].games_played++;
            ptr[n].teams[i].wins += ptr[n].matches[match_num].teamA_score > ptr[n].matches[match_num].teamB_score;
            ptr[n].teams[i].draws += ptr[n].matches[match_num].teamA_score == ptr[n].matches[match_num].teamB_score;
            ptr[n].teams[i].losses += ptr[n].matches[match_num].teamA_score < ptr[n].matches[match_num].teamB_score;
            ptr[n].teams[i].goals_for += ptr[n].matches[match_num].teamA_score;
            ptr[n].teams[i].goals_against += ptr[n].matches[match_num].teamB_score;

            // for team B
            ptr[n].teams[j].games_played++;
            ptr[n].teams[j].wins += ptr[n].matches[match_num].teamB_score > ptr[n].matches[match_num].teamA_score;
            ptr[n].teams[j].draws += ptr[n].matches[match_num].teamB_score == ptr[n].matches[match_num].teamA_score;
            ptr[n].teams[j].losses += ptr[n].matches[match_num].teamB_score < ptr[n].matches[match_num].teamA_score;
            ptr[n].teams[j].goals_for += ptr[n].matches[match_num].teamB_score;
            ptr[n].teams[j].goals_against += ptr[n].matches[match_num].teamA_score;

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
            // switch case to check the input
            switch (getch())
            {
                case '1': // inpuy the scorer only
                    ptr[n].matches[match_num].input_status = 1;
                    break;
                case '2': // input the time only
                    ptr[n].matches[match_num].input_status = 2;
                    break;
                case '3': // input both the scorer and the time
                    ptr[n].matches[match_num].input_status = 3;
                    break;
                case '4': // skip
                    ptr[n].matches[match_num].input_status = 4;
                    break;
                default: // invalid input
                    ptr[n].matches[match_num].input_status = 4;
                    break;
            }
            // asking for goals' details
            for (k = 0; k < ptr[n].matches[match_num].total_goals; k++) 
            {
                // set unknown name as default of scorer
                strcpy(ptr[n].matches[match_num].scorer[k], "Unknown");
                // set -1 as deafult time of goal
                ptr[n].matches[match_num].goal_time[k] = -1;

                // if the input is 4 skip this whole block
                if (ptr[n].matches[match_num].input_status != 4)
                {
                    // print header and overview of the match
                    clearAndPrintHeader("Input tournament's data");
                    printf("\nMatch %d:\n", match_num+1);
                    printf(
                        ">> %s VS %s <<\n",
                        ptr[n].matches[match_num].teamA_name,
                        ptr[n].matches[match_num].teamB_name
                    );
                    // INPUT details of goals
                    printf("Goal No-%d:\n", k+1);      
                    // if the input is 1 or 3, ask for the scorer              
                    if (ptr[n].matches[match_num].input_status == 1 ||
                        ptr[n].matches[match_num].input_status == 3)
                    {
                        printf("Scorer's name:\n");
                        printf(">> ");
                        scanf("%[^\n]s", ptr[n].matches[match_num].scorer[k]);
                        fflush(stdin);
                    }
                    // if the input is 2 or 3, ask for the time
                    if (ptr[n].matches[match_num].input_status == 2 ||
                        ptr[n].matches[match_num].input_status == 3)
                    {
                        printf("When was the goal scored? (minutes into the game):\n");
                        printf(">> ");
                        scanf("%d", &ptr[n].matches[match_num].goal_time[k]);
                        fflush(stdin);
                    }
                }
                                
            }
            // increment match number
            match_num++;
        }
    }
    // input data (goal diff and points) to struct
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        ptr[n].teams[i].goal_difference = ptr[n].teams[i].goals_for - ptr[n].teams[i].goals_against;
        ptr[n].teams[i].points = (ptr[n].teams[i].wins * 3) + ptr[n].teams[i].draws;
    }
}

void showStandingsTable(Tour* ptr, int n)
{   
    int i, j;
    char header_str[40];
    strcpy(header_str, ptr[n].name);
    strcat(header_str, " Table");
    clearAndPrintHeader(header_str);
    int printL = (maxLength(ptr[n].name_teams)+1);

    // printing header for table
    // printing the team name header
    for (i = 0; i < (printL-9)/2; i++)
        printf(" ");
    printf("Team Name");
    for (i = 0; i < ((printL-9)/2)+2; i++)
        printf(" ");
    // printing other headers
    printf("   GP    W    D    L    F    A    GD    P");
    printf("\n===========================================================================");
    // printing the details for each team
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        // printing the team name column
        printf("\n%s", ptr[n].name_teams[i]);
        for (j = 0; j < printL-strlen(ptr[n].name_teams[i]); j++)
        {
            printf(" ");
        }
    }
}

void standingsMenu(Tour* ptr, int n)
{
    int target_index;
    //showStandingsTable
    printf("Searching Options\n");
    printf("1. Search by team name\n");
    printf("2. Search by ranking\n");
    printf("Enter your choice :\n");
    printf(">> ");
    switch(getch())
    {
        case '1':
            // search by team name
            break;
        case '2':
            printf("Enter your desired ranking position : \n");
            printf(">> ");
            scanf("%d", &target_index);
            target_index--;
            break;
        default :
            clearAndPrintHeader("");
            printf("Invalid input\n");
            anyKey();
            standingsMenu(ptr, n);
            return;
    }
    if (target_index < 0 || target_index > ptr[n].num_teams)
    {
        clearAndPrintHeader("");
        printf("\nTeam not found!\n");
        anyKey();
        standingsMenu(ptr, n);
    }
    else 
    {
        showTeamDetails(ptr, n, target_index);
    }
}

void showTeamDetails(Tour* ptr, int n, int team_index)
{
    clearAndPrintHeader("Team Details");
    printf("Tournament: %s\n", ptr[n].name);
    printf(">> %s <<\n", ptr[n].name_teams[team_index]);
    printf(" - Games Played: %d\n", ptr[n].teams[team_index].games_played);
    printf(" - Wins: %d\n", ptr[n].teams[team_index].wins);
    printf(" - Draws: %d\n", ptr[n].teams[team_index].draws);
    printf(" - Losses: %d\n", ptr[n].teams[team_index].losses);
    printf(" - Goals For: %d\n", ptr[n].teams[team_index].goals_for);
    printf(" - Goals Against: %d\n", ptr[n].teams[team_index].goals_against);
    printf(" - Goal Difference: %d\n", ptr[n].teams[team_index].goal_difference);
    printf(" - Points: %d\n", ptr[n].teams[team_index].points);
}

void search(char arr[][35], char target[], int return_index[11], int size) {
    int i, j, count = 0, count_index = 0, flag = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < strlen(arr[i]); j++) {
            if (count == 0) {
                // membandingkan dua karakter
                // jika sama akan count++
                if (arr[i][j] == target[count]) {
                    count++; // jika ketemu maka count++
                } 
            } else if (count != 0) { // kondisi saat count bukan 0
                // jika kedua karakter sama maka akan count++
                if (arr[i][j] == target[count]) { 
                    count++;
                } else if (arr[i][j] != target[count]) {
                    count = 0;
                }
            }
            // IF SUBSTRING IS FOUND 
            if (count == strlen(target)) { //jika count == jumlah target
                return_index[count_index] = i+1;
                count_index++;
                count = 0;
                flag = 1;
                break;
            }
        }
    }
    if (flag != 1)
    {
        return_index[10] = -1;
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

void showMatchDetails(Tour* ptr, int n, int match_num, int mode)
{   
    int i;
    // error handling if match number goes out of range
    if (match_num < 0) // goes under min
    {
        match_num = 0;
    } 
    else if (match_num >= ptr[n].num_matches) // goes above max
    {
        match_num = ptr[n].num_matches - 1;
    }
    // print the header
    clearAndPrintHeader("");
    // mode -> 1    ; enable scrolling through matches in a tournament
    // mode -> 0    ; disables scrolling
    if (mode == 1)
    {
        printf("\t<<\t%d/%d\t>>\n\n", match_num+1, ptr[n].num_matches);
    }
    printf(" >> Match Details << \n");
    printf("Tournament: %s\n", ptr[n].name);
    printf(
        ">> %s VS %s <<\n",
        ptr[n].matches[match_num].teamA_name,
        ptr[n].matches[match_num].teamB_name
    );
    // add an extra space
    printf(" ");
    // print as long as team A's name above for formatting purposes
    for (i = 0; i < strlen(ptr[n].matches[match_num].teamA_name); i++)
    {
        printf(" ");
    }
    printf(
        "%d  -  %d", 
        ptr[n].matches[match_num].teamA_score,
        ptr[n].matches[match_num].teamB_score
    );
    // print goal details
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
        else // if input status -> 4, dont print any details
        {
            printf("-\n");
            break;
        }
    }
    // in mode -> 1, enables scrolling with arrow keys
    if (mode == 1)
    {
        printf("\n(Press arrow keys to scroll through matches or press q to exit...)");
        switch(inputArrowKey()) // ask for arrow key input
        {
            case 1: case 2: // go to the left page
                showMatchDetails(ptr, n, match_num-1, mode);
                break;
            case 3: case 4: // go to the right page
                showMatchDetails(ptr, n, match_num+1, mode);
                break;
            case (-1): // press 'q' to exit
                mainMenu(ptr, n);
                // return;
                break;
            default:
                break;
        }

    }
}

void showPrevMatchHistory(Tour* ptr, int n)
{

}

void searchAndPickTeam(Tour* ptr, int n)
{
    int i, count = 0;
    char target_name[35];
    int index_team[11] = {0};
    clearAndPrintHeader("Search for a team");
    printf("Search for name of the team:\n");
    printf(">> ");
    scanf("%[^\n]s", target_name);
    clearAndPrintHeader("Search for a team");
    search(ptr[n].name_teams, target_name, index_team, ptr[n].num_teams);
    if (index_team[10] == -1)
    {
        printf("Team not found!\n");
    }
    else
    {
        printf("Below is the list of teams that match your search:\n");
        for (i = 0; i < ptr[n].num_teams; i++)
        {
            if (index_team[i] != 0)
            {
                count++;
                printf(" %d. %s\n", count, ptr[n].name_teams[index_team[i]-1]);
            }
        }
        for (i = 0; i < 11; i++)
        {
            printf("%d ", index_team[i]);
        }
        printf("\nChoose a team:\n");
        printf(">> ");
        scanf("%d", &i);
        showTeamDetails(ptr, n, index_team[i-1]-1);
    }
}

void exitMenu()
{
    clearAndPrintHeader("");
    printf("Thank you for using this program!\n");
    exit(0);
}

