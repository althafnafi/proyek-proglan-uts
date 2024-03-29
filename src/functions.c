#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <math.h> // for ceil and floor
#include "functions.h"

void welcomeScreen()
{
    // print the welcome screen
    system("cls");
    printf("\n");
    printf("  +===============================================+\n");
    printf("  |             << WELCOME TO THE >>              |\n");
    printf("  |      << Football Standings Calculator >>      |\n");
    printf("  |                   Made by:                    |\n");
    printf("  |       Adrien Ardra Ramadhan (2106731485)      |\n");
    printf("  |         Althaf Nafi Anwar (2106634881)        |\n");
    printf("  |          Muhammad Suhaili (2106731535)        |\n");
    printf("  +===============================================+\n");
    printf("\n");
    // print loading bar
    showLoadingBar();
    system("cls");
}

void showLoadingBar()
{
    int i;
    char a = 177, b = 219;

    printf("  Loading . . .\n\n");
    printf("  ");

    // print empty loading bar
    for (i = 0; i < 48; i++)
        printf("%c", a);

    // print the loading bar
    printf("\r");
    printf("  ");
    for (int i = 0; i < 48; i++) {
        printf("%c", b);
        // add delay for effect
        Sleep(35);
    }
}

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
            // storing the max length string at that point of the loop
            maxL = tempL;
        }
    }
    // return the max length of the strring in the array
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
    printf("               Made easy!\n");
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
    puts(" 1. Calculate standings of a new competition");
    puts(" 2. See previous competitions' standings");
    puts(" 3. Help");
    puts(" 4. About");
    puts(" 5. Exit the program");
    // get the input from the user
    puts("Enter the desired menu: ");
    printf(">> ");
    int choice = getch();
    // will call functions based on the input
    switch(choice) 
    {
        case '1':
            // menu 1 calls the function to calculate the standings
            calcStandings(ptr, n);
            break;
        case '2':
            // menu 2 calls the function to see the previous standings
            showPrevStandings(ptr, n);
            break;
        case '3':
            // menu 3 calls the function to show the help
            helpMainMenu(ptr, n);
            break;
        case '4':
            // menu 4 calls the function to show the about page/menu
            aboutMenu(ptr, n);
            break;
        case '5':
            // menu 5 calls the function to exit the program
            exitMenu(ptr, n);
            break;
        default:
            // if user enters other than 1...5 then callback the function
            mainMenu(ptr, n);
            break;
    }

}

