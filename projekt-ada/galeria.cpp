#include <conio.h>
#include <time.h>
#include <iostream>
#include <sstream> // do konwersji

#include "galeria.h"


using namespace std;

KatalogGalerii::KatalogGalerii(string miejsce_galerii, bool czy_bilety, bool czy_przewodnik)
{
	init(miejsce_galerii, czy_bilety, czy_przewodnik);
}

void KatalogGalerii::init(string miejsce_galerii, bool czy_bilety, bool czy_przewodnik) {
		//definicja zmienych prywatnych
		this->URL_Baza = "baza_log/KatalogGaleryjki.txt";
		this->URL_AutoIncrement = "baza_log/AutoIncrement.txt";
		this->URL_LogWyszukiwanie = "baza_log/log_wyszukiwanie.txt";
		//inicjalizacja wskaznikow prywatych
		this->lista_poczatek = nullptr;
		this->lista_koniec = nullptr;
		this->liczbaEksponatow = 0;
		// ladujemy informacje o numerze ostatniego ID z pliku konfiguracyjnego
		// przed odczytem plik jest otwierany
		fstream plik;
		plik.open(this->URL_AutoIncrement, ios::app);
		plik.close();
		//odczyt
		ifstream ifile(this->URL_AutoIncrement);
		string plik_au;
		while (!ifile.eof()) {
			getline(ifile,plik_au);
			if (plik_au.length() == 0) {
				this->autoIncrement = 0;
			} else {
				this->autoIncrement = atoi(plik_au.c_str()); //przypisanie do zmiennej prywatnej informacji o ostatnim ID
			}
		}
		ifile.close();
		//------------
		miejsce_galerii_ = miejsce_galerii;
		czy_bilety_ = czy_bilety;
		czy_przewodnik_ = czy_przewodnik;
}

//-------------------------------------------
void KatalogGalerii::wypiszInfoOGalerii()
{
		string a, b;
		if (czy_bilety_=1)
			a = "tak";
		else a="nie";
		if (czy_przewodnik_=1)
			b="tak";
		else b="nie";
		cout<<"\nGaleria ADA znajduje sie w miescie: "<<miejsce_galerii_<<"\nCzy sa jeszcze bilety: "<<a<<"\nCzy jest tam przewodnik: "<<b<<endl;
}

//-------------------------------------------
void KatalogGalerii::wypiszKatalog()
{
		if (lista_poczatek == nullptr) {
				cout<<"\nLista jest pusta!";
				return;
		}
		Eksponat* temp = lista_poczatek;
		while(temp != nullptr)
		{
			temp->zapiszNaStrumien(cout, true);
			cout << "\n==========================================\n\n";
			temp = temp->next;
		}
}
//------------------------------------------

string Eksponat::getStringFromConsole(string message) {
	string line;
	do {
		cout << endl << message << endl;
		getline(cin, line);
	} while (line == "");
	return line;
}

int Eksponat::getIntFromConsole(string message) {
	string line;
	stringstream ss;
	int num = 0;
	do {
		ss.str("");
		ss.clear();
		cout << endl << message << endl;
		getline(cin, line);
		ss << line;
		ss >> num;
	} while (ss.fail());
	return num;
}

void KatalogGalerii::dodaj(bool dodajNaKoncu)
{
	Eksponat* wn = nullptr;
	string line;
	bool ok;
	do {
	cout << "\nPodaj typ eksponatu (eksponat/obraz/fotografia/rzezba):\n";
		ok = true;
		getline(cin, line);
		if (line == "eksponat")
			wn = new Eksponat();
		else if (line == "obraz")
			wn = new Obraz();
		else if (line == "fotografia")
			wn = new Fotografia();
		else if (line == "rzezba")
			wn = new Rzezba();
		else
			ok = false;
	} while (!ok);
	wn->id = ++autoIncrement;
	++liczbaEksponatow;
	// magia dziedziczenia i funkcji wirtualnych
	wn->dodaj();
	if (dodajNaKoncu) {
		wn->prev = lista_koniec; //obecny koniec listy
		wn->next = nullptr; //nastepny element jest jeszcze nullptr - wlasnie jest dodawany ostatni element
		if(lista_koniec != nullptr) {
				lista_koniec->next = wn;
		} else {
				lista_poczatek = wn;
		}
		lista_koniec = wn; //nowy element koncowy - wn (Wskaznik Nowy na element ktory wlasnie dodano)
		cout<<"\nDodano na koniec listy!";
	} else {
		wn->prev = nullptr;
		wn->next = lista_poczatek;
		if(lista_poczatek != nullptr) {
				lista_poczatek->prev = wn;
		} else {
				lista_koniec = wn;
		}
		lista_poczatek = wn; //nowy poczatek listy
		cout<<"\nDodano na poczatek listy!";
	}
}

