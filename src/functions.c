#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
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
    return 0;
}

void anyKey()
{
    // if a user presses any key -> clear the screen
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
    printf("%d\n", n);
    puts("1. Calculate standings of a new competition");
    puts("2. See previous competitions' standings");
    puts("3. See previous competitions' match history");
    puts("4. Help");
    puts("5. Exit the program");

    // get the input from the user
    puts("Enter the desired menu: ");
    printf(">> ");
    int choice = getch();
    // will call functions based on the input
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
    fflush(stdin);
    // add new space
    n++;
    ptr = (Tour*) realloc (ptr, (n+1) * sizeof(Tour));

    // asking for tournament name
    clearAndPrintHeader("Input tournament's data");
    printf("%d\n", n);
    printf("Enter the tournament name:\n");
    printf(">> ");
    fflush(stdin);
    scanf("%[^\n]s", ptr[n].name);
    fflush(stdin);

    // asking for number of teams that are participating in that tourney
    while (invalid == 1) 
    {   
        clearAndPrintHeader("Input tournament's data");
        puts("How many teams participated?");
        printf(">> ");
        scanf("%d", &ptr[n].num_teams);
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
        fflush(stdin);
        scanf("%[^\n]s", ptr[n].name_teams[i]);
        strcpy(ptr[n].teams[i].name, ptr[n].name_teams[i]);
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
                        fflush(stdin);
                        scanf("%[^\n]s", ptr[n].matches[match_num].scorer[k]);
                    }
                    // if the input is 2 or 3, ask for the time
                    if (ptr[n].matches[match_num].input_status == 2 ||
                        ptr[n].matches[match_num].input_status == 3)
                    {
                        printf("When was the goal scored? (minutes into the game):\n");
                        printf(">> ");
                        scanf("%d", &ptr[n].matches[match_num].goal_time[k]);
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

    standingsMenu(ptr, n);
}

void showStandingsTable(Tour* ptr, int n)
{
    int i, j;
    int printL;

    if (maxLength(ptr[n].name_teams) <= 9)
        printL = 11;
    else
        printL = (maxLength(ptr[n].name_teams));

    // printing header for table
    // printing the team name header
    printf("+");
    for (i = 0; i < printL+57; i++)
    {
        printf("-");
    }
    printf("+\n");
    printf("|");


    printf(" Rank  ");
    // print "Team Name and the spaces beside it based on the max length of the team name"
    for (i = 0; i < floor(((float)printL-9)/2); i++)
        printf(" ");
    printf("Team Name");
    for (i = 0; i < ceil(((float)printL-9)/2); i++)
        printf(" ");

    // printing other headers
    printf("%8s%5s%5s%5s%6s%6s%6s%8s |","GP", "W", "D", "L", "GF", "GA", "GD", "Pts");
    printf("\n+");
    for (i = 0; i < printL+57; i++)
    {
        printf("=");
    }
    printf("+");

    // printing the details for each team
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        // printing the team name column
        printf("\n| %2d", ptr[n].teams[i].rank);
        printf("     %s", ptr[n].name_teams[i]);
        for (j = 0; j < printL-strlen(ptr[n].name_teams[i]); j++)
        {
            printf(" ");
        }
        // printing the other columns
        printf("%7d%5d%5d%5d%6d%6d%6d%7d  |",
            ptr[n].teams[i].games_played,
            ptr[n].teams[i].wins,
            ptr[n].teams[i].draws,
            ptr[n].teams[i].losses,
            ptr[n].teams[i].goals_for,
            ptr[n].teams[i].goals_against,
            ptr[n].teams[i].goal_difference,
            ptr[n].teams[i].points
        );
    }
    printf("\n+");
    for (i = 0; i < printL+57; i++)
    {
        printf("-");
    }
    printf("+\n");
}

