# Lab04

### output
 > Usage po wpisaniu polecenia z parametrem --help

Klasa do macierzy 2d wartości typu double. **+ cmake project structure**

Opis poszczególnych funkcji:

**kontruktory**: w sumie 4

    dwuargumentowy n, m, dynamiczna alokacja ciągłej pamięci

    jednoargumentowy n, deleguje na konstruktor dwuargumentowy

    jednoargumentowy z pliku, wczytuje dane z pliku, który został wcześniej utworzony

    kopujący, wymagany ze względu na dynamiczną pamięć

**destruktor**: ze względu na dynamiczną pamięć

**get/set**: prosty getter i setter ( tak samo z cols i rows )

**addMatrices**: dodaje macierze o tych samych rozmiarach, w przeciwnym wypadku zwraca pierwszą

**subtractMatrices**: jw. tylko odejmuje

**multiplyMatrices**: mnoży macierze wedle zasad algebry, warunki wymiarów muszą zostać spełnione, inaczej zwraca pierwszą

**print**: wypisuje macierz

**store**: zapisuje dane do pliku

###

**compile\.sh:**\
skrypt do kompilacji (CMake, Make), usage po odpaleniu z paramerem --help

###

**Autor:** Albert Mouhoubi