//-------------------------------------
void KatalogGalerii::dodajNaPoczatek()
{
	KatalogGalerii::dodaj(false);
}

//-------------------------------------
void KatalogGalerii::dodajNaKoniec()
{
	KatalogGalerii::dodaj(true);
}

//---------------------------------------
KatalogGalerii::~KatalogGalerii()
{
		saveAutoIncrement();
}

//--------------------------------------
void KatalogGalerii::saveAutoIncrement()
{
		fstream plik;
		plik.open(this->URL_AutoIncrement, ios::out);
		plik<<this->autoIncrement;
		plik.close();
}
//----------------------------------------
void KatalogGalerii::returnAutoIncrementAndLiczbaRekordow()
{
		countLiczbaEksponatow();//zliczamy liczbe rekordow przed wyswietleniem ich
		cout<<"\nID ostatnio dodanego eksponatu: "<<this->autoIncrement<<" Eksponatow w pamieci: "<<this->liczbaEksponatow<<"\n";
}
//-----------------------------------------
void KatalogGalerii::countLiczbaEksponatow()
{
		//zliczamy liczbe rekordow
		this->liczbaEksponatow = 0;
		if(this->lista_poczatek != nullptr) {
				Eksponat* temp = this->lista_poczatek;
				while(temp != nullptr)
				{
						this->liczbaEksponatow++;
						temp = temp->next;
				}
		}
}

//-----------------------------------------

void KatalogGalerii::usunEksponat(int wlaczKomunikaty, int ID_delete)
{
		if (wlaczKomunikaty) wypiszKatalog();
		if (this->lista_poczatek == nullptr && this->lista_koniec == nullptr) {
				if (wlaczKomunikaty) cout << " Nie ma co usuwac.\n";
				return;
		}

		int id;
		if(wlaczKomunikaty) {
				cout<<"\nPodaj ID rekordu ktory usunac: ";
				string get;
				getline(cin,get);
				id = atoi(get.c_str()); //konwersja string -> int
		} else {
				id = ID_delete; //usuwamy id ktory przeslalismy jako argument funkcji
		}
		Eksponat* temp = this->lista_poczatek;
		int znaleziono = 0; //nie znaleziono Eksponatu do usuniecia
		Eksponat* temp_usun;
		while(temp != nullptr)
		{
				if(temp->id != id) {
						temp = temp->next;
						continue;
				}
				Eksponat* temp_prev = temp->prev;
				Eksponat* temp_next = temp->next;
				if(temp_prev != nullptr) {
						temp_prev->next = temp->next;
						if(temp->next == nullptr) {
								this->lista_koniec = temp_prev;
						}
				}
				if(temp_next != nullptr) {
						temp_next->prev = temp->prev;
						if(temp->prev == nullptr) {
								this->lista_poczatek = temp_next;
						}
				}
				temp_usun = temp;
				if(wlaczKomunikaty) cout<<"\nUsunieto Eksponat o ID: "<<temp_usun->id;
				delete temp_usun;

				this->liczbaEksponatow--;
				if(this->liczbaEksponatow == 0)
				{
						this->lista_poczatek = nullptr;
						this->lista_koniec = nullptr;
				}
				znaleziono = 1;
				break;
		}
		if(znaleziono == 0 && wlaczKomunikaty) {
				cout<<"\nNie znaleziono rekordu do usuniecia.";
		}
}

//--------------------------------------

