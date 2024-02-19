Napisz prgoram, który wczytuje ze standardowego wejścia graf skierowany bez cykli o ujemnej sumie wag i wypisuje na standardowym wyjściu parę najbardziej odległych od siebie wierzchołków.

Wejście

Program na standardowym wejściu otrzyma liczby n - ilość wierzchołków, m - ilość krawędzi. Następnie program otrzyma m trójek liczb całkowitych postaci (wierzolek_początkowy wierzchołek_koncowy waga_krawedzi). Wierzchołki są ponumerowane od 0 do n-1. Wagi krawędzi oraz odległości pomiędzy wierzchołkami mieszczą się w typie long long int

1 <= m <= 1000000
1 <= n <= 1000


Wyjście

Program powinien na standardowym wyjściu wypisać parę wierzchołków a,b takich, że najkrótsza ścieżka z a do b jest najdłuższa spośród najkrótszych ścieżek łączących wierzchołki w grafie. Uwaga graf jest skierowany a więc kolejność wierzchołków ma znaczenie. W przypadku wielu par o takiej samej długości najkrótszej ścieżki program powinien wypisać parę pierwszą w porządku leksykograficznym. W przypadku grafów niespójnych należy wypisać parę wierzchołków pomiędzy, którymi nie ma ścieżki

Przykład 1

Wejście
 
4 4 
1 2 5
2 3 5
3 1 -3
0 2 1

Wyjście
1 0 
Przykład 2

Wejście
 
4 5 
1 2 5
2 3 5
3 1 -3
0 2 10
2 0 1 

Wyjście
0 3 
Uwaga:
Magiczna linijka: ios_base::sync_with_stdio(false);
