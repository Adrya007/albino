#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <time.h>
#include <sstream>
#include <cstdlib>
#include "galeria.h"

using namespace std;


//konstruktor2
KatalogGalerii::KatalogGalerii()

{
    //definicja zmienych prywatnych
    this->URL_Baza = "baza_log/KatalogGaleryjki.txt";
    this->URL_AutoIncrement = "baza_log/AutoIncrement.txt";
    this->URL_LogWyszukiwanie = "baza_log/log_wyszukiwanie.txt";
    //inicjalizacja wskaznikow prywatych
    this->lista_poczatek = NULL;
    this->lista_koniec = NULL;
    this->liczbaEksponatow = 0;
    // ladujemy informacje o numerze ostatniego ID z pliku konfiguracyjnego
    // przed odczytem otwieramy plik tak jakbysmy chcieli cos dopisac ale nic nie dopiszemy dzieki temu nieistniejacy plik zostanie utworzony
    fstream plik;
    plik.open(this->URL_AutoIncrement, ios::app);
    plik.close();
}
//-------------------------------------------

KatalogGalerii::KatalogGalerii(string miejsce_galerii, bool czy_bilety, bool czy_przewodnik)
{
	miejsce_galerii_ = miejsce_galerii;
	czy_bilety_ = czy_bilety;
	czy_przewodnik_ = czy_przewodnik;
}
//-------------------------------------------
void KatalogGalerii::wypiszInfoOGalerii()
{
	cout<<"Galeria ADA znajduje sie w miescie: "<<miejsce_galerii_<<" Czy sa jeszcze bilety: "<<czy_bilety_<<" Czy jest tam przewodnik: "<<czy_przewodnik_<<endl;
}
//-------------------------------------------
Eksponat::Eksponat(){}
Eksponat::~Eksponat(){}






void KatalogGalerii::wypiszKatalog()
{
    if(this->lista_poczatek == NULL) {
        cout<<"\nLista jest pusta!";
    } else {
        Eksponat* temp = this->lista_poczatek;
        while(temp != NULL)
        {
            cout<<"ID:          "<<temp->id<<"\n"
                <<"Tytul dziela:        "<<temp->tytul_dziela<<"\n"
                <<"Nazwisko autora:    "<<temp->nazwisko_autora<<"\n"
                <<"Imie autora: "<<temp->imie_autora<<"\n"
                <<"Rok powstania dziela:    "<<temp->data_wykonania<<"\n"
                <<"Cena:     "<<temp->cena_w_pln<<"\n"
                <<"Narodowosc autora:      "<<temp->data_wykonania<<"\n"
                <<"==========================================\n";
            temp = temp->next;
        }
    }
}
//------------------------------------------
// w_l - wskaznik pierwszego elementu na calej liscie!

// w_k - wskaznik konca listy

// gdzie_dodac==1 dodamy na koniec listy, a gdy==0 to na poczatek

void KatalogGalerii::dodaj(Eksponat* &w_l, Eksponat* &w_k, int gdzie_dodac)

