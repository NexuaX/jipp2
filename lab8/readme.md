# Lab08

### output
 > Usage po wpisaniu polecenia z parametrem --help

Problem pięciu filozofów, wykonany za pomocą bibliotek z C++

    <thread> <mutex> <atomic> <conditional_variable>

1. thread : do utworzenia wątków filozofów
2. mutex : jako binarne semafory ( w tym wypadku widelce ) oraz semafor lokaja 
3. atomic : zmienna z zapewnieniem synchornizacji ( w tym wypadku lcznik filozofów aktualnie przy stole )
4. conditional_variable : obiekt do zatrzymywania i wznawiania wątków ( w połączeniu z lokajem i zmienną atomic tworzą semafor niebinarny )

##

**compile\.sh:**\
skrypt do kompilacji (CMake, Make), usage po odpaleniu z paramerem --help

###

**Autor:** Albert Mouhoubi
