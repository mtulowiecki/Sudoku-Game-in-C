#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "struct.h"

#define SHUFFLES 20

/*
* function  : swapColumn
* purpose   : replace the entire num1 column with num2 column in array
* input     : reference array, num1, num2
* output    : void
*/

void swapColumn(int array[][9], int num1, int num2)
{

    unsigned short temporary = 0;
    for (int i = 0; i < 9; i++)
    {
            temporary = array[num1][i];
            array[num1][i] = array[num2][i];
            array[num2][i] = temporary;
    }
    return;
}

/*
* function  : swapRow
* purpose   : replace the entire num1 row with num2 row in array
* input     : reference array, num1, num2
* output    : void
*/

void swapRow(int array[][9], int num1, int num2)
{
    unsigned short temporary = 0;
    for (int i = 0; i < 9; i++)
    {
            temporary = array[i][num1];
            array[i][num1] = array[i][num2];
            array[i][num2] = temporary;
    }
    return;
}

/*
* function  : showRandomCell
* purpose   : inserts the value of one cell from fromArray to toArray
* input     : referenceArray, user array
* output    : void
*/

void showRandomCell(int fromArray[][9], int **toArray)
{

    int rndRow, rndCol;
    do {
    rndRow = rand() % 9;
    rndCol = rand() % 9;
    } while (toArray[rndRow][rndCol] != 0);

    toArray[rndRow][rndCol] = fromArray[rndRow][rndCol];

    return;

}

/*
* function  : generateBoard
* purpose   : the function creates a game environment for the player, userBoard
* input     : game board array, well-filled pattern array, game structure containing the user's choice
* output    : void
*/

void generateBoard(int **userBoard, int referenceBoard[][9], Game_Type *game)
{
    srand(time(NULL));
    unsigned short n, m;
    n = (rand() % 3) * 3;
    m = rand() % 1;
    for (int i = 0; i < SHUFFLES ; i++)
    {
        switch (rand() % 6)
        {
        case 0:
            swapRow(referenceBoard, n + 0, m ? n + 1 : n + 2);
            break;
        case 1:
            swapRow(referenceBoard, n + 1, m ? n + 0 : n + 2);
            break;
        case 2:
            swapRow(referenceBoard, n + 2, m ? n + 0 : n + 1);
            break;
        case 3:
            swapColumn(referenceBoard, n + 0, m ? n + 1 : n + 2);
            break;
        case 4:
            swapColumn(referenceBoard, n + 1, m ? n + 0 : n + 2);
            break;
        case 5:
            swapColumn(referenceBoard, n + 2, m ? n + 0 : n + 1);
            break;
        }
    }

    for (int i = 0; i < game->level; i++)
        showRandomCell(referenceBoard, userBoard);

    return;
}

/*
* function  : generateBoard
* purpose   : the function allocates memory for the player's board
* input     : array, num of rows, num of columns to allocate
* output    : void
*/

void allocateArray( int ***array, int rows, int columns) //pointer to pointer of pointers pogJUMP
{
    if (((*array) = (int **)calloc(rows, sizeof(int *))) != NULL)
    {
        for (int i = 0; i < 9; i++)
            *((*array) + i) = (int *)calloc(columns, sizeof(int));
    }
    else{
        perror("memory allocation failure");
        exit(1);
    }
}

/*
* function  : generateBoard
* purpose   : the function deallocates memory
* input     : game board array, num of columns in array
* output    : void
*/

void deallocateArray(int ***array, int columns){
    for (int i=0; i < columns; i++)
        free(*((*array)+i));
    free(*array);
}