{
    Eksponat* wn = new Eksponat;
    //zwiekszamy wartosci zmiennych prywatynch
    this->autoIncrement++;
    this->liczbaEksponatow++;
    wn->id = this->autoIncrement;
    cout<<"\nPodaj imie autora: ";
    getline(cin,wn->imie_autora);
    while(wn->imie_autora == "") {
        cout<<"\nPodales pusty ciag znakow! Podaj imie: ";
        getline(cin,wn->imie_autora);
    }
    cout<<"\nPodaj nazwisko autora: ";
    getline(cin,wn->nazwisko_autora);
    while(wn->nazwisko_autora == "") {
        cout<<"\nPodales pusty ciag znakow! Podaj nazwisko: ";
        getline(cin,wn->nazwisko_autora);
    }
    cout<<"\nPodaj rok powstania dziela: ";
    string data_wykonania;
    int data_wykonania_int;
    getline(cin,data_wykonania); //ladujemy do stringa rok
    data_wykonania_int = atoi(data_wykonania.c_str()); //konwersja stringa na int
    while(data_wykonania == "" || data_wykonania_int == 0) {//jesli nie podano roku lub podany rok to liczba 0, np. jesli ktos zamiast liczby poda slowo to ono jest konwertowane na 0 wiec w takim przypadku ponownie zapytamy o podanie wlasciwego roku
        if(data_wykonania=="") {//podano pusty ciag znakow zamiast roku
            cout<<"\nPodales pusty rok! Podaj nowy rok wykonania dziela: ";
        } else { //podano ciag znakow o jakiejs dlugosci ktory zostal zamieniony na liczbe 0
            cout<<"\nPodales ciag znakow zamiast roku liczbowego! Podaj nowy rok: ";
        }
        getline(cin,data_wykonania);
        data_wykonania_int= atoi(data_wykonania.c_str());
    }
    wn->data_wykonania = data_wykonania_int;
    cout<<"\nPodaj narodowosc autora: ";
    getline(cin,wn->narodowosc_autora);
    while(wn->narodowosc_autora == "") {
        cout<<"\nPodales pusty ciag znakow! Podaj narodowosc: ";
        getline(cin,wn->narodowosc_autora);
    }
    cout<<"\nPodaj tytul dziela: ";
    getline(cin,wn->tytul_dziela);
    while(wn->tytul_dziela == "") {
        cout<<"\nPodales pusty ciag znakow! Podaj tytul: ";
        getline(cin,wn->tytul_dziela);
    }
    cout<<"\nPodaj cene dziela: ";
    string cena_w_pln;
    int cena_w_pln_int;
    getline(cin,cena_w_pln); //ladujemy do stringa rok
    cena_w_pln_int = atoi(cena_w_pln.c_str()); //konwersja stringa na int
    while(cena_w_pln == "" || cena_w_pln_int== 0) {//jesli nie podano roku lub podany rok to liczba 0, np. jesli ktos zamiast liczby poda slowo to ono jest konwertowane na 0 wiec w takim przypadku ponownie zapytamy o podanie wlasciwego roku
        if(cena_w_pln=="") {//podano pusty ciag znakow zamiast roku
            cout<<"\nPodales pusta cene! Podaj nowa: ";
        } else { //podano ciag znakow o jakiejs dlugosci ktory zostal zamieniony na liczbe 0
            cout<<"\nPodales ciag znakow zamiast jednej liczby: ";
        }
        getline(cin,cena_w_pln);
        cena_w_pln_int= atoi(cena_w_pln.c_str());
    }
    if(gdzie_dodac == 1) { //gdzie_dodac==1 to dodajemy na koniec listy
        wn->prev = w_k; //poprzedni element przed tym ktory teraz dodalismy to w_k czyli obecny koniec listy
        wn->next = NULL; // nastepny element to NULL bo wlasnie dodajemy ostatni element i po nim nic juz nie ma
        if(w_k != NULL) {
            w_k->next = wn;
        } else { //w_k==NULL co znaczy ze dodajemy pierwszy element!
            w_l = wn;
        }
        w_k = wn; //teraz ustawiamy ze nowym elementem koncowym jest nasze wn (wskaznik nowy do elementu ktory wlasnie dodalismy)
        cout<<"\nDodano na koniec listy!";
    } else { //gdzie_dodac==0 to dodajemy na poczatek listy
        wn->prev = NULL; //pierwszy element listy nigdy nie ma poprzednika
        wn->next = w_l; //nastepnym elementem listy staje sie wskaznik ktory dotychczas pokazywal na poczatek listy
        //aktualizujemy wskaznik ktory teraz staje sie drugim elementem listy aby wiedzial ze ma przed soba nasze wn
        if(w_l != NULL) {
            w_l->prev = wn;
        } else { //tylko gdy po raz pierwszy dodajemy rekord to ten dodany wlasnie element staje sie koncowym
            w_k = wn;
        }
        w_l = wn; //naszym nowym poczatkiem listy staje sie wn
        cout<<"\nDodano na poczatek listy!";
    }
}

