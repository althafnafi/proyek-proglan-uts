#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    int i = 0;

    Tour* tourPtr = (Tour*) malloc (sizeof(Tour));

    mainMenu(tourPtr, i);
    showTournamentDetails(tourPtr, i);

    return 0;
}
