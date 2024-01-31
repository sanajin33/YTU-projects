/*------ kutuphaneler -------*/
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

struct point{
    int row;
    int col;
};

struct elementler{
    int artiP;
    int eksiP;
    int artiE;
    int eksiE;
};
/*----------------------------- Fonksiyonlar ---------------------------- */

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

char** matrisOku(FILE *dosya, int row,int col){
int i,j;
    fgetc(dosya);
    
    char **matris = (char **) malloc (row+1 * sizeof(char *));
    for (i = 0; i < row; i++) {
        matris[i] = (char *)malloc(col +1 * sizeof(char));
        if (matris[i] == NULL) {
            perror("Bellek ayirma hatasi");
            // Daha Ã¶nce ayrilmis bellegi serbest birak
            for (j = 0; j < i; j++) {
                free(matris[j]);
            }
            free(matris);
            fclose(dosya);
            exit(1);
        }
    }

    // Dosyadan matrise okuma
    for ( i = 0; i < row; i++) {
        for ( j = 0; j < col; j++) {
            char karakter = fgetc(dosya);
            if (karakter == EOF) {
                // fprintf(stderr, "Dosya yeterince uzun degil.\n");
                // fclose(dosya);
                exit(1);
            }
            matris[i][j] = karakter;
        }
        // Satir sonundaki bosluk karakterini atla
        fgetc(dosya);
    }
    matrisyazdir(row, col, matris);
    return (matris);
}

int dosyadanOku(struct userInfo *kullainicbilgi) {

    FILE* data_dosya = fopen("kullanici_veritabani.txt", "r");
    if (data_dosya == NULL) {
        printf("Dosya acilamadi veya bulunamadi.\n");
        exit(1);
    }
    int kisi_sayisi=0;
    while(fscanf(data_dosya, "%s %s %d", kullainicbilgi[kisi_sayisi].kullaniciAdi, 
    kullainicbilgi[kisi_sayisi].sifre, &kullainicbilgi[kisi_sayisi].skor) == 3){
        kisi_sayisi++;
    }
    // simdi eski kullanici sayisini hesapladim ve struct icerisinde tuttugum kullanicisayisi degiskenine atadim
    // her program acilidiginda kullanici sayisi degiskeni eski userlarin sayisini tutacak
    kullainicbilgi->userData.kullaniciSayisi = kisi_sayisi;
    
    // Dosyayi kapat
    fclose(data_dosya);

    return(kisi_sayisi);
}

void dosyayaYaz(struct userInfo *kullanicibilgi) {
    FILE* data_dosya = fopen("kullanici_veritabani.txt", "a");
    if (data_dosya == NULL) {
        printf("Dosya acilamadi veya bulunamadi.\n");
        return;
    }

    fprintf(data_dosya, "%s %s 0",kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].kullaniciAdi,
    kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].sifre);
    kullanicibilgi->userData.kullaniciSayisi++;
    fclose(data_dosya);

    printf("Hesap olusturuldu.\n");

}

int kullaniciVarMi( struct userInfo *kullanicibilgi){
    int i;
    // Ayni kullanici adinin dosyada olup olmadigini kontrol et
    for ( i = 0; i < kullanicibilgi->userData.kullaniciSayisi -1 ; i++) {
        if (strcmp( kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].kullaniciAdi, kullanicibilgi[i].kullaniciAdi) == 0) {
            return (1); // kullanici ismi var 
        }
    }
    return 0; // kullanici ismi daha once kullanilmamis = bu isimle yeni hesap olusturabilir
}

int girisYap(struct userInfo *kullanicibilgi) {
    int i;
    for(i=0;i<kullanicibilgi->userData.kullaniciSayisi;i++){
        if(strcmp(kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].kullaniciAdi,kullanicibilgi[i].kullaniciAdi)==0 && 
        strcmp(kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].sifre,kullanicibilgi[i].sifre)==0 ){
            return 1; // kullanici ismi ve sifre uyustu 
        }
    }
    return 0;
}

