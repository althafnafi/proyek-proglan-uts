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
    for (i = 0; i < size; i++)
    {
        tempL  = strlen(arr[i]);
        if (maxL < tempL)
        {
            maxL = tempL;
        }
    }
    return maxL;
}

int inputArrowKey()
{
    int input = getch();
    if (input == 0 || input == 0xE0)
    {
        input = getch();
    }
    else if (input == 113) // 'q' to quit
    {
        return (-1);
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
    printf(" =======================================\n");
    printf("       Football Standings Program\n");
    printf("            Some sub heading!\n");
    printf(" =======================================\n\n");
    // printf("<< Football Standings Program >>\n");
    // printf("    << Some sub heading! >>\n\n");
    if (strcmp("", str) != 0)
        printf(" >>> %s <<<\n", str);
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
                strcpy(ptr[n].matches[match_num].scorer[k], "Unknown");
                ptr[n].matches[match_num].goal_time[k] = -1;
                if (ptr[n].matches[match_num].input_status != 4)
                {
                    clearAndPrintHeader("Input tournament's data");
                    printf("\nMatch %d:\n", match_num+1);
                    printf(
                        ">> %s VS %s <<\n",
                        ptr[n].matches[match_num].teamA_name,
                        ptr[n].matches[match_num].teamB_name
                    );
                    printf("Goal No-%d:\n", k+1);                    
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
                                
            }
            // increment match number
            match_num++;
        }
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
    int i, j;
    char target[35];
    int target_index;
    int index_arr[10] = {-1};
    //showStandingsTable
    printf("Searching Options\n");
    printf("1. Search by team name\n");
    printf("2. Search by ranking\n");
    printf("Enter your choice :\n");
    printf(">> ");
    switch(getch())
    {
        case '1':
            printf("Enter the name of the team : ");
            printf(">> ");
            fflush(stdin);
            scanf("%[^\n]s", target);
            fflush(stdin);
            search(ptr[n].name_teams, target, index_arr, ptr[n].num_teams);
            for (i = 0; i < 10; i++)
            {
                if (index_arr[i] != -1)
                {
                    showTeamDetails(ptr, n,  i);
                }
            }
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
    // clear screen and print header
    // GP    W    D    L    F    A    GD    P
    clearAndPrintHeader("Team Details");
    printf("%s\n", ptr[n].name_teams[team_index]);
    printf("Games Played: %d\n", ptr[n].teams[team_index].games_played);
    printf("Wins: %d\n", ptr[n].teams[team_index].wins);
    printf("Draws: %d\n", ptr[n].teams[team_index].draws);
    printf("Losses: %d\n", ptr[n].teams[team_index].losses);
    printf("Goals For: %d\n", ptr[n].teams[team_index].goals_for);
    printf("Goals Against: %d\n", ptr[n].teams[team_index].goals_against);
    printf("Goal Difference: %d\n", ptr[n].teams[team_index].goal_difference);
    printf("Points: %d\n", ptr[n].teams[team_index].points);
}

void search(char arr[][35], char target[], int return_index[10], int size) {
    int i, j, count = 0;
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
            if (count == strlen(target)) { //jika count == jumlah target
                count = 0;
                printf("Nama yang mirip: %s\n", arr[i]);
                return_index[i] = 1;
                break;
            }
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
        switch(inputArrowKey()) // ask for arrow key input
        {
            case 1: case 2: // go to the left page
                showMatchDetails(ptr, n, match_num-1, mode);
                break;
            case 3: case 4: // go to the right page
                showMatchDetails(ptr, n, match_num+1, mode);
                break;
            case (-1): // press 'q' to exit
                exit(0);
                // return;
                break;
            default:
                break;
        }
    }
}
