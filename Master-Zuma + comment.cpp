#include<bits/stdc++.h>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
using namespace std;


#define REPup(i, a, p)  for(int (i) = int (a); i<int (p); i++) //mendefine perulangan for dari a sampai p dengan a++
#define REPdown(i, a, p)  for(int (i) = int (a); i>=int (p); i--)//perulangan for dari a sampai p dengn a--

//***************************  Double Linked List  ****************************
//*****************************************************************************
typedef char infotype; // tipe data karakter yang ditampilkan dalam list zuma
typedef struct TElmtList *address;
typedef struct TElmtList{
  infotype info;
  address next;
  address prev;
}ElmtList;

typedef struct {
  address first;
  address last;
}List ;

 //SELEKTOR

#define Info(P) (P)->info

#define Next(P) (P)->next

#define Prev(P) (P)->prev

#define First(L) ((L).first)

#define Last(L) ((L).last)



//KONSTANTA

#define Nil NULL

#define Infinity 99999


//
void pilihMenuu(List *data, List data1, List data2, int *nyawa);
void instruksi();


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
 address NewElmt;

 NewElmt = (ElmtList*) malloc (sizeof(ElmtList));
 Info(NewElmt) = x;
 Next(NewElmt) = Nil;
 Prev(NewElmt) = Nil;
 return NewElmt;
 //dikembalikan gerbong yang memiliki isi nilai x, next = Nil, dan prev = Nil
}



