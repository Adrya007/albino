eiti-zpr-zadanie-dodatkowe
==========================

Zadanie dodatkowe z przedmiotu ZPR: przykładowa aplikacja wykorzystująca Python([web2py][web2py]), C++([boost][boost]) oraz [Adobe Flex][flex].

**Projekt znajduje się w katalogu SudokuSolver.** Tam jest np. plik SConstruct.

Wymagane biblioteki:
+ [boost][boost],
+ [PyAMF][pyamf],
+ [web2py][web2py],
+ [SCons][scons].

[web2py]: http://www.web2py.com/
[boost]: http://www.boost.org/
[flex]: http://www.adobe.com/pl/products/flex.html
[pyamf]: http://www.pyamf.org/index.html
[scons]: http://www.scons.org/

Zadanie oraz treść niniejszej instrukacji oparte są na przykładach ze strony <http://staff.elka.pw.edu.pl/~rnowak2/dyd/zpr2013L/homework.html>.

Opis
----

**Jest to aplikacja rozwiązuje proste zadania Sudoku.** Program NIE sprawdza poprawności wprowadzonego częściowego rozwiązania (czy np. nie występuję dwie takie same cyfry w wierszu), lecz po prostu próbuje rozwiązać zadany układ.

Format danych wejściowych
-------------------------

W pliku **SudokuSolver/puzzle-examples/txt** znajdują się przykładowe łamigłówki, które aplikacja potrafi lub nie potrafi rozwiązać. Wystarczy skopiować taką łamigłówkę do górnego pola aplikacji w przeglądarce pod adresem **http://127.0.0.1:8000/sudoku/static/client.html**, a następnie kliknąć "Solve this sudoku!".

Przykładowe dane wejściowe:

				12.|4.6|7.9
				.5.|7..|1..
				..9|..3|.5.
				---+---+---
				23.|..7|8..
				...|.9.|2..
				8.1|2.4|.6.
				---+---+---
				.4.|..8|91.
				6.8|...|...
				.1.|.45|6.8

Tak naprawdę znaczenie mają tylko cyfry od 1 do 9 oraz kropki (oznaczające brak wartości). Pozostałe znaki są ignorowane.

Kompilacja i uruchomienie
-------------------------

### Przygotowanie środowiska ###

#### Linux (Ubuntu 13.04) ####

1. Intalujemy *g++* oraz *Python* wraz z *pip*:

				sudo apt-get update
				sudo apt-get install g++ python python-dev python-pip
				
2. Instalujemy *PyAMF*:

				sudo pip install pyamf
				
3. Następnie należy [pobrać][web2pySrc] i rozpakować *web2py* :

[web2pySrc]: http://www.web2py.com/examples/static/web2py_src.zip

				cd ~/Downloads
				unzip web2py_src.zip
				mv web2py ~/web2py
			
			
4. Kolejny krok to [pobranie][boostSrc] i rozpakowanie bibliotek *boost* oraz ich instalacja:

[boostSrc]: http://sourceforge.net/projects/boost/files/boost/1.53.0/boost_1_53_0.tar.bz2/download

				cd ~/Downloads
				tar jxvf boost_1_53_0.tar.bz2
				mv boost_1_53_0 ~/boost_1_53_0
				cd  ~/boost_1_53_0
				./bootstrap.sh
				./b2
				sudo cp -R boost /usr/include/boost
				sudo cp -R stage/lib/* /usr/lib/				
				
5. Przed następnym krokiem należy upewnić się, że jest zainstalowane [Java SE Development Kit][javaSrc]. Można postępować zgodnie z instrukcjami ze strony albo wykonać następujące polecenia ([źródło][ubuntuJava]):

[javaSrc]: http://www.oracle.com/technetwork/java/javase/downloads/index.html
[ubuntuJava]: http://ebloog.pl/ubuntu-instalacje-oracle-java/

				sudo add-apt-repository ppa:webupd8team/java
				sudo apt-get update 
				sudo apt-get install oracle-java7-installer
			
7. Teraz można [pobrać][flexSrc] i rozpakować w odpowienie miejsce *Flex SDK* oraz dodać jego binaria do zmiennej *PATH*:

[flexSrc]: http://www.adobe.com/devnet/flex/flex-sdk-download.html

				cd ~/Downloads
				unzip flex_sdk_4.6.zip -d flex
				mv flex ~/flex
				cd ~
				gedit .profile
				
   W pliku *.profile* należy dopisać poniższe linie, a następnie wylogować się i zalogować ponownie, aby zmiany nastąpiły:
	 
				# Adobe Flex
				if [ -d "$HOME/flex/bin" ] ; then
					PATH="$HOME/flex/bin:$PATH"
				fi

8. Na koniec potrzebne będzie narzędzie *Scons*:

				sudo apt-get install scons

#### Windows XP ####

1. Zainstaluj Microsoft Visual Studio.

2. Zainstaluj Pyhon 2.7 np. w domyślnej ścieżce `C:\Python27\` i dodaj tę ścieżkę do zmiennej środowiskowej *Path*.

3. Zainstaluj narzędzie *pip* dla Python-a

4. Zainstaluj *PyAMF* poleceniem `pip install pyamf`
				
5. Następnie należy [pobrać][web2pySrc] i rozpakować *web2py* np. do `C:\web2py` :

6. [Pobierz][boostSrc] i rozpakuj biblioteki *boost*. Następnie w oknie terminala Visual Studio (muszą być ustawione ścieżki do kompilatora) uruchomić komendę `bootstrap`, później `.\bjam.exe --build-type=complete`  w celu kompilacji, a nia koniec `.\bjam --build-type=complete install` w celu przeniesienia nagłówków i wersji *release* do `C:\boost'.

7. Przed kolejnym krokiem konieczna będzie instalacja właściwej wersji Java. Zainstaluj 32-bitową Javę SE w wersji JRE (nie JDK). Następnie utwórz katalog np. `C:\Java7_x86` i utwórz w nim dowiązanie do `jre7` czy innego katalogu JRE - w konsoli wpisz np.:

				mklink /J jre "C:\Program Files (x86)\Java\jre7"

8. [Pobierz][flexSrc] i rozpakuj gdzieś Adobe Flex. Następnie ścieżkę do katalogu `bin` wewnątrz miejsca rozpakowania Adobe Flex dodaj do zmiennej ~środowiskowej `Path`.

   Teraz w katalogu Flex-a (np. `C:\Flex 4.6`) w pliku `bin\jvm.config` zamień linię
	 
				java.home=
				
   na
	 
				java.home=C:/Java7_x86
				
   Uruchom z konsoli `mxmlc` (po wcześniejszym dodaniu `C:\Flex 4.6\bin` do `Path`) i upewnij się, że wszystko jest OK.

9. [Pobrać][scons] i zainstalować *Scons*.

### Kompilacja ###

Kompilacja pod Linux z poziomu katalogu **SudokuSolver**:

				scons -c
				scons

kompilacja pod Windows z poiomu katalogu **SudokuSolver** (kompilację należy uruchomić w oknie terminala Visual Studio):

				scons -c
				scons

### Testowanie wołania biblioteki (Python) ###

1. Przejdź do katalogu `SudokuSolver/app/modules`. Powinna być tam skopiowana biblioteka dzielona, np. `sudoku.so` lub `sudoku.pyd`.

2. Uruchom interpreter Pythona i wpisać w nim:

				import sudoku
				sudoku.solveSudoku("abc")
				
   W efekcie powinno pojawić się:
	 
				'TEXT TOO SHORT!'

   Wyjdź poleceniem `quit()`.
				
### Testowanie serwera ###

1. Katalog `SudokuSolver/app` skopiuj pod nową nazwą w lokację `C:\web2py\applications\sudoku` (zakładając, że *web2py* rozpakowano do `C:\web2py`). Dla konfiguracji linuksowej będzie to:

				cp -R SudokuSolver\app ~\web2py\applications\sudoku
				
2. Uruchom serwer: w katalogu `C:\web2py` lub `~/web2py` wywołać komendę:

				python web2py.py
				
   Następnie wybrać działanie pod adresem **127.0.0.1:8000**. Powinna uruchomić się w przeglądarce strona <http://127.0.0.1:8000/sudoku>.
	 
3. Z katalogu `SudokuSolver` wykonaj poniższe polecenie i przekonaj się, że nie pojawiły się żadne komunikaty błędów:

				python echo.py
				
   To polecenie uruchomi szereg zapytań do serwera z przykładowymi planszami sudoku, które aplikacja serwerowa będzie w stanie (lub nie) rozwiązać. **Komunikaty w stylu 'TEXT TOO SHORT!' są poprawnymi komunikatami i nie należy się nimi przejmować.**

### Testowanie aplikacji w przeglądarce ###

1. Wykonaj punkty 1 i 2 z poprzedniego opisu nt. testowania serwera w celu uruchomienia serwera

2. Uruchom przeglądarkę i przejdź do adresu <http://127.0.0.1:8000/sudoku>. Powinna się pojawić strona z linkiem do strony <http://127.0.0.1:8000/sudoku/static/client.html>. Można w niego kliknąć, ale i tak przekierowanie nastąpi po 3 sekundach.

3. Po przejściu na <http://127.0.0.1:8000/sudoku/static/client.html> powinno wyświetlić się przykładowe Sudkou oraz przycisk do jego rozwiązania i miejsce na wynik.

### Przydatny skrypt dla środowika linuksowego ###

W celu przyspieszenia procesu wygenerowania nowej wersji aplikacji po każdej zmianie przygotowany został skrypt `deploy.sh` w katalogu `SudokuSolver`. Należy wywołać go komendą:

				./deploy.sh