void calcStandings(Tour* ptr, int n) 
{
    // the calc standings function consists of three parts
    // part 1 -> ask the user to input the details of the tournaments
    //        -> tournament details = (name, num of teams, name of the teams)
    //        -> store the details in the struct
    // part 2 -> ask the user to input the details of each match
    //        -> match details = (team name, goal scored)
    //        -> user can also input the details of each goals if they choose to
    //        -> goal details = (scorer's name, time of the goal)
    //        -> store the details in the struct
    // part 3 -> calculate the points of each team based on the matches
    //        -> calculate the goal difference of each team
    // and so all the stored data will be used to print the table and determine the rankings
    // this function will afterwards call the function to print the standings
    int i, j, k;
    int match_num = 0;
    int invalid = 1;
    fflush(stdin);
    // add new space
    n++;
    ptr = (Tour*) realloc (ptr, (n+1) * sizeof(Tour));

    // asking for tournament name
    clearAndPrintHeader("Input tournament's data");
    printf("Enter the tournament name:\n");
    printf(">> ");
    fflush(stdin);
    scanf("%[^\n]s", ptr[n].name);
    fflush(stdin);

    // asking for number of teams that are participating in that tourney
    do
    {   
        clearAndPrintHeader("Input tournament's data");
        puts("How many teams participated?");
        printf(">> ");
        fflush(stdin);
        scanf("%d", &ptr[n].num_teams);
        if (ptr[n].num_teams < 2 || ptr[n].num_teams > 10)
        {
            puts("\nThe number you entered was invalid!");
            puts("Enter a minimum of 2 teams and a maximum of 10 teams!");
            anyKey();
            invalid = 1;
        }
        else
        {
            invalid = 0;
        }
    } while (invalid == 1);

    // calculate number of matches that are going to be played in that tourney
    ptr[n].num_matches = ptr[n].num_teams * (ptr[n].num_teams - 1)/2;

    // ask for the names of those teams
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

    // for loop to zero every thing out in the teams struct
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

    // for loop to set -1 as defaut score (used for error handling)
    for (i = 0; i < ptr[n].num_matches; i++)
    {
        ptr[n].matches[match_num].teamA_score = -1;
        ptr[n].matches[match_num].teamB_score = -1;
    }

    // for loops to ask for the scores of each match
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        for (j = i+1; j < ptr[n].num_teams; j++) 
        {
            // do while used for error handling of user inputs
            do
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
                fflush(stdin);
                scanf("%d", &ptr[n].matches[match_num].teamA_score);
                fflush(stdin);
                if (ptr[n].matches[match_num].teamA_score < 0)
                {
                    invalid = 1;
                    puts("\nThe number you entered was invalid!");
                    puts("Enter a number greater than or equal to 0!\n");
                    anyKey();
                    continue;
                }
                // from team B
                printf("How many goals did %s score?\n", ptr[n].matches[match_num].teamB_name);
                printf(">> ");
                scanf("%d", &ptr[n].matches[match_num].teamB_score);
                fflush(stdin);
                if (ptr[n].matches[match_num].teamB_score < 0)
                {
                    invalid = 1;
                    puts("\nThe number you entered was invalid!");
                    puts("Enter a number greater than or equal to 0!");
                    puts("Resetting input...\n");
                    anyKey();
                    continue;
                }
                // if the scores are valid, break the loop
                invalid = 0;
            } while (invalid == 1);

            // calculate the details for each category and points
            // and store the data in the struct

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

            // do while used for error handling of user inputs
            do 
            {
                invalid = 0;
                //ask for details of each goal (or skip)
                clearAndPrintHeader("Input tournament's data");
                printf("Do you want to input the details of the goals?\n");
                printf("1. Yes, the scorer only\n");
                printf("2. Yes, the time only\n");
                printf("3. Yes, both the scorer and the time\n");
                printf("4. No\n");
                printf("\nEnter your choice: ");
                printf(">> ");
                // switch case to check the input
                switch (getch())
                {
                    case '1': // input the scorer only
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
                        invalid = 1;
                        break;
                }
            } while (invalid == 1);
            // asking for goals' details
            for (k = 0; k < ptr[n].matches[match_num].total_goals; k++) 
            {
                // do while used for error handling of user inputs
                do
                {
                    invalid = 0;
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
                        // check if user input is valid, if not, reset the input and ask again
                        if (ptr[n].matches[match_num].goal_time[k] < 0 ||
                            ptr[n].matches[match_num].goal_time[k] > 90)
                        {
                            invalid = 1;
                            puts("\nThe number you entered was invalid!");
                            puts("Enter a number between 0 and 90!");
                            puts("Resetting input...\n");
                            anyKey();
                        }
                    }
                } while(invalid == 1);        
            } 
            // increment match number
            match_num++;
        }
    }
    // input data (goal diff and points) to struct based on the matches
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        ptr[n].teams[i].goal_difference = ptr[n].teams[i].goals_for - ptr[n].teams[i].goals_against;
        ptr[n].teams[i].points = (ptr[n].teams[i].wins * 3) + ptr[n].teams[i].draws;
    }

    standingsMenu(ptr, n, -1);
}

void showStandingsTable(Tour* ptr, int n)
{
    int i, j;
    int printL;
    // the number 9 is based on the column's name length (Team Name)
    // if the max length of string is smaller than or equal to 9
    // set printL (print length) to 9
    if (maxLength(ptr[n].name_teams) <= 9)
        printL = 11;
    else
        // if not, set printL to the max length of team name
        printL = (maxLength(ptr[n].name_teams));

    // printing the table's border
    printf("+");
    for (i = 0; i < printL+57; i++)
    {
        printf("-");
    }
    printf("+\n");
    printf("|");

    // printing the column's name
    printf(" Rank  ");
    // print "Team Name" and the spaces beside it based on the max length of the team name
    for (i = 0; i < floor(((float)printL-9)/2); i++)
        printf(" ");
    printf("Team Name");
    for (i = 0; i < ceil(((float)printL-9)/2); i++)
        printf(" ");
    printf("%8s%5s%5s%5s%6s%6s%6s%8s |","GP", "W", "D", "L", "GF", "GA", "GD", "Pts");
    printf("\n+");

    // printing the table's border
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

    // printing the table's border
    printf("\n+");
    for (i = 0; i < printL+57; i++)
    {
        printf("-");
    }
    printf("+\n");
}