void KatalogGalerii::zapiszKatalogDoPliku (int wyswietlKomunikat, int wyswietlKomunikat2)
{
		Eksponat* temp = this->lista_poczatek;
		if(temp == nullptr) {
				if(wyswietlKomunikat) {
				cout<<"\nBrak rekordow w bazie ktore mozna by zapisac.\n"
						<<"Czy chcesz wyczyscic baze danych w pliku txt?\n";
				}
				cout<<"1 - Tak, wyczysc baze danych w pliku txt\n"
						<<"2 - Nie\n";
				char nawigacja;
				do {
						nawigacja = _getch();
				} while(nawigacja != '1' && nawigacja != '2');
				if(nawigacja == '1') {
						wyczyscKatalogWPliku();
						cout<<"Baza danych w pliku txt zostala wyczyszczona.\n";
				} else {
						cout<<"Baza danych w pliku txt pozostala nienaruszona.\n";
				}
		} else {
				cout<<"\nCzy chcesz zapisac liste rekordow do bazy w pliku txt?\n"
						<<"1 - Zapisz baze do pliku (obecne dane w pliku zostana nadpisane)\n"
						<<"2 - Zapisz baze do pliku poprzez dopisanie nowych rekordow\n"
						<<"3 - Nie zapisuj bazy\n";
				char nawigacja;
				do {
						nawigacja = _getch();
				} while(nawigacja != '1' && nawigacja != '2' && nawigacja != '3');
				ofstream plik;
				if(nawigacja == '1') {
						plik.open(this->URL_Baza, ios::out); //tryb nadpisania pliku
				} else if(nawigacja == '2') {
						plik.open(this->URL_Baza, ios::app); //tryb dopisywania do pliku
				} else {
						cout<<"\nBaza nie zostanie zapisana!";
				}
				//dane w pliku zapisane

				if(nawigacja == '1' || nawigacja == '2')
				{
						cout<<"\nTrwa zapisywanie...n";
						if(nawigacja == '2') {
								cout<<"\nWybrales opcje dopisania rekordow do bazy.\n"
										<<"Aby uniknac dublowania sie numerow ID, rekordy z pamieci programu\n"
										<<"otrzymaja nowe ID, ktore bedzie wieksze od ilosci rekordow w bazie txt\n";
						}
						int tempID;
						while(temp != nullptr)
						{
								/* jesli rekordy sa dopisywane do bazy, zmieniamy im ID na wieksze
								niz te ktore maja rekordy w pliku txt - aby uniknac sytuacji dublowania ID
								w bazie.
								*/
								if(nawigacja == '2') {
										tempID = ++autoIncrement;
										cout<<"Zapisano eksponat o ID = "<<temp->id<<" w bazie txt i w pamieci programu, nowe ID: "<<tempID<<"\n";
										temp->id = tempID;
								} else {
										tempID = temp->id;
										cout<<"Zapisano eksponat o ID = "<<temp->id<<"\n";
								}
								//zapis do pliku
								temp->zapiszNaStrumien(plik, false);
								temp = temp->next;
						}
						plik.close();
						saveAutoIncrement(); //zapis ID ostatnio dodanego rekordu
						if(nawigacja == '1') {
								cout<<"Pomyslnie nadpisano baze danych nowymi rekordami.\n";
						} else { //2
								cout<<"Pomyslnie dopisano rekordy do bazy danych.\n";

								if(wyswietlKomunikat2) {
										cout<<"Achtung! Teraz powinienes zsynchronizowac zawartosc pamieci programu z baza txt.\n"
												<<"Jesli chcesz to zrobic zaladuj baze z pliku:\n";
										wczytajKatalogZPliku(1, 1); //1- komunikat czy wczytac baze, 1- baze kasowana z pamieci programu po czym zaladowana z pliku
								}
						}
				}
		}
}
//--------------------------------------

void KatalogGalerii::wyczyscKatalogWPliku()
{
	fstream plik;
	plik.open(this->URL_Baza, ios::out); //tryb nadpisania pliku
	plik<<"";
	plik.close();
	saveAutoIncrement(); //zapis ID ostatnio dodanego rekordu
}


//---------------------------------------
void KatalogGalerii::skasujKatalog(int wyswietlKomunikat)
{
	if(this->lista_poczatek != nullptr)//czy lista nie jest pusta? jesli jest pusta -> nie tworz wskaznika
	{
		Eksponat* temp = this->lista_poczatek;
		int ID_delete; //id do skasowania
		while(temp != nullptr)
		{
			ID_delete = temp->id; //ID przypisane do zmiennej pomocniczej - przed usunieciem rekordu trzeba odczytac adres kolejnego Eksponatu
			temp = temp->next;
			usunEksponat(0, ID_delete); //rekord o danym ID usunieto
		}
		if(wyswietlKomunikat) {
			cout<<"Usunieto wszystkie rekordy z pamieci programu.\n";
		}
	} else if(wyswietlKomunikat) {
		cout<<"Baza danych w pamieci programu jest pusta. Nie ma co kasowac.\n";
	}
	if(wyswietlKomunikat) {
		cout<<"Czy chcesz aby wyczyscic rowniez plik txt bazy danych?\n";
		zapiszKatalogDoPliku(0);//brak wyswietlenia komunikatu z pytaniem o skasowanie baze txt
	}
}