void Deallocation(address hapus) {
 free(hapus);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/

//mencari sesuai parameter sebelum dan sesudah yang diinput dalam game
//digunakan dalam pilihan input angka tebakan sebelum dan sesudah
address Search1(List L, infotype sebelum, infotype sesudah){
	address P = First(L);
	while (P != Nil){
		if ( Prev(P) != Nil && Next(P) != Nil && (Next(P)->info == sesudah && Prev(P)->info == sebelum) && Info(P) == '_' ){
			return P;
		}
		P = Next(P);
	}
	return Nil;
}

void InsertFirst(List *L, infotype x) {
     address NewElmt;
     NewElmt = Allocation(x);
     if (NewElmt != NULL) {
      	if(IsEmpty(*L)){
      		First(*L) = NewElmt;
      		Last(*L) = NewElmt;
      	}
      	else{
      		Next(NewElmt) = First(*L);
      		Prev(First(*L)) = NewElmt;
      		First(*L) = NewElmt;
      	}
    }
}

void InsertLast(List *L, infotype x) {
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


void Outputdata(List L){  //output list dalam game Zuma
    address temp = (L).first;
    while(temp!=NULL){
        cout<<temp->info<<" ";
        temp = temp->next;
    }
}


void iinterface(){ //tampilan menu ketika game telah dimulai
	cout<<"Posisi Tebakkan Anda: \n";
	cout<<"a. Sebelum \nb. Setelah \nc. Awal \nd. Akhir\n";
	cout<<"Masukkan Posisi: ";
}

//mengecek apakah satu elemen dan dua elemen sebelum (prev) elemen yang ditebak memiliki info yang sama
bool cekPrev(List L, address temp){
	return (Prev(temp)!=NULL && Prev(Prev(temp)) != NULL && Info(temp) == Info(Prev(temp)) && Info(temp) == Info(Prev(Prev(temp))));
}

//mengecek apakah satu elemen dan dua elemen sesudah (next) elemen yang ditebak memiliki info yang sama
bool cekNext(List L, address temp){
	return (Next(temp)!=NULL && Next(Next(temp))!= NULL && Info(temp) == Info(Next(temp)) && Info(temp) == Info(Next(Next(temp))));
}


//mengecek apakah satu elemen sesudah dan satu elemen sebelum elemen yang ditebak memiliki info yang sama
bool cekBetween(List L, address temp){
	return (Prev(temp)!=NULL && Next(temp)!=NULL && Info(temp) == Info(Next(temp)) && Info(temp) == Info(Prev(temp)) );
}

void pushangka(int x, List *L){ //mengkonversi angka bertipe int ke tipedata char
        if(x == 1){             //dan melakukan insert ke dalam list Zuma
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

void randomLIST(List *L, int i){  //menghasilkan list dengan angka dan posisi kosong '_' yang random

    int x,y,angka = 0,simbol = 0;

    //jika i = 0 , maka akan memberikan kembalian angka random by time
    // jika i = selain 0 , akan mengembalikan angka random sesuai sistem
    if(i == 0){
  		srand(time(0));
  	}

    REPup(j, 0, 10){ //perulangan untuk menghasilkan list dengan 10 karakter
        x = rand()%10; //mengembalikan angka random 0-9 -> untuk angka dalam list
        y = rand()%2; //mengembalikan angka random 0-1 -> untuk merandom posisi karakter angka dan '_'

        if(y == 1){ //jika y = 1, maka akan menginsert angka kedalam list
          if(angka < 5)pushangka(x, &(*L)); //selama angka masih kurang dari 5 kali kemunculan

          else InsertLast(&(*L), '_'); //jika angka sudah mencapai 5 kali kemunculan

          angka++;

        }else{

          if(simbol > 4)pushangka(x, &(*L)); //jika karakter '_' telah terinsert 5 kali, maka aakan diinsert angka

          else InsertLast(&(*L), '_');//jika '_' belum mencapai 5 kali kemunculan

          simbol++;

        }
    }
}


//********************************* Antarmuka Menu Utama **********************************************
void interface1(){

	cout<<"                                             =============================\n";
	cout<<"============================================= SELAMAT DATANG DI GAME ZUMA =============================================\n";
	cout<<"                                             =============================\n\n";

	cout<<"                                             1. Pilih soal\n";
	cout<<"                                             2. Tentukan Kesempatan Menembak\n";
	cout<<"                                             3. Mulai Game\n";
	cout<<"                                             4. Instruksi Khusus\n";
	cout<<"                                             5. Keluar\n\n";
	cout<<"                                                Masukkan Pilihan Anda: ";

}

//pemilihan soal
void pilihSoal(List *data, List data1, List data2, int *nyawa){

	system("cls");
	cout<<"Pilihan Soal: \n";
	char pilih;
	cout<<"a. "; Outputdata(data1); cout<<"\n";
	cout<<"b. "; Outputdata(data2); cout<<"\n";

	cout<<"Masukkan Pilihan Soal: "; cin>>pilih;

	if(pilih == 'b') *data=data2;
	else if(pilih == 'a') *data=data1;
	else{
		cout<<"Inputan Salah!, silahkan masukkan lagi"; getche(); pilihSoal(data, data1, data2, nyawa); return;
	}

	pilihMenuu(data, data1, data2, nyawa);

}

//prosedur penginputan di dalam menu utama
void pilihMenuu(List *data, List data1, List data2, int *nyawa){
	system("cls");

	interface1();

	char pilih;

	cin>>pilih;

	switch (pilih){

		case '1' : pilihSoal(data, data1, data2, nyawa); break;

		case '2' : system("cls"); cout<<"Masukkan Nyawa : "; cin>>*nyawa; pilihMenuu(data, data1, data2, nyawa); break;

		case '3' : break;

		case '4' :instruksi(); getche(); pilihMenuu(data, data1, data2, nyawa); break;

		case '5' : exit(0); break;
		default  : cout<<"\t\t\t\t\tMasukkan Salah!, Silahkan Masukkan Pilihan Lagi! "; getche();pilihMenuu(data, data1, data2, nyawa);

	}

	system("cls");

}

//mengecek apakah yang diinput adalah karakter angka 0-9
bool isNumber(char n){
	return (n>='0' && n<='9');
}

//prosedur penginputan angka tebakan
void numberchoice(char *n){
	cout<<"\nMasukkan Angka Tebakan Anda : "; cin>>*n;
	if(isNumber(*n)) return;
	else {
		cout<<"Masukkan salah, silahkan masukkan lagi "; getche(); numberchoice(n);
	}
}

// Instruksi khusus untuk penginputan angka tebakan diantara sebelum dan sesudah dalam permainan
void instruksi (){
	system("cls");
	cout << "INSTRUKSI KHUSUS" << endl;
	cout << "  9 _ _ 7 8 _ 6 _ _ 8 " << endl;
	cout << "  Jika anda ingin memasukan angka setelah angka 9, " << endl;
	cout << "  Pilih menu 'b. setelah' dan kemudian input angka '9'  " <<endl;
	cout << "  Lalu input '_' pada perintah selanjutnya.\nKlik Sembarang untuk kembali...";
}

int main(){

	address temp=NULL;
	List data, data1, data2;
	int nyawa=3; // Variabel banyaknya kesempatan USER untuk menembak angka
	char pilih;
	infotype x, n, y;

	createList(&data); //Membuat List Kosong
	createList(&data1);
	createList(&data2);

	randomLIST(&data1,0);

	randomLIST(&data2,1);

	data = data1;

	pilihMenuu(&data, data1, data2, &nyawa);


	while(nyawa>0){

		system("cls");

		// play:

		Outputdata(data); // Menampilkan Susunan Angka

		cout<<"\nKesempatan Menembak: "<<nyawa; // Menampilkan sisa Kesempatan Menembak

		numberchoice(&n); // Meminta user menginputkan Angka yang akan ditembak



		iinterface(); // Memanggil fungsi Interface

		play:

		cin>>pilih; // User Memasukkan Pilihan Posisi
		pilih = tolower(pilih);
		switch(pilih){ // Case untuk Pilihan Posisi

			case 'a' :	cout<<"Angka: "; cin>>x; // Meminta user memasukkan Posisi Sebelum

						cout<<"Setelah Angka: "; cin>>y; //Meminta user memasukkan Posisi Setelah

						temp = Search1(data, y, x); // Proses pencarian posisi

						if(temp!=Nil) Info(temp) = n; // Proses reWrite/replace Info dengan angka pilihan user
						else {
							cout<<"Posisi Tidak ditemukan" ;
							getche();
						}
						break;

			case 'b' :	cout<<"Angka: "; cin>>x; // Meminta user memasukkan Posisi Setelah

						cout<<"Sebelum Angka: "; cin>>y; // Meminta user memasukkan Posisi Sebelum

						temp = Search1(data, x, y); // Proses pencarian posisi

						if(temp!=Nil) Info(temp) = n; // Proses reWrite/replace Info dengan angka pilihan user
						else {
							cout<<"Posisi Tidak ditemukan" ;
							getche();
						}
						break;

 			case 'c' :	if(First(data)->info == '_'){
			 				First(data)->info = n; // Proses reWrite/replace Info elemen pertama dengan angka pilihan user
							temp = First(data);
							break;
						}
						cout<<"Masukkan Salah! Posisi sudah terisi, anda kehilangan 1 kesempatan";
						getche();
						//goto play;
						break;


			case 'd' : if(Last(data)->info == '_'){
			 				Last(data)->info = n; // Proses reWrite/replace Info elemen pertama dengan angka pilihan user
							temp = Last(data);
							break;
						}
						cout<<"Masukkan Salah! Posisi sudah terisi, silahkan masukkan ulang.";
						getche();
						//goto play;
						break;

			default  : cout<<"Masukkan salah! Silahkan masukkan Lagi: "; goto play; break;

		}

		if(temp != Nil && (cekPrev(data, temp) || cekNext(data, temp) || cekBetween(data, temp))){ // Pengecekan kondisi apakah sudah berjejer 3 atau lebih angka yang sama
			system("cls");
			Outputdata(data);
			cout<<"\nAnda Beruntung"; // Jika sudah makan akan output "Anda Beruntung" dan

			return 0;
		}

		nyawa--; // jika belom dapat posisi angka berjejer >= 3 maka kesempatan menembak berkurang
		system("cls");
	}

		Outputdata(data); cout<<endl;

		cout<<"Anda Kurang Beruntung"; // Jika kesempatan menembak habis (daalam hal ini <1) maka

    											   // Output "anda Kurang Beruntung"
     	getche();

      return 0;
}
