# Projekt

### output
 > Usage po wpisaniu polecenia z parametrem --help

## HRMS extended

System HRMS z obsługą z poziomu konsoli, z zapisem/wczytaniem z bazy, całkowitą edycją.

System potrzebuje pliku konfiguracyjnego conf.cfg, który tworzy przy piwerszym uruchomieniu.

```conf
DATABASE=database_filename
USER=username
PASSWORD=password
HASH=hash
```

pola `USER`, `PASSWORD` oraz `HASH` są hashowane algorytmem sha256, wszelka próba podmiany danych logowania lub hasha zostaje wykryta przez program

Plik z bazą \*.db:

* można użyć wcześniejszy (ale musi być poprawny)
* program sam stworzy i przygotuje pustą bazę

## Funkcjonaloność

### Po uruchomieniu

1. Jeżeli plik konfiguracyjny istnieje.
    * Jeżeli nie program pyta czy zainicjować plik.
    * powadawne są nazwa pliku z bazą, user i password
2. Wyślietlany jest monit o logowanie. Max 3 próby.
3. Po poprawnym zalogowaniu ładowana jest baza i jej dane.
4. Wyświeltany jest znak zachęty do wprowadzania poleceń.

### Polecenia

zbiór wszystkich poleceń:
> polecenie(liczba_podpoleceń)
```
list(3), add, delete, change(6), load, save, exit, danger_zone(4), help
```

* list : pozwala wylistować aktualnych pracowników w systemie, pracowników danego departamentu oraz płace (z możliwością sortowania)
* add : polecenie do wprowadzania nowych pracowników do systemu
* delete : polecenie do usuwania pracowników z systemu
* change : polecenie pozwala zmienić jedną właściwość pracownika na raz 
* load : wczytuje dane z bazy
* save : zapisuje aktualny stan systemu do bazy (nadpisuje wszystko)
* exit : wychodzi z systemu i programu
* help : wyświetla listę poleceń
* danger_zone : *używaj ostrożnie*, pozwala na zmianę konfiguracji (bazy, loginu, hasła) oraz na usunięcie wszytchich pracowników, wymagane potwierdzenie loginem i hasłem

Polecenia można kolejkować, tak samo jak ich konstrukcję czyli:

```
add
ID 10
Name Albert
Surname Mouhoubi
Dep_ID 10
Position Master
Salary 10000
```

Odpowiada
```
add 10 Albert Mouhoubi 10 Master 10000
```

## Budowa

Program zbudowałem w oparciu o klasy. W szczególności sama klasa HRMS jest zbudowana wedle wzorcu **Singleton**. Wszystkie klasy tj. (HRMS, User, Command, Employee) zostały napisane ręcznie. Algorytm sha256 został zapożyczony z sieci.

Projekt w strukturze prostego CMake.

W funkcji main zostały wywołane jedynie dwie funkcje. `Init` oraz `prompt` służące kolejno do inicjalizacji systemu i wyśietlenia monitu do wprowadzania komend.

#

**compile\.sh:**\
skrypt do kompilacji (CMake, Make), usage po odpaleniu z paramerem --help

###

**Autor:** Albert Mouhoubi
