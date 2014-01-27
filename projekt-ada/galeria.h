#include <string>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <list>

#ifndef GALERIA_H
#define GALERIA_H

#include <ostream>
using namespace std;

class Eksponat{
private:
    bool czy_wystawiony;

public:
    Eksponat* next;
    Eksponat* prev;
	string tytul_dziela;
	int data_wykonania;
	string nazwisko_autora;
	string imie_autora;
	string narodowosc_autora;
	float cena_w_pln;
	int id;


	//----metody publiczne----
	Eksponat();  //konstruktor
	Eksponat(int tytul_dziela, int data_wykonania, string nazwisko_autora, string imie_autora, string narodowosc_autora, float cena_w_pln, int id);
	~Eksponat(); //destruktor

//    void wypiszEksponat();



    void dodaj(Eksponat* &, Eksponat* &, int);
    virtual string czymJestes();

};

class KatalogGalerii{
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

public:

    KatalogGalerii();
    void dodajEksponatBezposrednio(Eksponat* &, Eksponat* &, string, string, string, string, string, string, string);
    KatalogGalerii(string miejsce_galerii, bool czy_bilety, bool czy_przewodnik);
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
    void dodaj(Eksponat* &, Eksponat* &, int);
    void dodajNaPoczatek();
    void dodajNaKoniec();
    void edytujEksponat();
    void countLiczbaEksponatow();
    void QuickSort(Eksponat [], int, int, string, int);
    void sortujEksponaty();
};

class Obraz: public virtual Eksponat{
public:
    string rodzaj_plotna;
    string uzyta_farba;
    float wysokosc_obrazu;
    float szerokosc_obrazu;
    string uzyta_technika;

    //----metody publiczne----
    Obraz();
    ~Obraz();
    string czymJestes();
};

class Fotografia: public virtual Eksponat{
public:
    string typ_fotografii;
    string uzyty_aparat;
    float wysokosc_fotografii;
    float szerokosc_fotografii;
    string miejsce_wykonania;

    //----metody publiczne----
    Fotografia();
    ~Fotografia();
    string czymJestes();
};

class Rzezba: public virtual Eksponat{
public:
    string material;
    string rodzaj_rzezby;
    float wysokosc_rzezby;
    float glebokosc_rzezby;
    string miejsce_wykonania;

    //----metody publiczne----
    Rzezba();
    ~Rzezba();
    string czymJestes();
};
#endif
