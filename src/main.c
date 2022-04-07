#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    // set initial index to -1 so the program knows it is the first time
    int n = -1;
    // use malloc to allocate memory for the tournaments' data
    Tour* tourPtr = (Tour*) malloc (sizeof(Tour));

    // print the welcome screen of the program
    welcomeScreen();
    // call the mainMenu function to start the program
    mainMenu(tourPtr, n);

    return 0;
}
