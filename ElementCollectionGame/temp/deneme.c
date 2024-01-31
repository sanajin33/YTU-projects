#include <stdio.h>

#define ROWS 5
#define COLS 5

void printlabirent(char labirent[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(" ___");
        }
        printf("\n");
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", labirent[i][j]);
        }
        printf("|\n");
    }
}

int isValidMove(char labirent[ROWS][COLS], int row, int col, int visited[ROWS][COLS]) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS && labirent[row][col] != '1' && visited[row][col] == 0 && labirent[row][col] != 'K') ;
}

int findPath(char labirent[ROWS][COLS], int row, int col, int visited[ROWS][COLS], int *collectedp, int *collectedP, int *collectedE,int *collectede) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || labirent[row][col] == '1' || visited[row][col] == 1) {
        return 0;
    }

    visited[row][col] = 1;

    if (labirent[row][col] == 'C') {
        return 1;
    }



    if (isValidMove(labirent, row - 1, col, visited) && findPath(labirent, row - 1, col, visited, collectedp, collectedE, collectedP, collectede)) {
        labirent[row][col] = 'X';
        if (labirent[row-1][col] == 'p') {
            *collectedp += 1;
        }
        else if (labirent[row-1][col] == 'P') {
            *collectedP += 1;
        }
        else if (labirent[row-1][col] == 'E') {
            *collectedE += 1;
        }
        else if (labirent[row-1][col] == 'e') {
            *collectede += 1;
        }
        printlabirent(labirent);
                printf("\n------------------------------------\n");

        return 1;
    }

    if (isValidMove(labirent, row + 1, col, visited) && findPath(labirent, row + 1, col, visited, collectedp, collectedE, collectedP, collectede)) {
        labirent[row][col] = 'X';
        if (labirent[row+1][col] == 'p') {
            *collectedp += 1;
        }
        else if (labirent[row+1][col] == 'P') {
            *collectedP += 1;
        }
        else if (labirent[row+1][col] == 'E') {
            *collectedE += 1;
        }
        else if (labirent[row+1][col] == 'e') {
            *collectede += 1;
        }
        printlabirent(labirent);
        printf("\n------------------------------------\n");

        return 1;
    }

    if (isValidMove(labirent, row, col - 1, visited) && findPath(labirent, row, col - 1, visited, collectedp, collectedE, collectedP, collectede)) {
        labirent[row][col] = 'X';
        if (labirent[row][col-1] == 'p') {
            *collectedp += 1;
        }
        else if (labirent[row][col-1] == 'P') {
            *collectedP += 1;
        }
        else if (labirent[row][col-1] == 'E') {
            *collectedE += 1;
        }
        else if (labirent[row][col-1] == 'e') {
            *collectede += 1;
        }     
        printlabirent(labirent);
            printf("\n------------------------------------\n");

        return 1;
    }

    if (isValidMove(labirent, row, col + 1, visited) && findPath(labirent, row, col + 1, visited, collectedp, collectedE, collectedP, collectede)) {
        labirent[row][col] = 'X';
        if (labirent[row][col+1] == 'p') {
            *collectedp += 1;
        }
        else if (labirent[row][col+1] == 'P') {
            *collectedP += 1;
        }
        else if (labirent[row][col+1] == 'E') {
            *collectedE += 1;
        }
        else if (labirent[row][col+1] == 'e') {
            *collectede += 1;
        }    
        printlabirent(labirent);
        printf("\n------------------------------------\n");

        return 1;
   
    }


    visited[row][col] = 0;

    return 0;
}

int main() {
    char labirent[ROWS][COLS] = {
        {'0', '0', 'p', '0', 'C'},
        {'1', '1', '0', '1', '1'},
        {'0', 'e', '0', '1', '0'},
        {'1', '0', '1', '1', '1'},
        {'K', 'p', 'X', '0', '1'}
    };

    int visited[ROWS][COLS] = {0};
    int startX, startY;

    // Find the starting position
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (labirent[i][j] == 'X') {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    int collectede = 0;
    int collectedE = 0;
    int collectedp = 0;
    int collectedP = 0;

    if (findPath(labirent, startX, startY, visited, &collectede, &collectedE, &collectedp, &collectedP)) {
        printf("Path found:\n");
        printlabirent(labirent);
    } else {
        printf("No path found.\n");
    }

    return 0;
}
