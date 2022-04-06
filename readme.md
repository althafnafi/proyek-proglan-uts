# Program's outline:
Proyek Tengah Semester Proglan
## Penilaian Proyek
- [X] Ada > 3 function selain main
- [X] Penggunaan return type void dan non-void
- [X] Penggunaan fungsi tanpa dan dengan parameter
- [X] Penggunaan fungsi dengan satu parameter
- [X] Penggunaan fungsi dengan lebih dari satu parameter
- [ ] Penamaan variabel dan function yang user-friendly
- [ ] Dekomposisi algoritma kompleks (pake comment2an)
- [ ] Ada welcome message
- [ ] Panduan di setiap halaman
- [ ] Info bila user salah input (error handling)
- [X] Ada Header File
- [X] Ada function prototype
- [ ] Penggunaan rekursi yang tepat
- [X] Penggunaan Array 1D yang tepat
- [X] Penggunaan Array 2D yang tepat
- [X] Ada searching algorithm yang tepat
- [ ] Ada sorting algorithm yang tepat
- [ ] Tidak ada error/bug dalam program
- [ ] Tujuan aplikasi tercapai
- [ ] Penilaian video (wajah, pembagian, penjelasan, semangat, waktu)
## To-Do List:
- [ ] Add a fun facts menu (top scorer, teams with most goals, etc)
- [] Search for sorting algorithms
- [X] Search for searching algorithms
- [X] Scroll function between match details (with arrow key)
- [ ] Sort the goals and scorers based on time of the goal
- [X] Add a feature to differentiate goals between different teams
- [ ] Add error handling to all getch() and scanf()
## How to compile and run
```
gcc -Wall -c functions.c && gcc -Wall -c main.c && gcc -o program functions.o main.o && program
```
## Main Menu:1
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