void standingsMenu(Tour* ptr, int n, int tour_index)
{
    int target_index;
    int target_rank;
    int temp_index;
    char header_str[40];

    
    temp_index = tour_index;
    // if the tour_index is -1, set tour_index to n
    if (tour_index == -1)
    {
        tour_index = n;
    }

    // sort based on points and set rankings
    int size = ptr[n].num_teams;
    sortTeamsByRank(ptr, tour_index, size, "desc");
    setRankings(ptr, tour_index, "desc");
    
    // print the header
    strcpy(header_str, ptr[tour_index].name);
    strcat(header_str, " Table");
    clearAndPrintHeader(header_str);

    // print the standings table
    showStandingsTable(ptr, tour_index);

    // print the options
    printf("\n >> Menu Options <<\n");
    printf("1. Search by team name\n");
    printf("2. Search by ranking\n");
    printf("3. Show match details\n");
    printf("4. Show tournament details\n");
    printf("5. Help\n");
    printf("6. Exit to main menu\n");
    printf("Enter your choice :\n");
    printf(">> ");
    // ask user for input
    switch(getch())
    {
        case '1': // search by team name
            // determine the team's index by calling searchAndPickTeam
            // which return's the index of the team based on the search result
            target_index = searchAndPickTeam(ptr, tour_index);
            // if the index is -1, team was not found and program will return to menu
            if (target_index == -1)
            {
                standingsMenu(ptr, n, temp_index);
                break;
            }
            // if team is found, print their details
            showTeamDetails(ptr, tour_index, target_index);
            // the user can press any key to go back to the standings menu
            printf("\n(Press any key to go back...) ");
            getch();
            standingsMenu(ptr, n, temp_index);
            break;
        case '2': // search by ranking
            clearAndPrintHeader(header_str);
            showStandingsTable(ptr, tour_index);
            // asks user for input of their desired ranking
            printf("\nEnter your desired ranking position : \n");
            printf(">> ");
            fflush(stdin);
            scanf("%d", &target_rank);
            // determine the team's index by calling getIndexByRank
            target_index = getIndexFromRank(ptr, tour_index, target_rank);
            // if the index is -1, team was not found and program will return to menu
            if (target_index == -1)
            {
                printf("\nInvalid ranking position!\n");
                anyKey();
                standingsMenu(ptr, n, temp_index);
                break;
            }
            // if team is found, print their details
            showTeamDetails(ptr, tour_index, target_index);
            // the user can press any key to go back to the standings menu
            printf("\n(Press any key to go back...) ");
            getch();
            standingsMenu(ptr, n, temp_index);
            break;
        case '3': // show match details w/ "scroll" feature
            showMatchDetails(ptr, tour_index, 0, "scroll");
            standingsMenu(ptr, n, temp_index);
            break;
        case '4': // show tournament details
            showTournamentDetails(ptr, tour_index);
            printf("\n(Press any key to go back...) ");
            getch();
            standingsMenu(ptr, n, temp_index);
            break;
        case '5': // go to help menu
            helpStandingsMenu();
            standingsMenu(ptr, n, temp_index);
            break;
        case '6': // exit to main menu
            mainMenu(ptr, n);
            break;
        default : // invalid input -> callback standingsMenu
            standingsMenu(ptr, n, temp_index);
            break;
    }
}

