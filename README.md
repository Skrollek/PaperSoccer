# PaperSoccer
## Opis programu
Program PaperSoccer służy do gry w piłkarzyki na kartce według zasad opisanych na https://pl.wikipedia.org/wiki/Pi%C5%82karzyki_na_kartce. 

Program posiada funkcjonalność wczytwania i zapisywania gier jak i wyboru wielkości planszy od najmniejszej 4x4 do największej 40x40.

## Technologie
Technologie użyte do stworzenia programu to:

1. Język C11 (GCC 11.2),
2. Biblioteka GTK 4.0,
3. Program make,
4. Visual Studio Code.

## Kompilacja i uruchamianie

### Windows
1. Pobrać i zainstalować MSYS2 (https://www.msys2.org/), zgodnie z poleceniami na stronie.
2. Pobrać i zainstalować bibliotekę GTK 4.0 (https://www.gtk.org/docs/installations/windows/) zgodnie z poleceniami na stronie.
3. Jeżeli kompilator mingw oraz program make nie są zainstalowane to wtedy należy je zainstalować przez menadżer pakietów MSYS2.
4. Przejść do folderu z kodem źródłowym w konsoli MSYS2 MINGW 64 lub 32.
5. Wpisać polecenie "make".
6. Uruchomić program poleceniem ./PaperSoccer.exe

### Linux
1. Pobrać i zainstalować bibliotekę GTK 4.0.
2. Jeżeli któryś z programów: pkg-config, make oraz gcc nie jest zainstalowany to wtedy należy je zainstalować.
3. Przejść do foldoer z kodem źródłowym w konsoli.
4. Wpisać polecenie "make".
5. Uruchomić program polecniem ./PaperSoccer

## Instrukcja

### Start game
Uruchamia grę otwierając dwa okienka. Okienka są przydzielone do gracz odpowidnio 1 i 2. 
W momencie w którym jeden gracz wykonuje ruch kliknięcia drugiego nie będą działać. 
W razie gdyby żadne okno nie pozwalało kliknąć należy oba z nich zminimalizować i odminimalizować.
Klinięcie przycisku "X" w okienku zamyka oba okna i pozwala zapisać stan gry. 
UWAGA jeżeli przebieg gry nie zostanie zapisany nie można go później w żaden sposób odtworzyć.
Zapisanie polega na wypełnieniu pola nazwą pliku kończącą się rozszerzeniem .txt.
Jeżeli nie chcemy zapisać gry wystarczy ponownie nacisnąć przycisk "X".
Na koniec gry gracze zostaną poinformowani o zwycieżcy oraz będą mogli zapisać przebieg gry w identyczny sposób jak przy przerwaniu rozgrywki.
Jeżeli nie chce się zapisywać rogrywki należy albo wyjść do menu za pomocą przycisku lub po prostu wyjść z programu za pomocą "X".
### Load game
Pozwala wczytać wcześniejszą rozgrywkę i ją kontynuwać. 
Wczytywanie odbywa się analogicznie do zapisywania.
Po wczytaniu pliku zostanie uruchmiona gra.
Wczytywane pliki zaczynają się od dwóch liczb: pierwsza będącą ilościa kratek w poziomie plus jeden, druga będące ilością kratek w pionie plus trzy. Obie liczby muszą być nieparzyste. Pierwsza musi być z przedziału od 5 od 41. Druga z przedziału 7 do 43.
UWAGA gra dopuszcza podanie wymiaru planszy większego niż 40 (ostateczny limit to 9996) ale czytelność takie planszy jest prawie zerowa.
### Options
Pozwala wybrać wielkość planszy.
Gdy wybrano pożądaną wielkość planszy należy wyjść do menu za pomocą przycisku i wystartować grę.
### Quit
Pozwala wyjść z programu.

## Modułu programu
### Callbacks.h Callbacks.c
Różnego rodzaju funkcje wywoływane przez gtk które obsługują przyciski i kliknięcia myszy.
### Draw.h. Draw.c
Funkca rysująca plansze
### Board.h Board.c
Strukura danych przechowująca dane gry.
### Logic.h Logic.c
Funkcje użyteczności jak i funkcje opisujące zasady gry.
