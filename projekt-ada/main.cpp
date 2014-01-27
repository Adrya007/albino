#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h> // zawiera funkcja getch()
#include <ctime> // time()
#include <Windows.h> //zawiera funkcje SetConsoleTextAttribute
#include "galeria.h"

using namespace std;

//deklaracja funkcji globalnych
void color(int);
void clear_screen();
void menu_glowne();

KatalogGalerii db("Warszawa", 1, 1); //tworze obiekt db katalogu

//------------
int main( int argc, char* argv[] )
{
	/*
	 *	ladujemy baze danych przy uruchomieniu programu,
	 *	0 - nie wyswietlamy komunikatu czy wczytac baze,
	 *	0 - nie kasujemy baze, bo przy pierwszym ladowaniu baza jest juz pusta
	 */
	db.wczytajKatalogZPliku(0, 0);
	menu_glowne();
	db.saveAutoIncrement(); //zapisanie wartosci ostatnio dodanego ID
	return 0;
}

void color(int i) { // funkcja wlacza kolorowanie napisow drukowanych przez cout
	if (i==1) {
		// czerwony
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	} else if (i==2)	{
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
		// domyslny kolor tekstu w konsoli
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}

//--------------

void clear_screen()
{

	//system("cls");
	cout<<"\n\n====== Katalog galerii sztuki 'ADA' ======\n";
	db.returnAutoIncrementAndLiczbaRekordow();
	color(1);
	cout<<"1";
	color(0);
	cout<<" - wczytaj katalog z pliku, \n";
	color(1);
	cout<<"2";
	color(0);
	cout<<" - zapisz katalog, \n";
	color(1);
	cout<<"3";
	color(0);
	cout<<" - skasuj katalog,\n";
	color(3);
	cout<<"4";
	color(0);
	cout<<" - dodaj nowy eksponat, \n";
	color(3);
	cout<<"5";
	color(0);
	cout<<" - usun eksponat, \n";
	color(3);
	cout<<"6";
	color(0);
	cout<<" - edytuj eksponat\n";
	color(4);
	cout<<"7";
	color(0);
	cout<<" - wyswietl eksponaty, \n";
	color(4);
	cout<<"8";
	color(0);
	cout<<" - posortuj eksponaty, \n";
	color(4);
	cout<<"9";
	color(0);
	cout<<" - wyszukaj eksponat\n";
	color(4);
	cout<<"10";
	color(0);
	cout<<" - wyswietl info o galerii\n";
	color(2);
	cout<<"k";
	color(0);
	cout<<" - koniec\n";
}

void menu_glowne() {
clear_screen();
char nawigacja;
bool wybrano_poprawny_klawisz = 0;
bool exit = 0;
	do {
		nawigacja = _getch(); // pobiera znak tak dlugo az zostana wcisniete strzalki gora/dol lub enter
		switch(nawigacja) {
			case '1':
				db.wczytajKatalogZPliku(1, 1);//1-wyswietl komunikat z pytaniem czy zaladowac baze, 1-uruchom funkcje czyszczaca baze przed zaladowaniem rekordow z pliku
				wybrano_poprawny_klawisz = 1;
				break;
			case '2':
				db.zapiszKatalogDoPliku();
				wybrano_poprawny_klawisz = 1;
				break;
			case '3':
				cout<<"Czy aby na pewno chcesz skasowac baze danych? Wybierz dzialanie\n"
					<<"1 - Skasuj baze danych zawarta w pamieci programu\n"
					<<"2 - Skasuj tylko baze danych w pliku txt\n"
					<<"3 - Anuluj\n";
				char nawigacja_kasuj;
				do {
					nawigacja_kasuj = _getch();
				} while(nawigacja_kasuj != '1' && nawigacja_kasuj != '2' && nawigacja_kasuj != '3');
				if(nawigacja_kasuj == '1') {
					db.skasujKatalog(1);//wyswietlamy komunikaty o udanym skasowaniu oraz zapytanie czy zapisac rowniez zmiany w bazie txt
				} else if(nawigacja_kasuj == '2') {
					db.wyczyscKatalogWPliku();
					cout<<"Baza danych w pliku txt zostala wyczyszczona!";
				} else {
					cout<<"Anulowano kasowanie bazy...";
				}
				wybrano_poprawny_klawisz = 1;
				break;
			case '4':
				cout<<"1 - Dodaj element na poczatek listy\n"
					<<"2 - Dodaj element na koniec listy\n"
					<<"3 - Anuluj\n";
				char nawigacja_dodaj;
				do {
					nawigacja_dodaj = _getch();
				} while(nawigacja_dodaj != '1' && nawigacja_dodaj != '2' && nawigacja_dodaj != '3');
				if(nawigacja_dodaj == '1') {
					db.dodajNaPoczatek();
				} else if(nawigacja_dodaj == '2') {
					db.dodajNaKoniec();
				} else cout<<"Anulowano...\n";
				wybrano_poprawny_klawisz = 1;
				break;
			case '5':
				db.usunEksponat();
				wybrano_poprawny_klawisz = 1;
				break;
			/*case '6':
				db.edytujEksponat();
				wybrano_poprawny_klawisz = 1;
				break;*/
			case '7':
				db.wypiszKatalog();
				wybrano_poprawny_klawisz = 1;
				break;
			case '8':
				db.sortujEksponaty();
				wybrano_poprawny_klawisz = 1;
				break;
			/*case '9':
				db.WyszukajRekordy();
				wybrano_poprawny_klawisz = 1;
				break;*/
			case 'k':
				cout<<"UWAGA!! Zanim wyjdziesz z programu\n ";
				db.zapiszKatalogDoPliku(1,0);//0 oznaczacza ze nie pytamy sie czy zaladowac do pamieci programu zaktualizowana baze
				wybrano_poprawny_klawisz = 1;
				exit = 1;
				break;
		}
	} while(wybrano_poprawny_klawisz==0);
	if(exit!=1) {
		cout<<"\n\n";
		system("pause");
		menu_glowne();
	}
}