void showTeamDetails(Tour* ptr, int n, int team_index)
{
    // print the team and tournament name
    clearAndPrintHeader("Team Details");
    printf("\nTournament: %s\n", ptr[n].name);
    printf(">> %s (Rank %d) <<\n", 
            ptr[n].teams[team_index].name,
            ptr[n].teams[team_index].rank
    );
    // print the team details
    printf(" - Games Played  : %d\n", ptr[n].teams[team_index].games_played);
    printf(" - Wins\t\t : %d\n", ptr[n].teams[team_index].wins);
    printf(" - Draws\t : %d\n", ptr[n].teams[team_index].draws);
    printf(" - Losses\t : %d\n", ptr[n].teams[team_index].losses);
    printf(" - Goals For\t : %d\n", ptr[n].teams[team_index].goals_for);
    printf(" - Goals Against : %d\n", ptr[n].teams[team_index].goals_against);
    printf(" - Goal Diff.\t : %d\n", ptr[n].teams[team_index].goal_difference);
    printf(" - Points\t : %d\n", ptr[n].teams[team_index].points);
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
    // print the tournament details
    clearAndPrintHeader("Tournament Details");
    printf("\n>> %s <<\n", ptr[n].name);
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

    // mode -> "scroll"    ; enable scrolling through matches in a tournament
    // mode -> ""    ; disables scrolling
    if (strcmp(mode, "scroll") == 0)
    {
        printf("\t<<   %d/%d   >>\n\n", match_num+1, ptr[n].num_matches);
    }

    //print match overview
    printf(" >> Match Details << \n");
    printf("\nTournament: %s\n", ptr[n].name);
    printf(
        ">> %s VS %s <<\n",
        ptr[n].matches[match_num].teamA_name,
        ptr[n].matches[match_num].teamB_name
    );
    printf(" ");

    // print as long as team A's name (for formatting purposes)
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
        printf("\n(Use arrow keys to scroll through matches or press q to exit...)\n");
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

void showPrevStandings(Tour* ptr, int n)
{
    int i, input, flag = 0;
    // erorr hanling if a tournament has not been created
    if (n == -1)
    {
        clearAndPrintHeader("Previous Tournament Standings");
        printf("No tournament has been created yet.\n");
        printf("To create a new tournament go to the first menu in the main menu.\n\n");
        anyKey();
        mainMenu(ptr, n);
    }
    // do while loop to keep asking for input until a valid input is given
    do 
    {
        clearAndPrintHeader("Previous Tournament Standings");
        printf("List of previous tournaments:\n");
        for (i = 0; i < n+1; i++)
        {
            printf(" %d. %s\n", i+1, ptr[i].name);
        }
        printf("\nEnter the number of the tournament you want to view: ");
        fflush(stdin);
        scanf("%d", &input);
        if (input < 1 || input > n+1)
        {
            clearAndPrintHeader("Previous Tournament Standings");
            printf("\nInvalid input!\n");
            anyKey();
            flag = 1;
        }
        else
        {
            flag = 0;
        }
    } while (flag != 0);

    // print the tournament standings
    standingsMenu(ptr, n, input-1);
}

int searchAndPickTeam(Tour* ptr, int n)
{
    int input = 0;
    int i, count;
    char target_name[35];
    // index_team is used as a place to store the index of the team
    // index 0...10 will store index of the team that matches the substring passed to the search func
    // 11th index is the status index
    // which is used to determine if the team is found or not (-1 if not found)
    int index_team[11] = {0};
    clearAndPrintHeader("Search for a team");
    // ask user's input for a team name
    printf("Search for name of the team:\n");
    printf(">> ");
    fflush(stdin);
    scanf("%[^\n]s", target_name);
    // pass that input to the search function
    // and get the index of the teams with similar names
    search(ptr[n].name_teams, target_name, index_team, ptr[n].num_teams);

    // if the 11th index is -1, then the team is not found
    // and the function will exit and returns -1
    if (index_team[10] == -1)
    {
        clearAndPrintHeader("Search for a team");
        printf("\nTeam not found!\n");
        anyKey();
        return -1;
    }
    // if the 11th index is not -1, then the team is found
    // and the user can pick the teams that satisfied the search function
    // and this function will return that team's index for use
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
    // searches through all the teams
    // and returns the index of the team with the given rank
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        if (ptr[n].teams[i].rank == team_rank)
        {
            return i;
        }
    }
    return -1;
}

