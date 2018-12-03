#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <queue>
using namespace std;

void gotoxy(short int x, short int y);

void printQ(queue <char> *Q){
    char x;
    gotoxy(10,2);cout << "-------------------" << endl;
    gotoxy(10,3);
    for(int i = 0 ; i < 10 ; i++){
        cout << (*Q).front() << " ";
        (*Q).pop();
    }
    gotoxy(10,4);cout << "-------------------" << endl;
    gotoxy(10,5);cout << "tekan apa saja untuk menghasilkan list random" << endl;
    gotoxy(10,6);cout << "tekan q untuk keluar" << endl;

    //gotoxy(10,6); cout <<"Tebak angka: ";
    // cin >> x;
}

void pushangka(int x, queue <char> *Q){
        if(x == 1){
            (*Q).push('1');
        }else if( x == 2){
            (*Q).push('2');
        }else if( x == 3){
            (*Q).push('3');
        }else if( x == 4){
            (*Q).push('4');
        }else if( x == 5){
            (*Q).push('5');
        }else if( x == 6){
            (*Q).push('6');
        }else if( x == 7){
            (*Q).push('7');
        }else if( x == 8){
            (*Q).push('8');
        }else if( x == 9){
            (*Q).push('9');
        }else{
            (*Q).push('0');
        }

}

int main(){
    queue <char> Q;
    int x,y,z = 0,z2 = 0;

    awal:
    srand(time(0));
    for(int i = 0 ; i < 10 ; i++){
        x = rand()%10;
        y = rand()%2;

        if(y == 1){
          if(z < 5)pushangka(x, &Q);
          else Q.push('_');
          z++;
        }else{
          if(z2 > 4)pushangka(x, &Q);
          else Q.push('_');
          z2++;
        }
    }

    printQ(&Q);
    cout << endl;
    char ulang = getch();
    if(ulang != 'q'){
        system("cls");
        z = 0; z2 = 0;
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