//------------------------------------------------

void KatalogGalerii::wczytajKatalogZPliku(bool komunikat, bool czy_kasowac)
{
	bool zaladuj_baze;
	if (komunikat) //wyswietl komunikat z pytaniem czy zaladowac baze
	{
		cout<<"Czy chcesz wczytac baze danych z pliku do pamieci programu?\n"
				<<"(Baza zawarta w pamieci programu zostanie nadpisana baza z pliku)\n"
				<<"1 - Wczytaj baze z pliku\n"
				<<"2 - Anuluj.\n";
		char nawigacja_dodaj;
		do {
				nawigacja_dodaj = _getch();
		} while(nawigacja_dodaj != '1' && nawigacja_dodaj != '2');
		if(nawigacja_dodaj == '1') {
				zaladuj_baze = true;
				cout << "Wczytano.\n";
		} else {
				zaladuj_baze = false;
				cout << "Anulowano.\n";
		}
	} else { //brak komunikatu, baza ladowana automatycznie
			zaladuj_baze = true;
	}
	if(!zaladuj_baze)
			return;
	//skasowanie obecnej bazy w pamieci programu
	//jesli baza ladowana przy pierwszym uruchomieniu programu -> nie uruchamiana jest funkcji kasujaca
	if(czy_kasowac) { //true = uruchom funkcje kasujaca baze
			skasujKatalog();
	}
	// odczyt bazy
	ifstream ifile(this->URL_Baza);
	dodajEksponatyBezposrednio(ifile);
	ifile.close();
}

//-------------------------------------------
void KatalogGalerii::dodajEksponatyBezposrednio(ifstream& file)
{
	Eksponat* wn = nullptr;
	string typ;
	while (!file.eof()) {
		typ = "";
		while (!file.eof() && typ == "")
			getline(file, typ);
		if (file.eof()) break;
		if (typ == "eksponat") {
			wn = new Eksponat();
		} else if (typ == "obraz") {
			wn = new Obraz();
		} else if (typ == "fotografia") {
			wn = new Fotografia();
		} else if (typ == "rzezba") {
			wn = new Rzezba();
		} else {
			//TODO nieznany identyfikator
			continue;
		}
		wn->wczytajStrumien(file);
		// wstawianie do listy
		wn->prev = wn->next = nullptr;
		if (lista_poczatek == nullptr && lista_koniec == nullptr)
			lista_poczatek = lista_koniec = wn;
		else {
			wn->prev = lista_koniec;
			lista_koniec->next = wn;
		}
		cout << "\n>Dodano rekord:\n";
		wn->zapiszNaStrumien(cout, true);
		this->liczbaEksponatow++;
	}
}

//-------------------------------------------
int Eksponat::fromString(string s) {
	int result = 0;
	stringstream ss(s);
	ss >> result;
	return result;
}

//------------------ konstruktory
Eksponat::Eksponat() {}

Obraz::Obraz() {}

Fotografia::Fotografia() {}

Rzezba::Rzezba() {}

//--------------------------------------
Eksponat::Eksponat(int id_, string tytul_dziela_, string imie_autora_, string nazwisko_autora_, string narodowosc_autora_, int data_wykonania_, int cena_w_pln_)
{
		id = id_;
		tytul_dziela = tytul_dziela_;
		imie_autora = imie_autora_;
		nazwisko_autora = nazwisko_autora_;
		narodowosc_autora = narodowosc_autora_;
		data_wykonania = data_wykonania_;
		cena_w_pln = cena_w_pln_;
}

//------------------ destruktory
Eksponat::~Eksponat(){}

Obraz::~Obraz() {}

Fotografia::~Fotografia() {}

Rzezba::~Rzezba() {}

//------------------ dodawanie z konsoli

void Eksponat::dodajPodstawowe() {
	tytul_dziela = Eksponat::getStringFromConsole(
		"Podaj tytul dziela:");
	imie_autora = Eksponat::getStringFromConsole(
		"Podaj imie autora:");
	nazwisko_autora = Eksponat::getStringFromConsole(
		"Podaj nazwisko autora:");
	narodowosc_autora = Eksponat::getStringFromConsole(
		"Podaj narodowosc autora:");
	data_wykonania = Eksponat::getIntFromConsole(
		"Podaj date wykonania dziela:");
	cena_w_pln = Eksponat::getIntFromConsole(
		"Podaj cene w pln dziela:");
}

