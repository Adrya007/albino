#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h> // do funkcji getch()

#include "galeria.h"
#include "galeria.cpp"

using namespace std;

//funkcje globalne:
//void kolorek(int);
void wyswietlajka();
void wybierajka();

KatalogGalerii db("Warszawa", 1, 1); //stworzenie obiektu db katalogu galerii

//------------
int main( int argc, char* argv[] )
{
        /*
                 katalog eksponatow zostaje zaladowany przy starcie programu
                 0 - brak komunikatu czy wczytac baze,
                 0 - baza nie ulega skasowaniu
         */
        system("COLOR 1e");
        db.wczytajKatalogZPliku(0, 0);
        wybierajka();
        db.saveAutoIncrement(); //zapisanie wartosci ostatnio dodanego ID
        return 0;
}
/*
void color(int i) { // funkcja wlacza kolorowanie // wylaczam - program mial byc uniwersalny, funkcja dziala tylko pod Windowsem
        if (i==1) {
                // czerwony
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        } else if (i==2)        {
                // bialy
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else if (i==3) {
                // zielony
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        } else if (i==4) {
                // niebieski
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        } else if (i==5) {
                // czarno na bialym
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
        } else {
                //
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
}*/

//--------------

void wyswietlajka()
{

       // system("COLOR 1e");
        cout<<"\n\n====== Katalog galerii sztuki 'ADA' ======\n";
        db.returnAutoIncrementAndLiczbaRekordow();
        cout<<"\n";
        cout<<"1";
        cout<<" - wczytaj katalog z pliku, \n";
        cout<<"2";
        cout<<" - zapisz katalog,\n";
        cout<<"3";
        cout<<" - skasuj katalog,\n";
        cout<<"4";
        cout<<" - dodaj nowy eksponat,\n";
        cout<<"5";
        cout<<" - usun eksponat,\n";
        cout<<"6";
        cout<<" - edytuj eksponat,\n";
        cout<<"7";
        cout<<" - wyswietl eksponaty,\n";
        cout<<"8";
        cout<<" - posortuj eksponaty,\n";
        cout<<"9";
        cout<<" - wyszukaj eksponat,\n";
        cout<<"i";
        cout<<" - wyswietl informacje o galerii sztuki 'ADA',\n";
        cout<<"k";
        cout<<" - koniec.\n";
}

void wybierajka() {
wyswietlajka();
char nawigacja;
bool wybrano_poprawny_klawisz = 0;
bool exit = 0;
        do {
                nawigacja = _getch(); // pobiera znak tak dlugo az zostana wcisniete strzalki gora/dol lub enter
                switch(nawigacja) {
                        case '1':
                                db.wczytajKatalogZPliku(1, 1);//1 - komunikat z pytaniem czy zaladowac baze, 1 - uruchom funkcje czyszczaca baze przed zaladowaniem rekordow z pliku
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case '2':
                                db.zapiszKatalogDoPliku();
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case '3':
                                cout<<"Czy na pewno chcesz skasowac baze danych?\n"
                                        <<"1 - Skasuj baze danych w pamieci programu\n"
                                        <<"2 - Skasuj tylko baze danych w pliku txt\n"
                                        <<"3 - Anuluj\n";
                                char nawigacja_kasuj;
                                do {
                                        nawigacja_kasuj = _getch();
                                } while(nawigacja_kasuj != '1' && nawigacja_kasuj != '2' && nawigacja_kasuj != '3');
                                if(nawigacja_kasuj == '1') {
                                        db.skasujKatalog(1);//komunikat o udanym skasowaniu + zapytanie czy zapisac rowniez zmiany w bazie txt
                                } else if(nawigacja_kasuj == '2') {
                                        db.wyczyscKatalogWPliku();
                                        cout<<"Baza danych w pliku txt zostala wyczyszczona.";
                                } else {
                                        cout<<"Anulowano kasowanie bazy.";
                                }
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case '4':
                                cout<<"1 - Dodaj eksponat na poczatek listy\n"
                                        <<"2 - Dodaj eksponat na koniec listy\n"
                                        <<"3 - Anuluj.\n";
                                char nawigacja_dodaj;
                                do {
                                        nawigacja_dodaj = _getch();
                                } while(nawigacja_dodaj != '1' && nawigacja_dodaj != '2' && nawigacja_dodaj != '3');
                                if(nawigacja_dodaj == '1') {
                                        db.dodajNaPoczatek();
                                } else if(nawigacja_dodaj == '2') {
                                        db.dodajNaKoniec();
                                } else cout<<"Anulowano.\n";
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case '5':
                                db.usunEksponat();
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case '6':
                                cout<<"\nUsluga edytowania istniejacego eksponatu w trakcie realizacji...\n";
                               /* db.edytujEksponat();*/
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case '7':
                                db.wypiszKatalog();
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case '8':
                                db.sortujEksponaty();
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case '9':
                                cout<<"\nUsluga wyszukiwania istniejacego eksponatu w trakcie realizacji...\n";
                                /*db.WyszukajRekordy();*/
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case 'i':
                                db.wypiszInfoOGalerii();
                                wybrano_poprawny_klawisz = 1;
                                break;
                        case 'k':
                                cout<<"\nZanim wyjdziesz z programu:\n ";
                                db.zapiszKatalogDoPliku(1,0);//0 - brak pytania czy zaladowac do pamieci programu zaktualizowana baze
                                wybrano_poprawny_klawisz = 1;
                                exit = 1;
                                break;
                }
        } while(wybrano_poprawny_klawisz==0);
        if(exit!=1) {
                cout<<"\n\n";
                system("pause");
                wybierajka();
        }
}
