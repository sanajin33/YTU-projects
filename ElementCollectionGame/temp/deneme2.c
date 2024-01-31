#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>


/*------ degiskenler -------*/
#define MAX_USERS 100

/*----------------------------- struct ---------------------------- */
struct kullaniciData{
    int kullaniciSayisi;
};

struct userInfo {
    char isim[50];
    char soyisim[50];
    char kullaniciAdi[50];
    char sifre[50];
    int skor;
    struct kullaniciData userData;
};

struct elementler{
    int artiP;
    int eksiP;
    int artiE;
    int eksiE;
};
int findXlocation(char** matrix, int row, int col){
    int i,j;
    int x;
    for(i=0 ; i<row ; i++ ){
        for( j=0 ; j<=col ;j++ ){
            if(matrix[i][j]=='X'){
                x = i*10 + j; // iki sayiyi dondurebilmek icin onlari tek sayiymis gibi birlestiriyorum
                // sonra ayirip kullancam, i=0 olursa tek basamakli sayi olacagindan i sifir hesaplanir.
                return x;
            }
        }
    }
    return -1; // Return -1 if 'X' is not found
}

void matrisyazdir(int row, int col, char **matris){
int i,j;
    // Matris iÃ§erigini ekrana yazdirma
    printf("\n\nlabirent:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf(" ___");
        }
        printf("\n");
        for (j = 0; j < col; j++) {
            printf("| %c ", matris[i][j]);
            if(j ==  col-1){
                printf("|");
            }
        }

        printf("\n");
    }
    printf("\n");
}


void freeVisited(int **visited, int row) {
    for (int i = 0; i < row; i++) {
        free(visited[i]);
    }
    free(visited);
}

int isValidMove(char** labirent, int Xrow, int Xcol, int **visited,int row, int col) {
    return (Xrow >= 0 && Xrow < row && Xcol >= 0 && Xcol < col && labirent[Xrow][Xcol] != '1' && visited[Xrow][Xcol] == 0 && labirent[Xrow][Xcol] != 'K') ;
}

int AutoMode(char **labirent,int Xrow, int Xcol , struct elementler elementler, int row, int col){

    int** visited = (int **)calloc(row, sizeof(int *));
    for (int i = 0; i < row; i++) {
        visited[i] = (int *)calloc(col, sizeof(int));
    }




    if (Xrow < 0 || Xrow >= row || Xcol < 0 || Xcol >= col || labirent[Xrow][Xcol] == '1' || visited[Xrow][Xcol] == 1) {
        freeVisited(visited, row);
        return 0;
    }

    visited[Xrow][Xcol] = 1;

    if (labirent[Xrow][Xcol] == 'C') {
        return 1;
    }


    if (isValidMove(labirent, Xrow - 1, Xcol, visited, row,col) && AutoMode(labirent, Xrow - 1, Xcol, elementler, row, col)) {
        labirent[Xrow][Xcol] = 'X';
        if (labirent[Xrow-1][Xcol] == 'p') {
            elementler.eksiP += 1;
        }
        else if (labirent[Xrow-1][Xcol] == 'P') {
            elementler.artiP += 1;
        }
        else if (labirent[Xrow-1][Xcol] == 'E') {
            elementler.artiE += 1;
        }
        else if (labirent[Xrow-1][Xcol] == 'e') {
            elementler.eksiE += 1;
        }
        matrisyazdir(row,col,labirent);
 
        return 1;
    }

    if (isValidMove(labirent, Xrow + 1, Xcol, visited, row, col) && AutoMode(labirent, Xrow + 1, Xcol, elementler, row, col)) {
        labirent[Xrow][Xcol] = 'X';
        if (labirent[Xrow+1][Xcol] == 'p') {
            elementler.eksiP += 1;
        }
        else if (labirent[Xrow+1][Xcol] == 'P') {
            elementler.artiP += 1;
        }
        else if (labirent[Xrow+1][Xcol] == 'E') {
            elementler.artiE += 1;
        }
        else if (labirent[Xrow+1][Xcol] == 'e') {
            elementler.eksiE += 1;
        }
        matrisyazdir(row,col,labirent);

        return 1;
    }

    if (isValidMove(labirent, Xrow, Xcol - 1, visited, row, col) && AutoMode(labirent,Xrow, Xcol - 1,elementler, row, col)) {
        labirent[Xrow][Xcol] = 'X';
        if (labirent[Xrow][Xcol-1] == 'p') {
            elementler.eksiP += 1;
        }
        else if (labirent[Xrow][Xcol-1] == 'P') {
            elementler.artiP += 1;
        }
        else if (labirent[Xrow][Xcol-1] == 'E') {
            elementler.artiE += 1;
        }
        else if (labirent[Xrow][Xcol-1] == 'e') {
            elementler.eksiE += 1;
        }     
        matrisyazdir(row,col,labirent);
  
        return 1;
    }

    if (isValidMove(labirent, Xrow, Xcol + 1, visited, row, col) && AutoMode(labirent, Xrow, Xcol + 1,elementler, row, col)) {
        labirent[Xrow][Xcol] = 'X';
        if (labirent[Xrow][Xcol+1] == 'p') {
            elementler.eksiP += 1;
        }
        else if (labirent[Xrow][Xcol+1] == 'P') {
            elementler.artiP += 1;
        }
        else if (labirent[Xrow][Xcol+1] == 'E') {
            elementler.artiE += 1;
        }
        else if (labirent[Xrow][Xcol+1] == 'e') {
            elementler.eksiE += 1;
        }    
        matrisyazdir(row,col,labirent); 
        return 1;
   
    }
        printf("\n%d adet +e topladin\n", elementler.artiE);
        printf("\n%d adet -e topladin\n", elementler.eksiE);
        printf("\n%d adet +p topladin\n", elementler.artiP);
        printf("\n%d adet -p topladin\n", elementler.eksiP);
        
        

    freeVisited(visited, row);

    visited[Xrow][Xcol] = 0;

    return 0;
}


int main() {


 
  
    struct elementler elementler;
    elementler.artiE = 0; 
    elementler.artiP = 0;
    elementler.eksiE = 0;
    elementler.eksiP = 0;
    int zorluk;
    int row, col;
    FILE *dosya;
    char** labirent = (char **)malloc(MAX_USERS +1 * sizeof(char *));


    int Xrow = 0, Xcol = 0, Xlocation = 0;
    Xlocation = findXlocation(labirent, row, col);
    
    if (Xlocation != -1) {
        Xrow = Xlocation / 10;
        Xcol = Xlocation % 10;
    } else {
        printf("X is not found in the maze!\n");
        return 1;
    }

    printf("\nWhich mode do you want to play:\n1-Manual Mode\n2-Auto Mode\n");
    int secim3;
    scanf("%d", &secim3);

    if (secim3 == 1) {
        // Call your existing function for manual mode
    } else if (secim3 == 2) {
        if (AutoMode(labirent, Xrow, Xcol, elementler, row, col)) {
            printf("Path found:\n");
            matrisyazdir(row, col, labirent);
        } else {
            printf("No path found.\n");
        }
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    // Your existing code for other functionalities

    return 0;
}