void Eksponat::dodaj() {
	dodajPodstawowe();
}

void Obraz::dodaj() {
	dodajPodstawowe();
	uzyta_technika = Eksponat::getStringFromConsole(
		"Podaj :");
	uzyta_farba = Eksponat::getStringFromConsole(
		"Podaj :");
	rodzaj_plotna = Eksponat::getStringFromConsole(
		"Podaj :");
	wysokosc_obrazu = Eksponat::getIntFromConsole(
		"Podaj :");
	szerokosc_obrazu = Eksponat::getIntFromConsole(
		"Podaj :");
}

void Fotografia::dodaj() {
	dodajPodstawowe();
	typ_fotografii = Eksponat::getStringFromConsole(
		"Podaj :");
	uzyty_aparat = Eksponat::getStringFromConsole(
		"Podaj :");
	miejsce_wykonania = Eksponat::getStringFromConsole(
		"Podaj :");
	wysokosc_fotografii = Eksponat::getIntFromConsole(
		"Podaj :");
	szerokosc_fotografii = Eksponat::getIntFromConsole(
		"Podaj :");
}

void Rzezba::dodaj() {
	dodajPodstawowe();
	rodzaj_rzezby = Eksponat::getStringFromConsole(
		"Podaj :");
	material = Eksponat::getStringFromConsole(
		"Podaj :");
	miejsce_wykonania = Eksponat::getStringFromConsole(
		"Podaj :");
	wysokosc_rzezby = Eksponat::getIntFromConsole(
		"Podaj :");
	glebokosc_rzezby = Eksponat::getIntFromConsole(
		"Podaj :");
}

//------------------ ZAPIS <<<<<<<<<<<

void Eksponat::zapiszPodstawowe(ostream& s, bool tytuluj) const {
	s << (tytuluj ? "Eksponat to:       " : "") << czymJestes() << endl;
	s << (tytuluj ? "ID eksponatu:      " : "") << id << endl;
	s << (tytuluj ? "Imie autora:       " : "") << imie_autora << endl;
	s << (tytuluj ? "Nazwisko autora:   " : "") << nazwisko_autora << endl;
	s << (tytuluj ? "Tytul dziela:      " : "") << tytul_dziela << endl;
	s << (tytuluj ? "Narodowosc autora: " : "") << narodowosc_autora << endl;
	s << (tytuluj ? "Data wykonania:    " : "") << data_wykonania << endl;
	s << (tytuluj ? "Cena w PLN:        " : "") << cena_w_pln << endl;
}

void Eksponat::zapiszNaStrumien(ostream& s, bool tytuluj) const {
	zapiszPodstawowe(s, tytuluj);
}

void Obraz::zapiszNaStrumien(ostream& s, bool tytuluj) const {
	zapiszPodstawowe(s, tytuluj);
	s << (tytuluj ? "Uzyta technika:    " : "") << uzyta_technika<< endl;
	s << (tytuluj ? "Uzyta farba:       " : "") << uzyta_farba << endl;
	s << (tytuluj ? "Rodzaj plotna:     " : "") << rodzaj_plotna << endl;
	s << (tytuluj ? "Wysokosc obrazu:   " : "") << wysokosc_obrazu << endl;
	s << (tytuluj ? "Szerokosc obrazu:  " : "") << szerokosc_obrazu << endl;
}

void Fotografia::zapiszNaStrumien(ostream& s, bool tytuluj) const {
	zapiszPodstawowe(s, tytuluj);
	s << (tytuluj ? "Typ fotografii:    " : "") << typ_fotografii << endl;
	s << (tytuluj ? "Uzyty aparat:      " : "") << uzyty_aparat << endl;
	s << (tytuluj ? "Miejsce wykonania: " : "") << miejsce_wykonania << endl;
	s << (tytuluj ? "Wysokosc:          " : "") << wysokosc_fotografii << endl;
	s << (tytuluj ? "Szerokosc:         " : "") << szerokosc_fotografii << endl;
}

