Sortowanie funkcjonariuszy
Eksperci z Ministerstwa Postępu nie przewidzieli, jak wielkim wyzwaniem organizacyjnym jest wprowadzenie zajęć z programowania do przedszkoli. Największym problemem okazało się znalezienie nauczycieli będących w stanie uczyć programowania. Nie łatwo jest bowiem znaleźć informatyków chcących pracować za minimalną krajową. Próbowano dokształcać z programowania nauczycieli przedszkolnych, ale, poza niewielkimi wyjątkami, gdy tylko ktoś nauczył się programować od razu rzucał pracę w przedszkolu i szedł do biznesu. W obliczu potencjalnej klęski nagłośnionego w mediach programu Ministerstwo zdecydowało się na wysłanie do przedszkoli funkcjonariuszy służb mundurowych. Wcześniej jednak przeprowadzono test mający określić, którzy funkcjonariusze mają największe predyspozycje do uczenia przedszkolaków programowania. W wyniku testu uzyskano gigantyczne ilości danych, które teraz trzeba uporządkować. Pierwszym zadaniem jest posortowanie listy zawierającej pary: numer legitymacji służbowej funkcjonariusza, liczba punktów zdobytych przez danego funkcjonariusza.

Wejście
Program na standardowym wejściu otrzyma liczby n, p, k oraz c, a następnie n par liczb całkowitych l, w oznaczających numery legitymacji służbowych oraz liczby punktów zdobyte przez poszczególnych funkcjonariuszy (p<=w<=k). Zarówno liczba zdobytych punktów jak i numer legitymacji służbowej może się powtarzać (każdy z funkcjonariuszy mógł podejść do testu wielokrotnie).

1 <= n <= 3000000
0 <= p <= k <= 1000000

Wyjście
Program powinien posortować wczytaną listę funkcjonariuszy niemalejąco względem liczby zdobytych punktów oraz wypisać na standardowym wyjściu elementy posortowanej listy rozdzielone pojedynczymi odstępami. Numery legitymacji, którym odpowiadają te same wartości zdobytych punktów powinny być wypisane w oryginalnej kolejności. W zależności od wczytanej wartości c program powinien wypisać tylko same numery legitymacji (dla c równego 0) lub same wartości zdobytych punktów (dla c równego 1).

Przykład 1
Wejście

Copy code
4 0 100 0
12345 100
23456 0
34567 90
23456 90
Wyjście

Copy code
23456 34567 23456 12345
Przykład 2
Wejście

yaml
Copy code
4 0 1000 1
12345 100
23456 0
34567 90
23456 90
Wyjście

Copy code
0 90 90 100
Uwaga: Program powinien opierać się na samodzielnej implementacji algorytmów introsort, timsort oraz sortowania przez zliczanie (uruchamianych w zależności od parametrów danych wejściowych).

Magiczna linijka: ios_base::sync_with_stdio(false);