//-------------------------------------------
void KatalogGalerii::dodajEksponatBezposrednio(Eksponat* &w_l, Eksponat* &w_k, string id, string t, string n, string i, string d, string z, string nar)
{
    Eksponat* wn = new Eksponat;
    int id_int = atoi(id.c_str()); //konwersja string na int
    wn->id = id_int;
    wn->imie_autora = i;
    wn->nazwisko_autora = n;
    int data_wykonania = atoi(d.c_str()); //konwersja string na int
    wn->data_wykonania=data_wykonania;
    wn->narodowosc_autora = nar;
    wn->tytul_dziela = t;
    float cena_w_pln = atoi(z.c_str());
    wn->cena_w_pln=cena_w_pln;
    //dodajemy na koniec listy

    wn->prev = w_k; //poprzedni Eksponat przed tym ktory teraz dodalismy to w_k czyli obecny koniec listy
    wn->next = NULL; // nastepny Eksponat to NULL bo wlasnie dodajemy ostatni Eksponat i po nim nic juz nie ma
    if(w_k != NULL) {
        w_k->next = wn;
    } else { //w_k==NULL co znaczy ze dodajemy pierwszy Eksponat!
        w_l = wn;
    }
    w_k = wn; //teraz ustawiamy ze nowym Eksponatem koncowym jest nasze wn (wskaznik nowy do Eksponatu ktory wlasnie dodalismy)
    cout<<"Dodano rekord: "<<id<<", "<<t<<", "<<n<<", "<<i<<", "<<d<<", "<<z<<", "<<nar<<"\n";
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
Eksponat::Eksponat(int tytul_dziela_, int data_wykonania_, string nazwisko_autora_, string imie_autora_, string narodowosc_autora_, float cena_w_pln_, int id_)
{
    tytul_dziela=tytul_dziela;
	int data_wykonania=data_wykonania_;
	string nazwisko_autora=nazwisko_autora_;
	string imie_autora=imie_autora_;
	string narodowosc_autora=narodowosc_autora_;
	float cena_w_pln=cena_w_pln_;
	int id=id_;
}

//Eksponat::void wypiszEksponat()

//---------------------------------------
KatalogGalerii::~KatalogGalerii()
{
    saveAutoIncrement();
}
//domyslne parametry okreslone w galeria.h
//int WlaczKomunikaty=1, int ID_delete=0

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
    if(wlaczKomunikaty)	wypiszKatalog();
    if(this->lista_poczatek == NULL && this->lista_koniec == NULL)
    {
        if(wlaczKomunikaty)	cout<<" Nie ma co usuwac!";
    }
    else
    {
        int id;
        if(wlaczKomunikaty) {
            cout<<"\nPodaj ID rekordu ktory usunac: ";
            string get;
            getline(cin,get);
            id = atoi(get.c_str()); //konwersja string na int
        } else {
            id = ID_delete; //usuwamy id ktory przeslalismy jako argument funkcji
        }
        Eksponat* temp = this->lista_poczatek;
        int znaleziono = 0; //domyslana zmienna okreslajaca ze nie znaleziono Eksponatu do usuniecia
        Eksponat* temp_usun;
        while(temp != NULL)
        {
            if(temp->id == id) {
                Eksponat* temp_prev = temp->prev; //1
                Eksponat* temp_next = temp->next; //3
                //zalozmy mamy Eksponat 1, 2, 3. Eksponat 2 usuwamy.
                // Ponizej Eksponatowi 1 ustawiamy iz po nim jest 3
                if(temp_prev != NULL) {
                    temp_prev->next = temp->next; //ustawiamy ze po elemencie 1 jest 3
                    if(temp->next == NULL) { //to oznacza ze ostatni Eksponat nie istnieje wiec Eksponat 2 ktory teraz usuwamy  jest ostatnim a wiec Eksponat 1 bedzie teraz ostatnim wiec musimy mu ustawic ze dla naszej listy wskaznik ostatni to nasz Eksponat 1
                        this->lista_koniec = temp_prev;
                    }
                }
                // Ponizej Eksponatowi 3 ustawiamy iz go poprzedza 1
                if(temp_next != NULL) {
                    temp_next->prev = temp->prev;
                    if(temp->prev == NULL) { //jezeli nie istnieje Eksponat 1 to ustawiamy ze Eksponat 3 staje sie poczatkiem listy bo skasowalismy Eksponat 2
                        this->lista_poczatek = temp_next;
                    }
                }
                //kasujemy Eksponat 2
                temp_usun = temp;
                if(wlaczKomunikaty) cout<<"\nUsunieto Eksponat o ID: "<<temp_usun->id;
                delete temp_usun;

                //cout<<"ntemp_usun: "<<temp_usun->imie;
                //cout<<"ntemp: "<<temp->imie;

                this->liczbaEksponatow--; //zmniejszamy liczbe rekordow
                if(this->liczbaEksponatow == 0)
                {
                    //skasowalismy wszystkie rekordy wiec ustawiamy na NULL wartosci
                    this->lista_poczatek = NULL;
                    this->lista_koniec = NULL;
                }
                znaleziono = 1; //znaleziono rekord do usuniecia
                break; //przerwanie petli poniewaz znalezlismy juz Eksponat do usuniecia
            } else {
                temp = temp->next;
            }
        }
        if(znaleziono == 0 && wlaczKomunikaty) {
            cout<<"\nNie znaleziono rekordu do usuniecia!";
        }
    }
}