void standingsMenu(Tour* ptr, int n)
{
    int target_index;
    int target_rank;
    char header_str[40];

    // sort based on points
    sortTeamsByRank(ptr, n, "desc");

    strcpy(header_str, ptr[n].name);
    strcat(header_str, " Table");
    clearAndPrintHeader(header_str);
    showStandingsTable(ptr, n);
    printf("\n >> Menu Options <<\n");
    printf("1. Search by team name\n");
    printf("2. Search by ranking\n");
    printf("3. Show match details\n");
    printf("4. Help\n");
    printf("5. Exit to main menu\n");
    printf("Enter your choice :\n");
    printf(">> ");
    switch(getch())
    {
        case '1':
            target_index = searchAndPickTeam(ptr, n);
            if (target_index == -1)
            {
                standingsMenu(ptr, n);
                break;
            }
            showTeamDetails(ptr, n, target_index);
            printf("\nPress any key to go back... ");
            getch();
            standingsMenu(ptr, n);
            break;
        case '2':
            clearAndPrintHeader(header_str);
            showStandingsTable(ptr, n);
            printf("\nEnter your desired ranking position : \n");
            printf(">> ");
            scanf("%d", &target_rank);
            target_index = getIndexFromRank(ptr, n, target_rank);
            if (target_index == -1)
            {
                printf("\nInvalid ranking position!\n");
                anyKey();
                standingsMenu(ptr, n);
                break;
            }
            showTeamDetails(ptr, n, target_index);
            printf("\nPress any key to go back... ");
            getch();
            standingsMenu(ptr, n);
            break;
        case '3':
            // show match details w/ "scroll"
            showMatchDetails(ptr, n, 0, "scroll");
            standingsMenu(ptr, n);
            break;
        case '4':
            // go to help menu
            helpStandingsMenu();
            standingsMenu(ptr, n);
            break;
        case '5':
            // exit to main menu
            mainMenu(ptr, n);
            break;
        default :
            standingsMenu(ptr, n);
            break;
    }
}

void showTeamDetails(Tour* ptr, int n, int team_index)
{
    clearAndPrintHeader("Team Details");
    printf("\nTournament: %s\n", ptr[n].name);
    printf(">> %s (Rank %d) <<\n", 
            ptr[n].teams[team_index].name,
            ptr[n].teams[team_index].rank
    );
    printf(" - Games Played: %d\n", ptr[n].teams[team_index].games_played);
    printf(" - Wins\t: %d\n", ptr[n].teams[team_index].wins);
    printf(" - Draws\t: %d\n", ptr[n].teams[team_index].draws);
    printf(" - Losses\t: %d\n", ptr[n].teams[team_index].losses);
    printf(" - Goals For\t: %d\n", ptr[n].teams[team_index].goals_for);
    printf(" - Goals Against\t: %d\n", ptr[n].teams[team_index].goals_against);
    printf(" - Goal Diff.\t: %d\n", ptr[n].teams[team_index].goal_difference);
    printf(" - Points\t: %d\n", ptr[n].teams[team_index].points);
}

void search(char arr[][35], char target[], int return_index[11], int size)
{
    // this search function will return the index of the team in the array
    // if the substring is found
    int i, j, count = 0, count_index = 0, flag = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < strlen(arr[i]); j++) {
            if (count == 0) 
            {
                // if the first character of the string is the same as the target
                // increment count
                if (arr[i][j] == target[count]) 
                    count++; 
            } 
            else if (count != 0) 
            {   
                // if the character is the same as the target for the second time and so on
                // increment count again
                if (arr[i][j] == target[count]) 
                    count++;
                // if the character is not the same as the target
                // reset count and start over
                else if (arr[i][j] != target[count]) 
                    count = 0;
            
            }
            // If the substring is found in the string
            // return the array containing the index of the team
            if (count == strlen(target)) 
            {
                return_index[count_index] = i+1;
                count_index++;
                count = 0;
                flag = 1;
                break;
            }
        }
    }
    // flag = 0 means the target is not found
    // and will set the last index of the return index
    // which is the status element of the array to -1
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

void showMatchDetails(Tour* ptr, int n, int match_num, char* mode)
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
    if (strcmp(mode, "scroll") == 0)
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
    // in mode -> "scroll", enables scrolling with arrow keys
    if (strcmp(mode, "scroll") == 0)
    {
        printf("\n(Press arrow keys to scroll through matches or press q to exit...)\n");
        switch(inputArrowKey()) // ask for arrow key input
        {
            case 1: case 2: // go to the left page
                showMatchDetails(ptr, n, match_num-1, mode);
                break;
            case 3: case 4: // go to the right page
                showMatchDetails(ptr, n, match_num+1, mode);
                break;
            case (-1): default: // press 'q' to exit
                return;
        }

    }
}

void showPrevMatchHistory(Tour* ptr, int n)
{
    
}

