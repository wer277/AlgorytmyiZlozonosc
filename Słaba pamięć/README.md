# Treść zadania
Funkcjonariusze służb pomagający w przedszkolach mają problem z zapamiętywaniem imion i nazwisk swoich podopiecznych. Sprawy nie ułatwia, że w jednej grupie może być 15 Kubów i czwórka dzieci o nazwisku Nowak. Siłą oderwani od radiowozów (wozów strażackich itp.) funkcjonariusze z podziwem patrzą na doświadczone przedszkolanki, które rozróżniają Jana Jakuba Bisa-Lisa od Jana Jakuba Lisa-Bisa. Dobrze, że w całym przedszkolu nie ma dzieci które mają te same imiona i nazwiska.

Jeden z funkcjonariuszy postanowił napisać bazę dzieci umożliwiającą wyszukiwanie zarówno po imionach jak i nazwiskach

### Wejście:
W pierwszej linii wejścia program otrzymuje liczbę n oznaczającą liczbę operacji na bazie a następnie n opisów operacji z poniższej listy

d – dodanie do bazy nowego dziecka. W kolejnych dwóch liniach będą znajdowały się Imiona oraz nazwiska danego dziecka
i – wypisanie w osobnych liniach nazwisk dzieci noszących podane imię. Imię zostanie podane w kolejnej linii wejścia. Nazwiska należy wypisywać w kolejności ich dodawania do bazy.
n– wypisanie w osobnych liniach imion dzieci noszących podane nazwisko. Nazwisko zostanie podane w kolejnej linii. Imiona należy wypisywać w kolejności dodawania do bazy.
1<=n<=2000000

### Wyjście:
Na standardowym wyjściu program powinien wypisać efekty działania operacji i i n. W przypadku gdy w bazie nie ma dziecka o podanym imieniu (operacja i) lub nazwisku (operacja n) program nie powinien niczego wypisać.

### Przykładowe wejście:

6
d

Jan Kanty

Nowak

d

Elwira

Kowalska

d

Jan Kanty

Owanty

i 

Jan Kanty

n

Kowalska

n

Nowak

### Przykładowe wyjście:

Nowak

Owanty

Elwira

Jan Kanty

Uwaga:
Zadanie ma zostać rozwiązane przy pomocy samodzielnie zaimplementowanych drzew splay.
