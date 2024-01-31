# Treść zadania
Ulubioną formą spędzania czasu przedszkolaków jest zabawa w parku, który jest świetnym miejscem do gry w berka ze względu na liczne rozdroża, w których można zgubić goniącego. Dzieci odwiedzają go wraz z wychowawczynią każdego słonecznego dnia. W tymże parku, z okazji ogólnoświatowego dnia aktywności fizycznej, dyrekcja przedszkola postanowiła zorganizować bieg na orientację w terenie dla podopiecznych. Bieg ma rozpocząć się od fontanny w samym centrum parku. Problemem jest jednak ustalenie miejsca finiszu, które nie może być zbyt daleko, tak by dzieci były w stanie przebiec cały dystans bez nadmiernego zmęczenia, ani zbyt blisko, by nie rozczarować dzieci.

Każdy z nauczycieli zaproponował inny punkt na mapie parku, który będzie najlepszym miejscem na metę. Pani dyrektor zleciła zaprzyjaźnionemu informatykowi znalezienie najkrótszej możliwej ścieżki od fontanny do każdego z zaproponowanych miejsc i poprosiła o przedstawienie jej raportu na podstawie, którego będzie mogła podjąć decyzję. Jedna z wychowawczyń przedszkolaków zwróciła uwagę, iż w jej grupie część dzieci jest niezwykle energiczna, więc z pewnością poradzi sobie z biegiem. Niestety druga część dzieci nie jest tak sprawna fizycznie, ale za to lepiej radzi sobie z łamigłówkami. Nauczycielka zaproponowała, by formuła biegu została lekko zmodyfikowana, tak by na niektórych ścieżkach oznaczonych niebieskimi wstążeczkami znajdowały się zadanie logiczne, za których rozwiązanie od łącznego czasu biegu odejmowana jest określona liczba minut w zależności od poziomu skomplikowania zagadki.

Zadanie polega na znalezieniu najkrótszej ścieżki w grafie skierowanym od zadanego wierzchołka do każdego innego wierzchołka. Wierzchołki reprezentują różne miejsca w parku, wagi krawędzi zaś średni czas w minutach potrzebny na pokonanie trasy między dwoma punktami na mapie parku. Na krawędziach, które reprezentują ścieżki z łamigłówkami wagi oznaczają ([średni czas na przebiegnięcie odcinka] -[trudność łamigłówki (od 1 do 10)]) minut.

### Wejście

Program na standardowym wejściu otrzyma liczby n - ilość wierzchołków, m - ilość krawędzi. Następnie program otrzyma k trójek liczb całkowitych postaci (wierzolek_początkowy wierzchołek_koncowy waga_krawedzi). Każdy wierzchołek ma być ponumerowany od 0 do n-1. Po wprowadzeniu krawędzi program ma otrzymać na standardowym wejściu numer wierzchołka startowego.

0 <= m <= 1400000
1 <= n <= 100000
-9 <= waga_krawedzi <= 10


### Wyjście

Program powinien na standardowym wyjściu wypisać najkrótsze ścieżki w grafie od wierzchołka startowego, do kolejno wszystkich pozostałych wierzchołków. Jeżeli, do któregoś z wierzchołków nie prowadzi żadna ścieżka program powinien zwrócić nieskończoność (w programie największa liczba całkowita = 2147483647). Jeżeli w grafie znajduje się ujemny cykl, program powinien wyświetlić "Graf zawiera ujemny cykl!".

### Przykład Wejście
 
6 11 

0 1 5

1 3 3

1 4 9

2 0 3

2 1 -4

3 4 3 

3 5 2 

4 2 -1 

4 5 -5 

5 2 8 

5 0 9 

0

### Wyjście

0: 0 

1: 5

2: 10

3: 8

4: 11

5: 6 

Uwaga:
W programie należy zaimplementować algorytmy Dijkstry i Bellmana-Forda i użyć właściwego w zależności od danych wejściowych (czyli czy w grafie są krawędzie o ujemnych wagach). Algorytm Dijkstry powinien zostać zaimplementowany z wykorzystaniem kopców Fibonacciego.

Magiczna linijka: ios_base::sync_with_stdio(false);