int searchAndPickTeam(Tour* ptr, int n)
{
    int input = 0;
    int i, count;
    char target_name[35];
    int index_team[11] = {0};
    clearAndPrintHeader("Search for a team");
    printf("Search for name of the team:\n");
    printf(">> ");
    fflush(stdin);
    scanf("%[^\n]s", target_name);
    search(ptr[n].name_teams, target_name, index_team, ptr[n].num_teams);

    if (index_team[10] == -1)
    {
        clearAndPrintHeader("Search for a team");
        printf("Team not found!\n");
        anyKey();
        return -1;
    }

    while (input < 1 || input > count)
    {
        count = 0;
        clearAndPrintHeader("Search for a team");
        printf("Below is the list of teams that match your search:\n");
        for (i = 0; i < ptr[n].num_teams; i++)
        {
            if (index_team[i] != 0)
            {
                count++;
                printf(" %d. %s\n", count, ptr[n].name_teams[index_team[i]-1]);
            }
        }

        printf("\nChoose a team:\n");
        printf(">> ");
        scanf("%d", &input);

        if (input < 1 || input > count)
        {
            printf("\nInvalid input!\n");
            anyKey();
        }
        else
        {
            return index_team[input-1]-1;
        }
    }
    return -1;  
}

int getIndexFromRank(Tour* ptr, int n, int team_rank)
{   
    int i;
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        if (ptr[n].teams[i].rank == team_rank)
        {
            return i;
        }
    }
    return -1;
}

void sortTeamsByRank(Tour* ptr, int n, char* mode)
{
    int i, j;
    int size = ptr[n].num_teams;
    // sort based on points
    // using bubble sort algorithm

    // we use 2 for loops to loop through all of the comparisons
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size-i-1; j++)
        {
            // if "asc" was passed as a parameter, sort in ascending order
            if (strcmp(mode, "asc") == 0)
            {
                // to sort in ascending order
                // check 2 adjacents elements of the arr containing points of a team
                // if the first element is greater than the second element then swap
                // do it until all the big numbers bubble up to the right
                // and the array becomes sorted
                if (ptr[n].teams[j].points > ptr[n].teams[j+1].points)
                {
                    swapAdjacentTeams(ptr, n, j);
                }
                else if (ptr[n].teams[j].points == ptr[n].teams[j+1].points &&
                        ptr[n].teams[j].goal_difference > ptr[n].teams[j+1].goal_difference)
                {
                    swapAdjacentTeams(ptr, n, j);
                }
            }
            // if "desc" is passed as a parameter, sort in descending order
            else if (strcmp(mode, "desc") == 0)
            {
                // to sort in descending order
                // check 2 adjacents elements of the arr containing points of a team
                // if the first element is smaller than the second element then swap
                // do it until all the small numbers bubble up to the right
                // and the array becomes sorted
                if (ptr[n].teams[j].points < ptr[n].teams[j+1].points)
                {
                    swapAdjacentTeams(ptr, n, j);
                }
                else if (ptr[n].teams[j].points == ptr[n].teams[j+1].points &&
                        ptr[n].teams[j].goal_difference < ptr[n].teams[j+1].goal_difference)
                {
                    swapAdjacentTeams(ptr, n, j);
                }
            }
            // if something else is passed, just get out
            else
            {
                // just so it's easier to debug
                printf("Invalid parameter for sort!\n");
                system("pause");
                exit(0);
            }
        }
    }

    for (i = 0; i < ptr[n].num_teams; i++)
    {
        if (strcmp(mode, "asc") == 0)
            ptr[n].teams[i].rank = ptr[n].num_teams-i;

        else if (strcmp(mode, "desc") == 0)
            ptr[n].teams[i].rank = i+1;
    }
}

void helpMainMenu(Tour* ptr, int n)
{
    
}

void helpStandingsMenu()
{
    clearAndPrintHeader("Help - Standings Menu");
    printf("HELP MENU WIP\n");
    printf("\nPress any key to exit... ");
    getch();
    system("cls");
}

void moreInfo(Tour* ptr, int n)
{

}

void exitMenu()
{
    clearAndPrintHeader("");
    printf("Thank you for using this program!\n");
    printf("See you next time\n");
    exit(0);
}

void swapAdjacentTeams(Tour* ptr, int n, int j)
{
    char tempStr[35];
    Team temp;

    temp = ptr[n].teams[j];
    ptr[n].teams[j] = ptr[n].teams[j+1];
    ptr[n].teams[j+1] = temp;

    strcpy(tempStr, ptr[n].name_teams[j]);
    strcpy(ptr[n].name_teams[j], ptr[n].name_teams[j+1]);
    strcpy(ptr[n].name_teams[j+1], tempStr);
}