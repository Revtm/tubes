#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <queue>
using namespace std;

void gotoxy(short int x, short int y);

typedef char infotype;
typedef struct TElmtList *address;
typedef struct TElmtList{
 infotype info;
 address next;
 address prev;
} ElmtList;

typedef struct {
 address first;
 address last;
}List ;

 //SELEKTOR
#define Info(P) (P)->info
#define Next(P) (P)->next
#define Prev(P) (P)->prev
#define First(L) (L).first
#define Last(L) (L).last

//KONSTANTA
#define Nil NULL
#define Infinity 99999


/****************** TEST LIST KOSONG ******************/
bool IsEmpty(List L) {
/* Mengirim true jika list kosong. Lihat definisi di atas. */
 return (First(L) == NULL && Last(L) == NULL);
}


/****************** PEMBUATAN LIST KOSONG ******************/
void createList(List *L) {
 First(*L) = NULL;
 Last(*L) = NULL;
}

/****************** Manajemen Memori ******************/
address Allocation(infotype x) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
 address NewElmt;
 NewElmt = (ElmtList*) malloc (sizeof(ElmtList));
 Info(NewElmt) = x;
 Next(NewElmt) = Nil;
 Prev(NewElmt) = Nil;
 return NewElmt;
}

void Deallocation(address hapus) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
 free(hapus);
}


/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X){
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
	address P = First(L);
	while (P != Nil){
		if (Info(P) == X){
			return P;
		}
		P = Next(P);
	}
	return Nil;
}


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsertFirst(List *L, infotype x) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
 address NewElmt;
 NewElmt = Allocation(x);
 if (NewElmt != NULL) {
 if(IsEmpty(*L)){
 First(*L) = NewElmt;
 Last(*L) = NewElmt;
 } else{
 Next(NewElmt) = First(*L);
 Prev(First(*L)) = NewElmt;
 First(*L) = NewElmt;
 }
 }
}

void InsertLast(List *L, infotype x) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
 address NewElmt;
 NewElmt = Allocation(x);
 if (NewElmt != NULL) {
 if(IsEmpty(*L)){
 InsertFirst(L,x);
 } else{
 Next(Last(*L)) = NewElmt;
 Prev(NewElmt) = Last(*L);
 Last(*L) = NewElmt;
 }
 }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/

void DelFirst (List *L){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
	address P = First(*L);
	First(*L) = Next(P);
	Prev(First(*L)) = Nil;
	Deallocation(P);
}


void printQ(List *L){
    char x;
    address Elmt = First(*L);
    gotoxy(10,2);cout << "-------------------" << endl;
    gotoxy(10,3);
    while(Elmt != NULL){
        cout << Info(Elmt) << " ";
        Elmt = Next(Elmt);
    }

    gotoxy(10,4);cout << "-------------------" << endl;
    gotoxy(10,5);cout << "tekan apa saja untuk menghasilkan list random" << endl;
    gotoxy(10,6);cout << "tekan q untuk keluar" << endl;


    //gotoxy(10,6); cout <<"Tebak angka: ";
    // cin >> x;
}

void pushangka(int x, List *L){
        if(x == 1){
            InsertLast(&(*L), '1');
        }else if( x == 2){
            InsertLast(&(*L), '2');
        }else if( x == 3){
            InsertLast(&(*L), '3');
        }else if( x == 4){
            InsertLast(&(*L), '4');
        }else if( x == 5){
            InsertLast(&(*L), '5');
        }else if( x == 6){
            InsertLast(&(*L), '6');
        }else if( x == 7){
            InsertLast(&(*L), '7');
        }else if( x == 8){
            InsertLast(&(*L), '8');
        }else if( x == 9){
            InsertLast(&(*L), '9');
        }else{
            InsertLast(&(*L), '0');
        }

}

int main(){
    List L;
    int x,y,z = 0,z2 = 0;

    createList(&L);

    awal:
    srand(time(0));
    for(int i = 0 ; i < 10 ; i++){
        x = rand()%10;
        y = rand()%2;

        if(y == 1){
          if(z < 5)pushangka(x, &L);
          else InsertLast(&(L), '_');
          z++;
        }else{
          if(z2 > 4)pushangka(x, &L);
          else InsertLast(&(L), '_');
          z2++;
        }
    }

    printQ(&L);
    cout << endl;
    gotoxy(10,7); char ulang = getch();
    if(ulang != 'q'){
        system("cls");
        z = 0; z2 = 0;
        createList(&L);
        goto awal;
    }

    return 0;
}

void gotoxy(short int x, short int y){

  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}
