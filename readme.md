# Program's outline:
Proyek Tengah Semester Proglan
## To-Do List:
- [] Add a fun facts menu (top scorer, teams with most goals, etc)
- [] Search for sorting algorithms
- [] Search for searching algorithms
## How to compile and run
```
gcc -Wall -c functions.c && gcc -Wall -c main.c && gcc -o program functions.o main.o && program
```
## Main Menu:
1. Calculate standings of a new competition
2. See previous competitions' standings
3. See previous competitions' match history
3. Help
4. Exit
## Main Menu -> 1:
- "Enter the tournament name: {tournament_name}"
- "How many teams are there? {num_of_teams}"

- (show every possible matchup and ask for data)
- "Number of goals: {num_of_goals}"
- "Who scored and at what time? {input}"
- (loop for every possible matchup)

### 1 -> Ranking Menu:
(show ranking table with the columns below)
- Rank, Team Name, Wins, Draws, Losses, Goal Difference (GD), Points
(also show menu below)
1. Search for a team
2. See a team's data
3. Exit to main menu

## Main Menu -> 2
halo