void Rzezba::zapiszNaStrumien(ostream& s, bool tytuluj) const {
	zapiszPodstawowe(s, tytuluj);
	s << (tytuluj ? "Rodzaj rzezby:     " : "") << rodzaj_rzezby << endl;
	s << (tytuluj ? "Material:          " : "") << material << endl;
	s << (tytuluj ? "Miejsce wykonania: " : "") << miejsce_wykonania << endl;
	s << (tytuluj ? "Wysokosc:          " : "") << wysokosc_rzezby << endl;
	s << (tytuluj ? "Glebokosc:         " : "") << glebokosc_rzezby << endl;
}

//------------------ ODCZYT >>>>>>>>>>>

void Eksponat::wczytajDaneEksponatuZPliku(istream& f) {
	string wiersz;
	int linii = 1; //liczba linii
	while (linii <= 7) {
		getline(f, wiersz);
		if (wiersz == "")
			continue;
		switch (linii) {
		case 1 : id = fromString(wiersz); ++linii; break;
		case 2 : tytul_dziela = wiersz; ++linii; break;
		case 3 : imie_autora = wiersz; ++linii; break;
		case 4 : nazwisko_autora = wiersz; ++linii; break;
		case 5 : narodowosc_autora = wiersz; ++linii; break;
		case 6 : data_wykonania = fromString(wiersz); ++linii; break;
		case 7 : cena_w_pln = fromString(wiersz); ++linii; break;
		default: continue; // TODO informacja -> pominieto linie z pliku
		}
	}
}

void Eksponat::wczytajStrumien(istream& f) {
	wczytajDaneEksponatuZPliku(f);
}

void Obraz::wczytajStrumien(istream& f) {
	wczytajDaneEksponatuZPliku(f);
	string wiersz;
	int linii = 1; //liczba linii
	while (linii <= 5) {
		getline(f, wiersz);
		if (wiersz == "")
			continue;
		switch (linii) {
		case 1 : uzyta_technika = wiersz; ++linii; break;
		case 2 : uzyta_farba = wiersz; ++linii; break;
		case 3 : rodzaj_plotna = wiersz; ++linii; break;
		case 4 : wysokosc_obrazu = fromString(wiersz); ++linii; break;
		case 5 : szerokosc_obrazu = fromString(wiersz); ++linii; break;
		default: continue; // TODO informacja -> pominieto linie z pliku
		}
	}
}

void Fotografia::wczytajStrumien(istream& f) {
	wczytajDaneEksponatuZPliku(f);
	string wiersz;
	int linii = 1; //liczba linii
	while (linii <= 5) {
		getline(f, wiersz);
		if (wiersz == "")
			continue;
		switch (linii) {
		case 1 : typ_fotografii = wiersz; ++linii; break;
		case 2 : uzyty_aparat = wiersz; ++linii; break;
		case 3 : miejsce_wykonania = wiersz; ++linii; break;
		case 4 : wysokosc_fotografii = fromString(wiersz); ++linii; break;
		case 5 : szerokosc_fotografii = fromString(wiersz); ++linii; break;
		default: continue; // TODO informacja -> pominieto linie z pliku
		}
	}
}

void Rzezba::wczytajStrumien(istream& f) {
	wczytajDaneEksponatuZPliku(f);
	string wiersz;
	int linii = 1; //liczba linii
	while (linii <= 5) {
		getline(f, wiersz);
		if (wiersz == "")
			continue;
		switch (linii) {
		case 1 : rodzaj_rzezby = wiersz; ++linii; break;
		case 2 : material = wiersz; ++linii; break;
		case 3 : miejsce_wykonania = wiersz; ++linii; break;
		case 4 : wysokosc_rzezby = fromString(wiersz); ++linii; break;
		case 5 : glebokosc_rzezby = fromString(wiersz); ++linii; break;
		default: continue; // TODO informacja -> pominieto linie z pliku
		}
	}
}

//-------------------
string Eksponat::czymJestes() const
{
		return "eksponat";
}

string Obraz::czymJestes() const
{
		return "obraz";
}

string Fotografia::czymJestes() const
{
		return "fotografia";
}

string Rzezba::czymJestes() const
{
		return "rzezba";
}
//-------------------


