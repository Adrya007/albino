#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h> // do funkcji getch()

#include "galeria.h"

using namespace std;

//funkcje globalne:
void wyswietlajka();
bool wybierajka();

KatalogGalerii db("Warszawa", 1, 1); //stworzenie obiektu db katalogu galerii

//------------
int main( int argc, char* argv[] )
{
	/*
	 *	katalog eksponatow zostaje zaladowany przy starcie programu
	 *	false - brak komunikatu czy wczytac baze,
	 *	false - baza nie ulega skasowaniu
	 */
	system("COLOR 1e");
	db.wczytajKatalogZPliku(false, false);
	bool exit = false;
	while (!exit) {
		cout<<"\n\n	";
		system("pause");
		exit = wybierajka();
	}
	db.saveAutoIncrement(); //zapisanie wartosci ostatnio dodanego ID
	return 0;
}

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

/** zwraca true gdy koniec programu */
bool wybierajka() {
	wyswietlajka();
	char nawigacja;
	bool wybrano_poprawny_klawisz = false;
	bool exit = false;
	do {
		// pobiera znak tak dlugo
		// az zostana wcisniete strzalki gora/dol lub enter
		nawigacja = _getch();
		switch (nawigacja) {
		case '1':
				//1 - komunikat z pytaniem czy zaladowac baze,
				// 1 - uruchom funkcje czyszczaca baze przed zaladowaniem rekordow z pliku
				db.wczytajKatalogZPliku(1, 1);
				wybrano_poprawny_klawisz = true;
				break;
		case '2':
				db.zapiszKatalogDoPliku();
				wybrano_poprawny_klawisz = true;
				break;
		case '3':
				cout<<"Czy na pewno chcesz skasowac baze danych?\n"
					<<"1 - Skasuj baze danych w pamieci programu\n"
					<<"2 - Skasuj tylko baze danych w pliku txt\n"
					<<"3 - Anuluj\n";
				char nawigacja_kasuj;
				do {
					nawigacja_kasuj = _getch();
				} while (nawigacja_kasuj != '1'
						&& nawigacja_kasuj != '2'
						&& nawigacja_kasuj != '3');
				if(nawigacja_kasuj == '1') {
					db.skasujKatalog(1);//komunikat o udanym skasowaniu + zapytanie czy zapisac rowniez zmiany w bazie txt
				} else if (nawigacja_kasuj == '2') {
					db.wyczyscKatalogWPliku();
					cout<<"Baza danych w pliku txt zostala wyczyszczona.";
				} else
					cout<<"Anulowano kasowanie bazy.";
				wybrano_poprawny_klawisz = true;
				break;
		case '4':
				cout<<"1 - Dodaj eksponat na poczatek listy\n"
					<<"2 - Dodaj eksponat na koniec listy\n"
					<<"3 - Anuluj.\n";
				char nawigacja_dodaj;
				do {
					nawigacja_dodaj = _getch();
				} while (nawigacja_dodaj != '1'
						&& nawigacja_dodaj != '2'
						&& nawigacja_dodaj != '3');
				if(nawigacja_dodaj == '1') {
					db.dodajNaPoczatek();
				} else if(nawigacja_dodaj == '2') {
					db.dodajNaKoniec();
				} else
					cout << "Anulowano.\n";
				wybrano_poprawny_klawisz = true;
				break;
		case '5':
				db.usunEksponat();
				wybrano_poprawny_klawisz = true;
				break;
		case '6':
				cout<<"\nUsluga edytowania istniejacego eksponatu w trakcie realizacji...\n";
				/* db.edytujEksponat();*/
				wybrano_poprawny_klawisz = true;
				break;
		case '7':
				db.wypiszKatalog();
				wybrano_poprawny_klawisz = true;
				break;
		case '8':
				db.sortujEksponaty();
				wybrano_poprawny_klawisz = true;
				break;
		case '9':
				cout<<"\nUsluga wyszukiwania istniejacego eksponatu w trakcie realizacji...\n";
				/*db.WyszukajRekordy();*/
				wybrano_poprawny_klawisz = true;
				break;
		case 'i':
				db.wypiszInfoOGalerii();
				wybrano_poprawny_klawisz = true;
				break;
		case 'k':
				cout<<"\nZanim wyjdziesz z programu:\n ";
				db.zapiszKatalogDoPliku(true, false);//0 - brak pytania czy zaladowac do pamieci programu zaktualizowana baze
				wybrano_poprawny_klawisz = true;
				exit = true;
				break;
		}
	} while (!wybrano_poprawny_klawisz);
	return exit;
}