void enYuksekSkorlariYazdir(struct userInfo *kullanicibilgi) {
    struct userInfo siralikullanicilar[MAX_USERS];
    int i,j;
    // Kullanicilari sirali bir sekilde yeni diziye kopyala
    for ( i = 0; i < kullanicibilgi->userData.kullaniciSayisi; i++) {
        siralikullanicilar[i] = kullanicibilgi[i];
    }

    // Siralama islemini yeni dizide yap
    for (i = 0; i < kullanicibilgi->userData.kullaniciSayisi - 1; i++) {
        for ( j = 0; j < kullanicibilgi->userData.kullaniciSayisi - i - 1; j++) {
            if (siralikullanicilar[j].skor < siralikullanicilar[j + 1].skor) {
                // Skorlari takas et
                struct userInfo temp = siralikullanicilar[j];
                siralikullanicilar[j] = siralikullanicilar[j + 1];
                siralikullanicilar[j + 1] = temp;
            }
        }
    }

  printf("\n\nEn Yuksek 5 Skor:\n");
    for ( i = 0; i < 5; i++) {
        printf("%s: %d\n", siralikullanicilar[i].kullaniciAdi, siralikullanicilar[i].skor);
    }
}

void oyunkurallariyazdir(){
    printf("\n--------------------------------------------------------------Hosgeldinn-----------------------------------------------------------\n");
    printf("bu bir labirent oyunudur labirentte amac olabildigince cok karsit madde olusturmaktir ((+p) + (-e) = H) ,ne kadar cok \n");
    printf("H toplarsan skorun o kadar cok yuksek olur. manuel modda oyunu istedigin dort yone ok tuslariyla giderek oynayabilirsin.\n");
    printf("Karadelikler(k) uzerine gelinirse oyun sonlanir.x harfi oyunda seni temsil eder. Duvarlara(1) ve labirent disina hamle yapildiginda\n");
    printf("yerin degismez. istedigin zaman esc tusuna basarak oyundan cikabilirsin.Her hamle ile elde edilmis atom alti parcaciklar\n");
    printf("ve labirentten ciktiginda kac karsit madde uretildigi ekrana yazilir. Auto play modunda oyun,kendi kendine oynar.\n\n");
    printf("Labirentin elemanlari asagidaki gibidir. \nP+ : P \nP- : p\ne- : e \ne+ : E \nKara Delik : K \nKullanici : X \nCikis : C \nYol : 0 \nDuvar : 1 \nGiris : G\n\n");

}

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

void clearScreen() {
    // Clear the console screen
    system("cls");
}

int elementHesapla(struct elementler elementler){

    int sonuc1 =0;
    int elementH = 0;

    sonuc1 = elementler.artiP - elementler.eksiP ;
    if ( sonuc1 < 0){
        sonuc1 = sonuc1 * (-1);
        elementler.eksiP = sonuc1;
        elementler.artiP = 0;
    }
    else if ( sonuc1 >= 0){
        elementler.artiP = sonuc1;
        elementler.artiE = 0;
    }
    

    int sonuc2=0;
    sonuc2 = elementler.artiE - elementler.eksiE ;
    if ( sonuc1 < 0){
        sonuc1 = sonuc1 * (-1);
        elementler.eksiE = sonuc1;
        elementler.artiE = 0 ;
    }
    else if ( sonuc1 >= 0){
        elementler.artiE = sonuc1;
        elementler.eksiE = 0;
    }

    if (elementler.eksiP > 0 && elementler.artiE > 0 ){
        if (elementler.eksiP < elementler.artiE){
            elementH = elementler.eksiP;
        }
        else {
            elementH = elementler.artiE;
        }
    }
    printf(" %d adet element olustrdun\n", elementH);
    return elementH;
}

void elementleriYazdir(struct elementler elementler){
    if(elementler.artiE > 0){
        printf("%d adet +e topladin \n", elementler.artiE);
    }
    if(elementler.artiP > 0){
        printf("%d adet +p topladin \n", elementler.artiP);
    }
    if(elementler.eksiE > 0){
        printf("%d adet -e topladin \n", elementler.eksiE);
    }
    if(elementler.eksiP > 0){
        printf("%d adet -p topladin \n", elementler.eksiP);
    }
}

