#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    int i = 0;
    Tour* tourPtr = (Tour*) malloc (sizeof(Tour));

    mainMenu(tourPtr, i);
    sortTeamsByRank(tourPtr, i, "desc");

    return 0;
}