void swapAdjacentTeams(Tour* ptr, int n, int j)
{
    // this function is used in the sort function
    // which utilizes bubble sort and uses swapping
    char tempStr[35];
    Team temp;
    // swap the structs of the two teams
    temp = ptr[n].teams[j];
    ptr[n].teams[j] = ptr[n].teams[j+1];
    ptr[n].teams[j+1] = temp;
    // swap the names of the two teams in the name_teams array
    strcpy(tempStr, ptr[n].name_teams[j]);
    strcpy(ptr[n].name_teams[j], ptr[n].name_teams[j+1]);
    strcpy(ptr[n].name_teams[j+1], tempStr);
}

void sortTeamsByRank(Tour* ptr, int n, int size, char* mode)
{
    int j;
    // sort based on points
    // using bubble sort algorithm

    // base case, if size is 1 stop sorting and set rankings
    if (size == 1)
    {
        setRankings(ptr, n, mode);
        return;
    }
    // we use for loops to loop through all of the comparisons
    for (j = 0; j < size-1; j++)
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
    // recursively call the function to sort the array
    sortTeamsByRank(ptr, n, size-1, mode);
}

void setRankings(Tour* ptr, int n, char* mode)
{
    int i;
    // loop through all team to set their rank based on sorted indexes
    for (i = 0; i < ptr[n].num_teams; i++)
    {
        if (strcmp(mode, "asc") == 0)
            ptr[n].teams[i].rank = ptr[n].num_teams-i;

        else if (strcmp(mode, "desc") == 0)
            ptr[n].teams[i].rank = i+1;
    }
}

void helpStandingsMenu()
{
    // print the help menu for standings menu
    clearAndPrintHeader("Help - Standings Menu");
    printf("\n");
    printf("You can choose several options in this menu to see a more detailed information of the tournament.\n");
    printf("You are also able to utilize the search function to search for a team by name or rank.\n");
    printf(" - Choose option 1 to search the team name you want and get the particular team details.\n");
    printf(" - Choose option 2 to input the rank order based on the standings table and get the team details.\n");
    printf(" - Choose option 3 to get the match details.\n");
    printf(" - Choose option 4 to get the user manual written for you.\n");
    printf(" - Choose option 5 to go back to the main menu.\n");
    printf("\nPress any key to exit... ");
    getch();
    system("cls");
}

void helpMainMenu(Tour* ptr, int n)
{
    // print the help menu for main menu
    clearAndPrintHeader("Help - Main Menu");
    printf("\n");
    puts(" - Choose option 1 to make a football standings table based on the\n   competitions, teams, and goals that you have input.");
    puts(" - Choose option 2 to see the previous competition's standings table.");
    puts(" - Choose option 3 to read this user manual.");
    puts(" - Choose option 4 to read this program's about page.");
    puts(" - Choose option 5 to exit the program.");
    printf("\nPress any key to exit... ");
    getch();
    mainMenu(ptr, n);
}

void aboutMenu(Tour* ptr, int n)
{
    // print the about page
    clearAndPrintHeader("About This Program");
    printf("\n");
    printf(" - This program was made to help users make a football standings table based on the\n");
    printf("   competitions, teams, and goals.\n");
    printf(" - This program is made by as for the mid-term project on the\n");
    printf("   2nd semester in 2022 at the University of Indonesia\n");
    printf(" - In this program, the user are excpected to make a football\n");
    printf("   standings table and a few extra details along with it\n");
    printf(" - Any use and further copies of this program are expected to\n");
    printf("   be allowed\n\n");
    printf("This program is made by:\n");
    printf("Adrien Adri Ramadhan, Althaf Nafi Anwar, and Muhammad Suhaili\n");
    printf("Press any key to exit... ");
    getch();
    mainMenu(ptr, n);
}

void exitMenu(Tour* ptr, int n)
{
    char exit_choice[5];
    // do while loop to make sure the user input is valid
    do
    {
        fflush(stdin);
        clearAndPrintHeader("Exit Menu");
        printf("\n");
        // the user can input y/n to exit the program or go back to the main menu
        printf("Are you sure you want to exit the program (y/n)? ");
        scanf("%s", exit_choice);
    } while (strcmp("y", exit_choice) != 0 && strcmp("n", exit_choice) != 0);

    if (strcmp("y", exit_choice) == 0)
    {
        clearAndPrintHeader("Exit Menu");
        printf("\nThank you for using this program :)\n");
        printf("See you next time!\n");
        exit(0);
    }
    else
    {
        mainMenu(ptr, n);
    }
}