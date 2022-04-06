#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    int i = 0;
    Tour* tourPtr = (Tour*) malloc (sizeof(Tour));

    mainMenu(tourPtr, i);
    searchAndPickTeam(tourPtr, i);


    // int return_index[11] = {0};
    // for (i = 0; i < 11; i++) {
    //     printf("%d ", return_index[i]);
    // }
    // char target[35];
    // char names[10][35] = {
    //     "Ale",
    //     "Althaf",
    //     "Bilal",
    //     "Chamber",
    //     "Dani",
    //     "Eli",
    //     "Fahad",
    //     "Gad",
    //     "Hassan",
    //     "Ibrahim"
    // };
    // printf("\n>> ");
    // scanf("%s", target);
    // search(names, target, return_index, 10);
    // printf("Return index: ");
    // for (i = 0; i < 11; i++) {
    //     printf("%d ", return_index[i]);
    // }

    return 0;
}