void KatalogGalerii::sortujEksponaty()
{
	countLiczbaEksponatow(); //liczy liczbe eksponatow
	if (liczbaEksponatow == 0)
			return;
	cout<<"Wybierz kryterium wedlug ktorego posortowac baze:\n"
			<<"1 - ID\n"
			<<"2 - Nazwisko autora\n"
			<<"3 - Cena dziela w polskich zlotych\n";

	char nawigacja;
	do {
			nawigacja = _getch();
	} while(nawigacja != '1' && nawigacja != '2' && nawigacja != '3');
	Eksponat* tab = new Eksponat[liczbaEksponatow];
	Eksponat* temp = this->lista_poczatek;
	int index=0; //tablica atrybutow
	while(temp != nullptr)
	{
			tab[index] = *temp;
			temp = temp->next;
			index++;
	}
	if(nawigacja == '1') {
			cout<<"Wybrano ID jako kryterium sortowania.\n";
			QuickSort(tab, 0, liczbaEksponatow-1, "id", 1);
	} else if(nawigacja == '2') {
			cout<<"Wybrano nazwisko autora jako kryterium sortowania.\n";
			QuickSort(tab, 0, liczbaEksponatow-1, "nazwisko autora", 1);
	} else if(nawigacja == '3') {
			cout<<"Wybrano cene jako kryterium sortowania.\n";
			QuickSort(tab, 0, liczbaEksponatow-1, "cena", 1);
	}
	//posortowane wyniki:
	for(int i=0; i<liczbaEksponatow; i++)
	{
		cout<<"ID:                      "<<tab[i].id<<"\n";
		cout<<"Tytul dziela:            "<<tab[i].tytul_dziela<<"\n";
		cout<<"Imie:                    "<<tab[i].imie_autora<<"\n";
		cout<<"Nazwisko autora:         "<<tab[i].nazwisko_autora<<"\n";
		cout<<"Narodowosc autora:       "<<tab[i].narodowosc_autora<<"\n";
		cout<<"Data wykonanania:        "<<tab[i].data_wykonania<<"\n";
		cout<<"Cena w PLN:              "<<tab[i].cena_w_pln<<"\n";
		cout<<"==========================================\n";
	}
}

//----------------------------------------------

void KatalogGalerii::QuickSort(Eksponat t[], int p, int k, string co_sortowac, int kolejnosc)
{
	static char typ_kolejnosci;
	if(kolejnosc) {//sposob prezentacji wynikow
		cout<<"Wybierz sposob wyswietlenia posortowanych danych:\n"
				<<"1 - ASC (rosnaco)\n"
				<<"2 - DESC(malejaco)\n";
		do {
				typ_kolejnosci = _getch();
		} while(typ_kolejnosci != '1' && typ_kolejnosci != '2');
	}
	int i, j, pivot;
	string pivot_s; //
	i = p;
	j = k;
	if(co_sortowac == "id") {
			pivot = t[p].id; //punkt podzialu
	} else if(co_sortowac == "cena") {
			pivot = t[p].cena_w_pln;
	} else if(co_sortowac == "nazwisko autora"){
					pivot_s = t[p].nazwisko_autora;
	}

	while(i < j)
	{
		if(co_sortowac == "id") {
			if(typ_kolejnosci=='1') {
					while(t[i].id<pivot) i++;
					while(t[j].id>pivot) j--;
			} else {
					while(t[i].id>pivot) i++;
					while(t[j].id<pivot) j--;
			}
		} else if(co_sortowac == "cena") {
			if(typ_kolejnosci=='1') {
					while(t[i].cena_w_pln<pivot) i++;
					while(t[j].cena_w_pln>pivot) j--;
			} else {
					while(t[i].cena_w_pln>pivot) i++;
					while(t[j].cena_w_pln<pivot) j--;
			}
		} else if(co_sortowac == "nazwisko autora") {
			if(typ_kolejnosci=='1') {
					while(t[i].nazwisko_autora<pivot_s) i++;
					while(t[j].nazwisko_autora>pivot_s) j--;
			} else {
					while(t[i].nazwisko_autora>pivot_s) i++;
					while(t[j].nazwisko_autora<pivot_s) j--;
			}
		}

		if(i <= j) {
			Eksponat wtemp;//zmienna pomocnicza
			wtemp = t[i];
			t[i] = t[j];
			t[j] = wtemp;
			i++;
			j--; 
		}
	}
	if(i < k) {
			QuickSort(t, i, k, co_sortowac, 0); //0 - brak pytania o typ sortowania
	}
	if(p < j) {
			QuickSort(t, p, j, co_sortowac, 0);
	}
}


//----------------------------

//konwersja int na string

string KatalogGalerii::IntToString(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}
