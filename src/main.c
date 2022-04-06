#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    int n = 0;
    Tour* tourPtr = (Tour*) malloc (sizeof(Tour));

    mainMenu(tourPtr, n);
    standingsMenu(tourPtr, n);

    return 0;
}
