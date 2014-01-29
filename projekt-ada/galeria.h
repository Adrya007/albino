#pragma once

#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class Eksponat {
private:
	bool czy_wystawiony;
protected:
	static int fromString(string s);
	void wczytajDaneEksponatuZPliku(istream& f);
public:
	Eksponat* next;
	Eksponat* prev;

	int id;
	string tytul_dziela;
	string imie_autora;
	string nazwisko_autora;
	string narodowosc_autora;
	int data_wykonania;
	int cena_w_pln;

	//----metody publiczne----
	Eksponat();
	Eksponat(int id, string tytul_dziela, string imie_autora, string nazwisko_autora, string narodowosc_autora, int data_wykonania, int cena_w_pln);
	virtual ~Eksponat();

	void dodaj(Eksponat* &, Eksponat* &, int);
	virtual void zapiszNaStrumien(ostream& f, bool tytuluj) const;
	virtual void wczytajStrumien(istream& f);
	virtual string czymJestes() const;
};

class KatalogGalerii {
private:
		Eksponat* lista_poczatek; //wskaznik na pierwszy element listy
		Eksponat* lista_koniec;
		int autoIncrement;
		int liczbaEksponatow;
		const char* URL_Baza; //adres pliku z zapisana baza
		const char* URL_AutoIncrement; //adres pliku przechowujacego informacje o ostatnio dodanym ID
		const char* URL_LogWyszukiwanie;
		string miejsce_galerii_;
		bool czy_bilety_;
		bool czy_przewodnik_;
		string IntToString(int);

public:
		void dodajEksponatyBezposrednio(ifstream& f);
		KatalogGalerii(string miejsce_galerii, bool czy_bilety, bool czy_przewodnik);
		void init(string miejsce_galerii, bool czy_bilety, bool czy_przewodnik);
		~KatalogGalerii();
		void czymJestes();
		void saveAutoIncrement();
		void wypiszKatalog();
		void wypiszInfoOGalerii();
		void skasujKatalog(int WyswietlKomunikat=0);
		void usunEksponat(int WlaczKomunikaty=1, int ID_delete=0);
		void wyczyscKatalogWPliku();
		void wczytajKatalogZPliku(bool, bool);
		void zapiszKatalogDoPliku(int wyswietlKomunikat=1, int wyswietlKomunikat2=1);
		void returnAutoIncrementAndLiczbaRekordow();
		void dodaj(bool dodajNaKoncu);
		void dodajNaPoczatek();
		void dodajNaKoniec();
		void edytujEksponat();
		void countLiczbaEksponatow();
		void QuickSort(Eksponat [], int, int, string, int);
		void sortujEksponaty();
};

class Obraz: public virtual Eksponat{
public:
		string uzyta_technika;
		string uzyta_farba;
		string rodzaj_plotna;
		int wysokosc_obrazu;
		int szerokosc_obrazu;

		//----metody publiczne----
		Obraz();
		~Obraz();
		virtual void zapiszNaStrumien(ostream& f, bool tytuluj) const;
		virtual void wczytajStrumien(istream& f);
		string czymJestes() const;

};

class Fotografia: public virtual Eksponat{
public:
		string typ_fotografii;
		string uzyty_aparat;
		string miejsce_wykonania;
		int wysokosc_fotografii;
		int szerokosc_fotografii;

		//----metody publiczne----
		Fotografia();
		~Fotografia();
		virtual void zapiszNaStrumien(ostream& f, bool tytuluj) const;
		virtual void wczytajStrumien(istream& f);
		string czymJestes() const;
};

class Rzezba: public virtual Eksponat{
public:
		string rodzaj_rzezby;
		string material;
		string miejsce_wykonania;
		int wysokosc_rzezby;
		int glebokosc_rzezby;

		//----metody publiczne----
		Rzezba();
		~Rzezba();
		virtual void zapiszNaStrumien(ostream& f, bool tytuluj) const;
		virtual void wczytajStrumien(istream& f);
		string czymJestes() const;
};