void ManuelMode(struct elementler elementler){
    int secim,zorluk;
    int row, col;
    FILE *dosya;
    char** labirent = (char **)malloc(MAX_USERS +1 * sizeof(char *));

    printf("\n--------------------Manuel mod---------------------\n");
    printf("1-hazir labirent\n2-ben kendi labirentimi yuklemek isterim\n");
    scanf("%d", &secim);
    if(secim == 1){
        // hazir labirent:
        printf("1'den 5'e kadar zorluk derecesi sec\n");
        scanf("%d", &zorluk);
        switch (zorluk){
            case 1:
                dosya = fopen("0.txt", "r");
                if (dosya == NULL) {
                perror("Dosya acma hatasi");
                exit (1);
                }
                if (fscanf(dosya, "%d %d", &row, &col) != 2) {
                 // stderr = standard error
                fprintf(stderr, "Dosya formati uyumsuz.\n");
                fclose(dosya);
                exit(1);
                }
                labirent = matrisOku(dosya,row,col);
                break;

            case 2:
                dosya = fopen("1.txt", "r");
                if (dosya == NULL) {
                perror("Dosya acma hatasi");
                exit (1);
                }
                if (fscanf(dosya, "%d %d", &row, &col) != 2) {
                 // stderr = standard error
                fprintf(stderr, "Dosya formati uyumsuz.\n");
                fclose(dosya);
                exit(1);
                }
                labirent = matrisOku(dosya,row,col);
                break;

            case 3:
                dosya = fopen("2.txt", "r");
                if (dosya == NULL) {
                perror("Dosya acma hatasi");
                exit (1);
                }
                if (fscanf(dosya, "%d %d", &row, &col) != 2) {
                 // stderr = standard error
                fprintf(stderr, "Dosya formati uyumsuz.\n");
                fclose(dosya);
                exit(1);
                }
                labirent = matrisOku(dosya,row,col);
                break;

            case 4:
                dosya = fopen("3.txt", "r");
                if (dosya == NULL) {
                perror("Dosya acma hatasi");
                exit (1);
                }
                if (fscanf(dosya, "%d %d", &row, &col) != 2) {
                 // stderr = standard error
                fprintf(stderr, "Dosya formati uyumsuz.\n");
                fclose(dosya);
                exit(1);
                }
                labirent = matrisOku(dosya,row,col);
                break;

            case 5:
                dosya = fopen("4.txt", "r");
                if (dosya == NULL) {
                perror("Dosya acma hatasi");
                exit (1);
                }
                if (fscanf(dosya, "%d %d", &row, &col) != 2) {
                 // stderr = standard error
                fprintf(stderr, "Dosya formati uyumsuz.\n");
                fclose(dosya);
                exit(1);
                }
                labirent = matrisOku(dosya,row,col);
                break;

            default:
            printf("Invalid choice.\n");
        }

    }
    else if (secim == 2){
        char dosyaAdi[50];

        printf("oyun haritasi text dosyasi icinde olmalidir, ilk satirda haritanin ebatlari yazilir\n");
        printf("mesela: 2 3\n01e\n0X0 \ngibi...\n");
        printf("lutfen dosya adini girin: (benimlabirent.txt) gibi\n");
        scanf("%s", &dosyaAdi);

        // bu durumu temizlemek iÃ§in bir kontrol yapalim
        if (dosyaAdi[strlen(dosyaAdi) - 1] == '\n') {
            dosyaAdi[strlen(dosyaAdi) - 1] = '\0'; // '\n' karakterini '\0' ile degistir
        }
        dosya = fopen(dosyaAdi, "r");
        if (dosya == NULL){
            printf("dosya bulunmadi\n");
            exit (1);
        }
        if (fscanf(dosya, "%d %d", &row, &col) != 2) {
            // stderr = standard error
            fprintf(stderr, "Dosya formati uyumsuz.\n");
            fclose(dosya);
            exit(1);
        }
        labirent = matrisOku(dosya,row,col);
    }

    // finding the X's location in the matrix
    int Xlocation;
    Xlocation = findXlocation(labirent,row,col);
    int Xrow,Xcol;
    if (Xlocation != -1) {
        Xrow = Xlocation / 10;
        Xcol = Xlocation % 10;
    }
    else{
        printf("x is not found in the maze!\n");
    }


char a, key;
int XmoveCounter = 0 ;
int temp;

    do{    

                a = getch();
                if (a == 0) {  // Kontrol karakteri algılandı
                    key = getch();

                    switch (key) {
                        case 72:

                            //Up arrow key pressed

                            temp = Xrow -1;
                            if (temp < 0){
                                printf("labirent siniri disina ciktin :(");
                            }
                            else if (labirent[temp][Xcol] == '1'){
                                printf("duvar var :( hareket edemezsin");
                            }
                            else if ( labirent[temp][Xcol] == 'K'){
                                printf("karadelige girdin");
                                printf("GAME OVER!!");
                                key = 27;
                            }
                            else if (labirent[temp][Xcol] == 'C'){
                                printf("cikisa ulastin");
                                elementHesapla(elementler);
                            }
                            else if( labirent[temp][Xcol] == '0' || labirent[temp][Xcol] == 'G'){
                                if (XmoveCounter == 0 ){
                                    labirent[Xrow][Xcol] = 'G';
                                }
                                else {
                                    labirent[Xrow][Xcol] = '0';
                                }
                                Xrow = temp;
                                labirent[Xrow][Xcol] ='X';

                            }
                            else if (labirent [temp][Xcol] == 'P' || labirent [temp][Xcol] == 'p'|| labirent [temp][Xcol] == 'E'|| labirent [temp][Xcol] == 'e'){

                                if( labirent[temp][Xcol] == 'P'){
                                    elementler.artiP ++;
                                }
                                else if(labirent[temp][Xcol] == 'p'){
                                    elementler.eksiP ++;
                                }
                                else if(labirent[temp][Xcol] == 'E'){
                                    elementler.artiE ++;
                                }
                                else if(labirent[temp][Xcol] == 'e'){
                                    elementler.eksiE ++;
                                }

                                if (XmoveCounter == 0 ){
                                    labirent[Xrow][Xcol] = 'G';
                                }
                                else {
                                    labirent[Xrow][Xcol] = '0';
                                }

                                Xrow = temp;
                                labirent[Xrow][Xcol] ='X';
                            }

                            break;
                            clearScreen();

                        case 80:

                            //Down arrow key pressed
                            
                            temp = Xrow +1;
                            if (temp > row){
                                printf("u r out");
                            }
                            else if (labirent[temp][Xcol] == '1'){
                                printf("duvar var");
                            }
                            else if ( labirent[temp][Xcol] == 'K'){
                                printf("karadelige girdin");
                                key = 27;
                            }
                            else if (labirent[temp][Xcol] == 'C'){
                                printf("cikisa ulastin");
                                elementHesapla(elementler);                                
                            }
                            else if( labirent[temp][Xcol] == '0'){
                                if (XmoveCounter == 0 ){
                                    labirent[Xrow][Xcol] = 'G';
                                }
                                else {
                                    labirent[Xrow][Xcol] = '0';
                                }
                                Xrow = temp;
                                labirent[Xrow][Xcol] ='X';

                            }
                            else if (labirent [temp][Xcol] == 'P' || labirent [temp][Xcol] == 'p'|| labirent [temp][Xcol] == 'E'|| labirent [temp][Xcol] == 'e'){
                                
                                if(labirent[temp][Xcol] == 'P'){
                                    elementler.artiP ++;
                                }
                                else if(labirent[temp][Xcol] == 'p'){
                                    elementler.eksiP ++;
                                }
                                else if(labirent[temp][Xcol] == 'E'){
                                    elementler.artiE ++;
                                }
                                else if(labirent[temp][Xcol] == 'e'){
                                    elementler.eksiE ++;
                                }
                                
                                if (XmoveCounter == 0 ){
                                    labirent[Xrow][Xcol] = 'G';
                                }
                                else {
                                    labirent[Xrow][Xcol] = '0';
                                }
                                Xrow = temp;
                                labirent[Xrow][Xcol] ='X';
                            }

                            break;
                            clearScreen();

                        case 77:
                            //Right arrow key pressed
                            
                            temp = Xcol +1 ;
                            if (temp > col){
                                printf("u r out");
                            }
                            else if (labirent [Xrow][temp] == '1'){
                                printf("duvar var");
                            }
                            else if ( labirent [Xrow][temp] == 'K'){
                                printf("karadelige girdin");
                                key = 27;
                            }
                            else if (labirent [Xrow][temp] == 'C'){
                                printf("cikisa ulastin");
                                elementHesapla(elementler);
                            }
                            else if( labirent [Xrow][temp] == '0'){
                                if (XmoveCounter == 0 ){
                                    labirent[Xrow][Xcol] = 'G';
                                }
                                else {
                                    labirent[Xrow][Xcol] = '0';
                                }
                                Xcol = temp;
                                labirent[Xrow][Xcol] ='X';

                            }
                            else if (labirent [Xrow][temp] == 'P' || labirent [Xrow][temp] == 'p'|| labirent [Xrow][temp] == 'E'|| labirent [Xrow][temp] == 'e'){
                                
                                if( labirent [Xrow][temp] == 'P'){
                                    elementler.artiP ++;
                                }
                                else if(labirent [Xrow][temp] == 'p'){
                                    elementler.eksiP ++;
                                }
                                else if(labirent [Xrow][temp] == 'E'){
                                    elementler.artiE ++;
                                }
                                else if(labirent [Xrow][temp] == 'e'){
                                    elementler.eksiE ++;
                                }                                
                                
                                if (XmoveCounter == 0 ){
                                    labirent[Xrow][Xcol] = 'G';
                                }
                                else {
                                    labirent[Xrow][Xcol] = '0';
                                }
                                Xcol = temp;
                                labirent[Xrow][Xcol] ='X';
                            }

                            break;
                            clearScreen();
                            
                        case 75:

                            //Left arrow key pressed

                            temp = Xcol-1 ;
                            if (temp < 0){
                                printf("labirent disina ciktin");
                            }
                            else if (labirent [Xrow][temp] == '1'){
                                printf("duvar var");
                            }
                            else if ( labirent [Xrow][temp] == 'K'){
                                printf("karadelige girdin");
                                key = 27;

                            }
                            else if (labirent [Xrow][temp] == 'C'){
                                printf("cikisa ulastin");
                                elementHesapla(elementler);
                            }
                            else if( labirent [Xrow][temp] == '0'){
                                if (XmoveCounter == 0 ){
                                    labirent[Xrow][Xcol] = 'G';
                                }
                                else {
                                    labirent[Xrow][Xcol] = '0';
                                }
                                Xcol = temp;
                                labirent[Xrow][Xcol] ='X';

                            }
                            else if (labirent [Xrow][temp] == 'P' || labirent [Xrow][temp] == 'p'|| labirent [Xrow][temp] == 'E'|| labirent [Xrow][temp] == 'e'){
                                
                                if( labirent [Xrow][temp] == 'P'){
                                    elementler.artiP ++;
                                }
                                else if(labirent [Xrow][temp] == 'p'){
                                    elementler.eksiP ++;
                                }
                                else if(labirent [Xrow][temp] == 'E'){
                                    elementler.artiE ++;
                                }
                                else if(labirent [Xrow][temp] == 'e'){
                                    elementler.eksiE ++;
                                }
                                
                                if (XmoveCounter == 0 ){
                                    labirent[Xrow][Xcol] = 'G';
                                }
                                else {
                                    labirent[Xrow][Xcol] = '0';
                                }
                                Xcol = temp;
                                labirent[Xrow][Xcol] ='X';
                            }
                            break;
                            clearScreen();

                            default :
                            printf("yalnis tusa basildi");

                    }

                    XmoveCounter ++;

                    elementleriYazdir(elementler);
                    matrisyazdir(row,col,labirent);

                }
        } while (key != 27);
}

 void AutoMode(int row,int col, char **labirent, struct point start, struct point end){
//     int dRow[4] = {-1, 1, 0, 0}; // Yukarı, aşağı
//     int dCol[4] = {0, 0, -1, 1}; // Sol, sağ
//     int visited[row][col] ;
//     struct Point *queue= (struct point *)malloc(((row*col) + 1) * sizeof(struct point));
//     int front = 0, rear = 1;
//     queue[rear] = start;
//     visited[start.row][start.col] = 1;

//     while (front < rear) {
//         struct Point current = queue[front++];

//         if (current.row == end.row && current.col == end.col) {
//             return 1;
//         }

//         for (int i = 0; i < 4; i++) {
//             int newRow = current.row + dRow[i];
//             int newCol = current.col + dCol[i];

//             if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < COL &&
//                 !visited[newRow][newCol] && labirent[newRow][newCol] != '1') {
//                 Point next = {newRow, newCol};
//                 queue[rear++] = next;
//                 visited[newRow][newCol] = 1;
//             }
//         }

//     }

//     return 0;
 }

