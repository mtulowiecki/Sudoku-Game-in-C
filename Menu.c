#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MAX_LEN 128
#define UP_ARROW 66
#define DOWN_ARROW 65

/*
* function  : printLogo
* purpose   : the function prints the ascii art logo from the fileptr
* input     : pointer to a file containing ascii art
* output    : void
*/

void printLogo( FILE *fptr){
    char readLine[MAX_LEN];
    while(fgets(readLine,sizeof(readLine),fptr) != NULL)
        printf("%s",readLine);
}

/*
* function  : arrowHere
* purpose   : print arrow in menu view
* input     : realPosition, arrowPosition
* output    : void
*/

void arrowHere(int realPosition, int arrowPosition) {
    if(realPosition == arrowPosition){
        printf("---->  ");
    }
    else{
        printf("       ");
    }
}

/*
* function  : startMenu
* purpose   : function that allows the user to choose the source of the board
* input     : void
* output    : user choice
*/

int startMenu() {
    short int choice = 1;
    short int keyPressed = 0;
    short int minChoice = 1;
    short int maxChoice = 2;
    FILE *logo_ptr = NULL;
    FILE *board_ptr = NULL;

    while (keyPressed != 10){

    system("clear || cls");

    if(( logo_ptr = fopen("asciiLogo.txt", "r")) != NULL){
        printLogo(logo_ptr);
        fclose(logo_ptr);
    }

    if(( board_ptr = fopen("Board.txt", "r")) != NULL){
        minChoice = 0;
        arrowHere(0, choice); printf("continue\n");
        fclose(board_ptr);
    }

    arrowHere(1, choice); printf("new game\n");
    arrowHere(2, choice); printf("exit\n");

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    keyPressed = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if(keyPressed == DOWN_ARROW && choice > minChoice){
        choice--;
    }
    else if(keyPressed == DOWN_ARROW && choice == minChoice){
        choice = maxChoice;
    }
    else if(keyPressed == UP_ARROW && choice < maxChoice){
        choice++;
    }
    else if(keyPressed == UP_ARROW && choice == maxChoice){
        choice = minChoice;
    }

    }

    return choice;
}

/*
* function  : startMenu
* purpose   : function that allows the user to choose the difficulty leve of the game
* input     : void
* output    : number of exposed fields on the board
*/

int levelMenu() {
    short int choice = 0;
    short int keyPressed = 0;
    short int minChoice = 0;
    short int maxChoice = 2;
    FILE *logo_ptr = NULL;

    while (keyPressed != 10){

    system("clear || cls");

    if(( logo_ptr = fopen("asciiLogo.txt", "r")) != NULL){
        printLogo(logo_ptr);
        fclose(logo_ptr);
    }

    arrowHere(0, choice); printf("easy\n");
    arrowHere(1, choice); printf("medium\n");
    arrowHere(2, choice); printf("hard\n");

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    keyPressed = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if(keyPressed == DOWN_ARROW && choice > minChoice){
        choice--;
    }
    else if(keyPressed == DOWN_ARROW && choice == minChoice){
        choice = maxChoice;
    }
    else if(keyPressed == UP_ARROW && choice < maxChoice){
        choice++;
    }
    else if(keyPressed == UP_ARROW && choice == maxChoice){
        choice = minChoice;
    }

    }
    switch(choice)
    {
        case 0:
            return 50;
            break;
        case 1:
            return 30;
            break;
        case 2:
            return 15;
            break;
        default:
            return 0;
    }
}