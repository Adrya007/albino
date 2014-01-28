#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <time.h>
#include <sstream> // do konwersji
#include <cstdlib>

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
        this->lista_poczatek = NULL;
        this->lista_koniec = NULL;
        this->liczbaEksponatow = 0;
        // ladujemy informacje o numerze ostatniego ID z pliku konfiguracyjnego
        // przed odczytem plik jest otwierany
        fstream plik;
        plik.open(this->URL_AutoIncrement, ios::app);
        plik.close();
        //odczyt
        ifstream ifile(this->URL_AutoIncrement);
        string plik_au;
        while(!ifile.eof()) {
            getline(ifile,plik_au);
            if(plik_au.length() == 0) {
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
        if(czy_bilety_=1)
            a = "tak";
        else a="nie";
        if(czy_przewodnik_=1)
            b="tak";
        else b="nie";
        cout<<"\nGaleria ADA znajduje sie w miescie: "<<miejsce_galerii_<<"\nCzy sa jeszcze bilety: "<<a<<"\nCzy jest tam przewodnik: "<<b<<endl;
}
//-------------------------------------------
Eksponat::Eksponat(){}
Eksponat::~Eksponat(){}
//-------------------------------------------
void KatalogGalerii::wypiszKatalog()
{
        if(this->lista_poczatek == NULL) {
                cout<<"\nLista jest pusta!";
                return;
        }
        Eksponat* temp = this->lista_poczatek;
        while(temp != NULL)
        {
                    cout<<"ID:                      "<<temp->id<<"\n"
                        <<"Tytul dziela:            "<<temp->tytul_dziela<<"\n"
                        <<"Imie autora:             "<<temp->imie_autora<<"\n"
                        <<"Nazwisko autora:         "<<temp->nazwisko_autora<<"\n"
                        <<"Narodowosc autora:       "<<temp->narodowosc_autora<<"\n"
                        <<"Rok powstania dziela:    "<<temp->data_wykonania<<"\n"
                        <<"Cena:                    "<<temp->cena_w_pln<<"\n"

                        <<"==========================================\n";
                temp = temp->next;
        }
}
//------------------------------------------
// w_l - wskaznik 1wszego eksponatu na liscie

// w_k - wskaznik konca listy

// gdzie_dodac == 1 na koniec listy, gdzie_dodac == 0 na poczatek

void KatalogGalerii::dodaj(Eksponat* &w_l, Eksponat* &w_k, int gdzie_dodac)
{
        Eksponat* wn = new Eksponat;
        //++ wartosci zmiennych prywatnych
        this->autoIncrement++;
        this->liczbaEksponatow++;
        wn->id = this->autoIncrement;
        cout<<"\nPodaj imie autora: ";
        getline(cin,wn->imie_autora);
        while(wn->imie_autora == "") {
                cout<<"\nPodano pusty ciag znakow. Podaj imie: ";
                getline(cin,wn->imie_autora);
        }
        cout<<"\nPodaj nazwisko autora: ";
        getline(cin,wn->nazwisko_autora);
        while(wn->nazwisko_autora == "") {
                cout<<"\nPodano pusty ciag znakow. Podaj nazwisko: ";
                getline(cin,wn->nazwisko_autora);
        }
        cout<<"\nPodaj rok powstania dziela: ";
        string data_wykonania;
        int data_wykonania_int;
        getline(cin,data_wykonania); //do stringa rok wykonania
        data_wykonania_int = atoi(data_wykonania.c_str()); //konwersja stringa na int
        while(data_wykonania == "" || data_wykonania_int == 0) {
                if(data_wykonania=="") {//podano pusty ciag znakow
                        cout<<"\nPodano pusty rok. Podaj nowy rok wykonania dziela: ";
                } else { //podano ciag znakow ktory zostal zamieniony na liczbe 0
                        cout<<"\nPodano ciag znakow zamiast roku liczbowego. Podaj nowy rok: ";
                }
                getline(cin,data_wykonania);
                data_wykonania_int= atoi(data_wykonania.c_str());
        }
        wn->data_wykonania = data_wykonania_int;
        cout<<"\nPodaj narodowosc autora: ";
        getline(cin,wn->narodowosc_autora);
        while(wn->narodowosc_autora == "") {
                cout<<"\nPodano pusty ciag znakow. Podaj narodowosc: ";
                getline(cin,wn->narodowosc_autora);
        }
        cout<<"\nPodaj tytul dziela: ";
        getline(cin,wn->tytul_dziela);
        while(wn->tytul_dziela == "") {
                cout<<"\nPodano pusty ciag znakow. Podaj tytul: ";
                getline(cin,wn->tytul_dziela);
        }
        cout<<"\nPodaj cene dziela: ";
        string cena_w_pln;
        int cena_w_pln_int;
        getline(cin,cena_w_pln); //do stringa cena_w_pln
        cena_w_pln_int = atoi(cena_w_pln.c_str()); //konwersja string -> int
        while(cena_w_pln == "" || cena_w_pln_int== 0) {
                if(cena_w_pln=="") {//pusty ciag znakow zamiast ceny
                        cout<<"\nPodano pusta cene. Podaj nowa: ";
                } else { //podano ciag znakow ktory zostal zamieniony na liczbe 0
                        cout<<"\nPodano ciag znakow zamiast jednej liczby: ";
                }
                getline(cin,cena_w_pln);
                cena_w_pln_int= atoi(cena_w_pln.c_str());
        }
        if(gdzie_dodac == 1) { //1 - na koniec listy
                wn->prev = w_k; //obecny koniec listy
                wn->next = NULL; //nastepny element jest jeszcze NULL - wlasnie jest dodawany ostatni element
                if(w_k != NULL) {
                        w_k->next = wn;
                } else {
                        w_l = wn;
                }
                w_k = wn; //nowy element koncowy - wn (Wskaznik Nowy na element ktory wlasnie dodano)
                cout<<"\nDodano na koniec listy!";
        } else { //gdzie_dodac==0 to dodajemy na poczatek listy
                wn->prev = NULL;
                wn->next = w_l;
                if(w_l != NULL) {
                        w_l->prev = wn;
                } else {
                        w_k = wn;
                }
                w_l = wn; //nowy poczatek listy
                cout<<"\nDodano na poczatek listy!";
        }
}

//-------------------------------------------
void KatalogGalerii::dodajEksponatBezposrednio(Eksponat* &w_l, Eksponat* &w_k, string id, string t, string i, string n, string nar, string data_wykonania, string cena_w_pln)
{
        Eksponat* wn = new Eksponat;
        int id_int = atoi(id.c_str()); //konwersja string -> int
        wn->id = id_int;
        wn->tytul_dziela = t;
        wn->imie_autora = i;
        wn->nazwisko_autora = n;
        wn->narodowosc_autora = nar;
        int data_wykonania_int = atoi(data_wykonania.c_str()); //konwersja string -> int
        wn->data_wykonania=data_wykonania_int;
        int cena_w_pln_int = atoi(cena_w_pln.c_str());
        wn->cena_w_pln=cena_w_pln_int;
        //na koniec listy

        wn->prev = w_k; //poprzedni Eksponat przed tym ktory dodalismy to w_k (obecny koniec listy)
        wn->next = NULL; // nastepny Eksponat to NULL
        if(w_k != NULL) {
                w_k->next = wn;
        } else {
                w_l = wn;
        }
        w_k = wn; //nowy eksponat koncowy
        cout<<"Dodano rekord: "<<id<<", "<<t<<", "<<i<<", "<<n<<", "<<nar<<", "<<data_wykonania<<", "<<cena_w_pln<<"\n";
        this->liczbaEksponatow++;
}
//-------------------------------------
void KatalogGalerii::dodajNaPoczatek()
{
        KatalogGalerii::dodaj(this->lista_poczatek, this->lista_koniec, 0);
}

//-------------------------------------
void KatalogGalerii::dodajNaKoniec()
{
        KatalogGalerii::dodaj(this->lista_poczatek, this->lista_koniec, 1);
}

//--------------------------------------
Eksponat::Eksponat(int id_, string tytul_dziela_, string imie_autora_, string nazwisko_autora_, string narodowosc_autora_, int data_wykonania_, int cena_w_pln_)
{
        int id=id_;
        tytul_dziela=tytul_dziela;
        string imie_autora=imie_autora_;
        string nazwisko_autora=nazwisko_autora_;
        string narodowosc_autora=narodowosc_autora_;
        int data_wykonania=data_wykonania_;
        float cena_w_pln=cena_w_pln_;

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
        if(this->lista_poczatek != NULL) {
                Eksponat* temp = this->lista_poczatek;
                while(temp != NULL)
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
        if (this->lista_poczatek == NULL && this->lista_koniec == NULL) {
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
        while(temp != NULL)
        {
                if(temp->id != id) {
                        temp = temp->next;
                        continue;
                }
                Eksponat* temp_prev = temp->prev;
                Eksponat* temp_next = temp->next;
                if(temp_prev != NULL) {
                        temp_prev->next = temp->next;
                        if(temp->next == NULL) {
                                this->lista_koniec = temp_prev;
                        }
                }
                if(temp_next != NULL) {
                        temp_next->prev = temp->prev;
                        if(temp->prev == NULL) {
                                this->lista_poczatek = temp_next;
                        }
                }
                temp_usun = temp;
                if(wlaczKomunikaty) cout<<"\nUsunieto Eksponat o ID: "<<temp_usun->id;
                delete temp_usun;

                this->liczbaEksponatow--;
                if(this->liczbaEksponatow == 0)
                {
                        this->lista_poczatek = NULL;
                        this->lista_koniec = NULL;
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
        if(temp == NULL) {
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
                fstream plik;
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
                        while(temp != NULL)
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
                                plik<<temp->id<<endl;
                                plik<<temp->tytul_dziela<<endl;
                                plik<<temp->imie_autora<<endl;
                                plik<<temp->nazwisko_autora<<endl;
                                plik<<temp->narodowosc_autora<<endl;
                                plik<<temp->data_wykonania<<endl;
                                plik<<temp->cena_w_pln<<endl;
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
        if(this->lista_poczatek != NULL)//czy lista nie jest pusta? jesli jest pusta -> nie tworz wskaznika
        {
                Eksponat* temp = this->lista_poczatek;
                int ID_delete; //id do skasowania
                while(temp != NULL)
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
        if (komunikat == 1) //wyswietl komunikat z pytaniem czy zaladowac baze
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
                        zaladuj_baze = 1;
                        cout << "Wczytano.\n";
                } else {
                        zaladuj_baze = 0;
                        cout << "Anulowano.\n";
                }
        } else { //brak komunikatu, baza ladowana automatycznie
                zaladuj_baze = true;
        }
        if(!zaladuj_baze)
                return;
        //skasowanie obecnej bazy w pamieci programu
        //jesli baza ladowana przy pierwszym uruchomieniu programu -> nie uruchamiana jest funkcji kasujaca
        if(czy_kasowac == 1) { //true = uruchom funkcje kasujaca baze
                skasujKatalog();
        }
        // odczyt bazy
        ifstream ifile(this->URL_Baza);
        string tab[7]; //tablica zawierajaca 7 wierszy z kazdym polem informacji z bazy txt
        string wiersz;
        int l=1; //liczba linii
        while(!ifile.eof()) {
                getline(ifile,wiersz);
                if(wiersz!="")
                {
                        if(l%7==0) {
                                tab[6] = wiersz;
                        } else if(l%6==0) {
                                tab[5] = wiersz;
                        } else if(l%5==0) {
                                tab[4] = wiersz;
                        } else if(l%4==0) {
                                tab[3] = wiersz;
                        } else if(l%3==0) {
                                tab[2] = wiersz;
                        } else if(l%2==0) {
                                tab[1] = wiersz;
                        } else if(l%1==0) {
                                tab[0] = wiersz;
                        }
                }
                if (l % 7 == 0) {
                        dodajEksponatBezposrednio(this->lista_poczatek, this->lista_koniec, tab[0],tab[1],tab[2],tab[3],tab[4],tab[5],tab[6]);
                        l=0; //reset licznika
                }
                l++;
        }
        ifile.close();
}
//-------------------
string Eksponat::czymJestes()
{
        return "eksponat";
}
//-------------------
string Obraz::czymJestes()
{
        return "obraz";
}
//-------------------
string Fotografia::czymJestes()
{
        return "fotografia";
}
//-------------------
string Rzezba::czymJestes()
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
        while(temp != NULL)
        {
                tab[index].id                   =   temp->id;
                tab[index].tytul_dziela         =   temp->tytul_dziela;
                tab[index].imie_autora          =   temp->imie_autora;
                tab[index].nazwisko_autora      =   temp->nazwisko_autora;
                tab[index].narodowosc_autora    =   temp->narodowosc_autora;
                tab[index].data_wykonania       =   temp->data_wykonania;
                tab[index].cena_w_pln           =   temp->cena_w_pln;

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
        Eksponat wtemp;//zmienna pomocnicza
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
                        }}

                if(i <= j)
                {

                        wtemp = t[i];
                        //informacje o adresach do kolejnych eksponatow pozostaja bez zmian
                        t[i].id = t[j].id;
                        t[i].tytul_dziela = t[j].tytul_dziela;
                        t[i].imie_autora = t[j].imie_autora;
                        t[i].nazwisko_autora = t[j].nazwisko_autora;
                        t[i].narodowosc_autora = t[j].narodowosc_autora;
                        t[i].data_wykonania = t[j].data_wykonania;
                        t[i].cena_w_pln = t[j].cena_w_pln;

                        t[j].id = wtemp.id;
                        t[j].tytul_dziela = wtemp.tytul_dziela;
                        t[j].imie_autora = wtemp.imie_autora;
                        t[j].nazwisko_autora = wtemp.nazwisko_autora;
                        t[j].narodowosc_autora = wtemp.narodowosc_autora;
                        t[j].data_wykonania = wtemp.data_wykonania;
                        t[j].cena_w_pln = wtemp.cena_w_pln;
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