/*----------------------------------- main function ------------------------------------- */

int main() {
    struct userInfo *kullanicibilgi = (struct userInfo *)malloc((MAX_USERS + 1) * sizeof(struct userInfo));
    char isim[10], soyisim[10];
    int secim,secim2,secim3,kisi_sayisi,i;
    kisi_sayisi = dosyadanOku(kullanicibilgi);
    kullanicibilgi->userData.kullaniciSayisi = 0;
    kullanicibilgi->userData.kullaniciSayisi = kisi_sayisi;
    int bool=0;
    struct elementler elementler;
    elementler.artiE = 0; 
    elementler.artiP = 0;
    elementler.eksiE = 0;
    elementler.eksiP = 0;



    printf("-------------------welcome--------------------\n");
    do{
        printf("1-hesap olustur \n2-giris yap \n3-cikis\n");
        scanf("%d", &secim);

        if(secim == 1){
             // hesap olustur
            printf("isim : ");
            scanf("%s", &isim);
            printf("soyisim :");
            scanf("%s", &soyisim);
            printf("Kullanici Adi: ");
            scanf("%s", &kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].kullaniciAdi);
            printf("Sifre: ");
            scanf("%s", &kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].sifre);

            // Kullanici var mi kontrolÃ¼
            if (kullaniciVarMi(kullanicibilgi)) {
                printf("Kullanici zaten var.\n\n");
                bool = 1;
            }
            else if(!kullaniciVarMi(kullanicibilgi)){
                // Hesap olustur
                dosyayaYaz(kullanicibilgi);
                bool = 0;
            }
        }


        else if(secim == 2){
            // Kullanicidan kullanici adi ve sifre bilgilerini al
            printf("Kullanici Adi: ");
            scanf("%s", &kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].kullaniciAdi);
            printf("Sifre: ");
            scanf("%s", &kullanicibilgi[kullanicibilgi->userData.kullaniciSayisi].sifre);
            // Giris yap
            if (girisYap( kullanicibilgi)) {
                printf("Giris basarili!\n");
                bool = 0;
            }
            else {
                printf("Kullanici adi veya sifre yanlis.\n\n");
                bool = 1;
            }
        }   
        else if (secim == 3){
            bool = 0;
        }
    }while(bool == 1);

    enYuksekSkorlariYazdir(kullanicibilgi);
    printf("\n1-oyun kurallarini ogrenmek ister misin ?\n2-oynamaya basla \n");
    scanf("%d", &secim2);
    
    if(secim2 == 1){
         oyunkurallariyazdir();
    }
    else if (secim2 == 2){
        printf("\nhangi modda oynamak istersin : \n1-Manuel Mode\n2-Auto Mode\n");
        scanf("%d", &secim3);
        if (secim3 == 1){
            ManuelMode(elementler);
        }
        else if (secim3 == 2){
            // AutoMode(row,col,labirent);
        }
    }

    return 0;
}