//--------------------------------------

void KatalogGalerii::zapiszKatalogDoPliku (int wyswietlKomunikat, int wyswietlKomunikat2)
{
    Eksponat* temp = this->lista_poczatek;
    if(temp == NULL) {
        if(wyswietlKomunikat) {//ten komunikat wyswietlamy podczas akcji zapisu do pliku, natomiast gdy uzytkownik uruchamia kasowanie bazy danych to pozniej wyswietlimy tylko same odpowiedzy czy chce rowniez skasowac baze txt. Nie wyswietlamy ponizszego komunikatu poniewaz juz w metodzie SkasujBaze jest wyswietlany komunikat z pytaniem
        cout<<"\nBrak rekordow w bazie ktore by mozna zapisac!\n"
            <<"A moze chcesz wyczyscic baze danych w pliku txt?\n";
        }
        cout<<"1 - Tak, wyczysc baze danych w pliku txt\n"
            <<"2 - Nie\n";
        char nawigacja;
        do {
            nawigacja = _getch();
        } while(nawigacja != '1' && nawigacja != '2');
        if(nawigacja == '1') {
            wyczyscKatalogWPliku();
            cout<<"Baza danych w pliku txt zostala wyczyszczona!\n";
        } else {
            cout<<"Baza danych w pliku txt pozostala nienaruszona.\n";
        }
    } else {
        cout<<"nCzy chcesz zapisac liste rekordow do bazy w pliku txt?\n"
            <<"1 - Zapisz baze do pliku (obecne dane w pliku zostana nadpisane)\n"
            <<"2 - Zapisz baze do pliku poprzez dopisanie nowych rekordow\n"
            <<"3 - Nie zapisuj bazy\n";
        char nawigacja;
        do {
            nawigacja = _getch();
        } while(nawigacja != '1' && nawigacja != '2' && nawigacja != '3');
        fstream plik;
        if(nawigacja == '1') {
            plik.open(this->URL_Baza, ios::out); //ustawiamy tryb nadpisania pliku
        } else if(nawigacja == '2') {
            plik.open(this->URL_Baza, ios::app); //ustawiamy tryb dopisywania do pliku
        } else {
            cout<<"\nBaza nie zostanie zapisana!";
        }
        //zapisujemy dane w pliku

        if(nawigacja == '1' || nawigacja == '2')
        {
            cout<<"\nTrwa zapisywanie...n";
            if(nawigacja == '2') {
                cout<<"\nWybrales opcje dopisania rekordow do bazy.n"
                    <<"Aby uniknac dublowania sie numerow ID, rekordy z pamieci programu\n"
                    <<"otrzymaja nowe ID, ktore bedzie wieksze niz rekordow w bazie txt\n";
            }
            int tempID;
            while(temp != NULL)
            {
                /* jesli dopisujemy rekordy do bazy to zmieniamy tym rekordom ID nawieksze
                niz posiadaja rekordy w pliku txt aby uniknac sytuacji ze dwa rekordy maja
                w bazie txt ten sam ID.
                */
                if(nawigacja == '2') {
                    //nadajemy rekordom nowe ID, wieksze od ostatnio dodanych ID w bazie aby uniknac sytuacji powtarzania sie ID rekordow w bazie
                    //jednoczesnie robimy to przez preinkrementacje aby zwiekszyc wartosc AutoIncrement
                    tempID = ++autoIncrement;
                    cout<<"Zapisano rekord o ID="<<temp->id<<" w bazie txt i w pamieci programu pod nowym ID: "<<tempID<<"\n";
                    temp->id = tempID; //ID z pamieci programu zmieniamy na nowe ID ktore bedzie w bazie aby zachowac synchornizacje numerow ID
                } else {
                    tempID = temp->id;
                    cout<<"Zapisano rekord o ID="<<temp->id<<"\n";
                }
                //wykonanie zapisu do pliku
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
            saveAutoIncrement(); //zapisujemy ID ostatnio dodanego rekordu
            if(nawigacja == '1') {
                cout<<"Pomyslnie nadpisano baze danych nowymi rekordami!\n";
            } else { //2
                cout<<"Pomyslnie dopisano rekordy do bazy danych!\n";
                /*trzeba teraz jeszcze zaktualizowac pamiec programu o rekordy ktore sa w bazie txt
                Mianowicie dane rekordy z pamieci dopisalismy do pliku txt zmieniajac im ID tak aby nie dublowac numerow ID
                z pliku txt. Teraz w pliku txt mamy jakies rekordy ktore juz tam byly plus rekordy ktore wlasnie dopisalismy.
                Dlatego wykonujemy teraz zaladowanie do pamieci programu calej bazy txt aby w pamieci miec to samo co w pliku txt
                */
                if(wyswietlKomunikat2) {
                    cout<<"UWAGA: Teraz powinienes zsynchronizowac zawartosc pamieci programu z baza txt.\n"
                        <<"Jesli chcesz to zrobic to po prostu zgodz sie na zaladowanie bazy z pliku:\n";
                    wczytajKatalogZPliku(1, 1); //1-wyswietlamy komunikatu czy wczytac baze, 1-kasujemy baze w pamieci programu po czym ladujemy z pliku
                }
            }
        }
    }
}
//--------------------------------------

void KatalogGalerii::wyczyscKatalogWPliku()
{
    fstream plik;
    plik.open(this->URL_Baza, ios::out); //ustawiamy tryb nadpisania pliku
    plik<<"";
    plik.close();
    saveAutoIncrement(); //zapisujemy ID ostatnio dodanego rekordu
}








//---------------------------------------
void KatalogGalerii::skasujKatalog(int wyswietlKomunikat)
{
    if(this->lista_poczatek != NULL)//sprawdzamy czy lista nie jest pusta, bo jesli jest pusta to nie ma sensu tworzyc wskaznika
    {
        Eksponat* temp = this->lista_poczatek;
        int ID_delete; //id do skasowania
        while(temp != NULL)
        {
            ID_delete = temp->id; //przypisujemy do zmiennej pomocniczej ID poniewaz musimy przed usunieciem rekordu odczytac adres kolejnego Eksponatu
            temp = temp->next;
            usunEksponat(0, ID_delete); //usuwamy rekord o danym ID
        }
        if(wyswietlKomunikat) {

            cout<<"Usunieto wszystkie rekordy z pamieci programu!\n";
        }
    } else if(wyswietlKomunikat) {
        cout<<"Baza danych w pamieci programu jest pusta! Nie ma co tam kasowac!\n";
    }
    if(wyswietlKomunikat) {
        cout<<"Czy chcesz rowniez aby wyczyscic plik txt bazy danych?\n";
        zapiszKatalogDoPliku(0);//uruchamiamy te metode bez wyswietlania komunikatu z pytaniem czy chcemy skasowac baze txt
    }
}

//------------------------------------------------
void KatalogGalerii::wczytajKatalogZPliku(bool komunikat, bool czy_kasowac)
{
    bool zaladuj_baze;
    if(komunikat == 1) //wyswietl komunikat z pytaniem czy zaladowac baze
    {
        cout<<"Czy chcesz wczytac baze danych z pliku do pamieci programu?\n"
            <<"(Baza zawarta w pamieci programu zostanie nadpisana baza z pliku)\n"
            <<"1 - Wczytaj baze z pliku\n"
            <<"2 - Anuluj\n";
        char nawigacja_dodaj;
        do {
            nawigacja_dodaj = _getch();
        } while(nawigacja_dodaj != '1' && nawigacja_dodaj != '2');
        if(nawigacja_dodaj == '1') {
            zaladuj_baze = 1;
            cout<<"Wczytano!\n";
        } else {
            zaladuj_baze = 0;
            cout<<"Anulowano wczytywanie bazy z pliku...\n";
        }
    } else { // nie wyswietlamy komunikatu i odrazu ladujemy automatycznie baze
        zaladuj_baze = 1;
    }
    if(zaladuj_baze) {
        //skasowanie obecnej bazy w pamieci programu
        //jesli ladujemy baze przy pierwszym uruhcomieniu programu to nie uruchamiamy funkcji kasujacej
        if(czy_kasowac == 1) { //true = uruchom funkcje kasujaca baze
            skasujKatalog();
        }
        // odczyt bazy

        ifstream ifile(this->URL_Baza);
        string tab[5]; //tablica zawierajaca 5 wierszy z kazdym polem informacji z bazy txt
        string wiersz;
        int l=1; //liczba linii
        while(!ifile.eof()) {
            getline(ifile,wiersz);
            //cout<<l<<": "<<wiersz<<endl;
            if(wiersz!="")
            {
                if(l%7==0) {
                    tab[6] = wiersz;
                } else if(l%6==0) {
                    tab[5] = wiersz;
                } else if(l%5==0) {
                    tab[4] = wiersz; //tab[4] bo indexy od 0
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
            if(l%7==0) {
                dodajEksponatBezposrednio(this->lista_poczatek, this->lista_koniec, tab[0],tab[1],tab[2],tab[3],tab[4],tab[5],tab[6]);
                l=0; //resetujemy po 5 rekordach na 0 licznik
            }
            l++;
        }
        ifile.close();
    }
//funkcja przyjmujaca jako argumenty stringi, dodajemy nowy rekord na koniec listy
}
//-------------------
string Eksponat::czymJestes()
{
    return "Jestem Eksponatem";
}
//-------------------
string Obraz::czymJestes()
{
    return "Jestem Obrazem";
}
//-------------------
string Fotografia::czymJestes()
{
    return "Jestem Fotografia";
}
//-------------------
string Rzezba::czymJestes()
{
    return "Jestem Rzezba";
}
//-------------------


void KatalogGalerii::sortujEksponaty()
{
    countLiczbaEksponatow(); //przeliczamy liczbe rekordow
    if(liczbaEksponatow) {
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

        //tworzymy tablice elementow

        int index=0;
        while(temp != NULL)
        {
            tab[index].id			        =	temp->id;
            tab[index].imie_autora			=	temp->imie_autora;
            tab[index].nazwisko_autora		=	temp->nazwisko_autora;
            tab[index].cena_w_pln	        =	temp->cena_w_pln;
            tab[index].narodowosc_autora	=	temp->narodowosc_autora;
            tab[index].data_wykonania   	=	temp->data_wykonania;
            tab[index].tytul_dziela        	=	temp->tytul_dziela;

            temp = temp->next;
            index++;
        }
        if(nawigacja == '1') {
            cout<<"Wybrales ID jako kryterium sortowania.\n";
            QuickSort(tab, 0, liczbaEksponatow-1, "id", 1);//przy pierwszym wywolaniu quicksort pytamy sie o kolejnosc w jakiej maja byc posortowane rekordy (typ sortowania: ASC lub DESC)
        } else if(nawigacja == '2') {
            cout<<"Wybrales nazwisko autora jako kryterium sortowania.\n";
            QuickSort(tab, 0, liczbaEksponatow-1, "nazwisko autora", 1);
        } else if(nawigacja == '3') {
            cout<<"Wybrales cene jako kryterium sortowania.\n";
            QuickSort(tab, 0, liczbaEksponatow-1, "cena", 1);
        }
        //wyswietlamy posortowane wyniki
        for(int i=0; i<liczbaEksponatow; i++)
        {
            cout<<"ID:          "<<tab[i].id<<"\n";
            cout<<"Imie:        "<<tab[i].imie_autora<<"\n";
            cout<<"Nazwisko autora:    "<<tab[i].nazwisko_autora<<"\n";
            cout<<"Tytul dziela: "<<tab[i].tytul_dziela<<"\n";
            cout<<"Data wykonanania:    "<<tab[i].data_wykonania<<"\n";
            cout<<"Cena w polskich zlotych:    "<<tab[i].cena_w_pln<<"\n";
            cout<<"Narodowosc autora:    "<<tab[i].narodowosc_autora<<"\n";
            cout<<"==========================================\n";
        }
    }
}
//----------------------------------------------

void KatalogGalerii::QuickSort(Eksponat t[], int p, int k, string co_sortowac, int kolejnosc)
{
    static char typ_kolejnosci;
    if(kolejnosc) {//przy pierwszym uruchomieniu funkcji zapytamy o sposob prezentacji wynikow
        cout<<"Wybierz sposob wyswietlenia posortowanych danych:\n"
            <<"1 - ASC (rekordy od najmniejszego do najwiekszego)\n"
            <<"2 - DESC (rekordy od najwiekszego do najmniejszego)\n";
        do {
            typ_kolejnosci = _getch();
        } while(typ_kolejnosci != '1' && typ_kolejnosci != '2');
    }
    int i, j, pivot;
    string pivot_s; //pivot dla stringow
    Eksponat wtemp;//pomocnicza zmienna
    i = p;
    j = k;
    if(co_sortowac == "id") {
        pivot = t[p].id; //definicja punkut podzialu
    } else if(co_sortowac == "cena") {
        pivot = t[p].cena_w_pln;
    } else if(co_sortowac == "nazwisko autora"){
            pivot_s = t[p].nazwisko_autora;
    }

    while(i < j) // moga ale nie musza sie powtarzac moga tez byc rowne (zamiana skrajnych)

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
            //cout<<"zamiana: "<<t[i].id<<" z "<<t[j].id<<endl;
            wtemp = t[i];
            //zamieniamy tylko wartosci, a informacje o adresach do kolejnych elementow pozostaja bez zmian
            t[i].id = t[j].id;
            t[i].nazwisko_autora = t[j].nazwisko_autora;
            t[i].cena_w_pln = wtemp.cena_w_pln;
            t[j].id = wtemp.id;
            t[j].nazwisko_autora = wtemp.nazwisko_autora;
            t[j].cena_w_pln = wtemp.cena_w_pln;
            i++;
            j--;
        }
    }
    if(i < k) {
        QuickSort(t, i, k, co_sortowac, 0); //ostatnie 0 oznacza ze nie pytamy sie juz o tym sortowania: ASC lub DESC
        // od i tam gdzie sie zatrzymalo na i, az do k koniec tablicy
    }
    if(p < j) {
        QuickSort(t, p, j, co_sortowac, 0);
    }
}

