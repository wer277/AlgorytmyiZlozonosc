# Treść zadania
Eksperci Ministerstwa Postępu choć sami nie potrafią programować, przeczytali kilka książek o programowaniu (bez zrozumienia) i nauczyli się nazw kilku pojęć. Tak przygotowani uznali, że przedszkolaki muszą się koniecznie uczyć programowania obiektowego w C++ oraz tworzenia w tym języku szablonów. To ich zdaniem ma przygotować przedszkolaki na wyzwania gospodarki przyszłości i Internetu 15.0.

Teraz wysłani do ratowania sytuacji w przedszkolach funkcjonariusze służb mundurowych głowią sie jakie zadanie zadać do domu przedszkolakom, aby ich rodzice zdołali je odrobić. Po długich naradach na forum służbowym ustalono, że jako zadanie zostanie zadane napisanie uproszczonej wersji STL-oewgo vectora.

Ustalono, że należy zaimplementować szablon klasy, którego parametrem ma być typ elementów przechowywanych w klasie. Szablon klasy powinien udostępniać następujące metody:

Bezargumentowy konstruktor alokujący dziesięcioelementową tablicę.
size() zwracającą liczbę przechowywanych elementów.
push_back dodającą podany w argumencie element na koniec listy (w razie takiej potrzeby metoda powinna zaalokować odpowiednią ilość pamięć).
Przeciążony operator [ ] umożliwiający dostęp do elementów listy na podstawie ich indeksu (pozycji/numeru w liście).
Ponadto klasa powinna zostać tak zaimplementowana aby możliwe było przeglądanie jej elementów pętlą for po zakresie.
Napisane przez rodziców przedszkolaków szablony postanowiono przetestować w programie odwracającym kolejność wczytanej listy.

### Wejście

Na standardowym wejściu program otrzyma ciąg dodatnich liczb całkowitych zakończony liczbą 0. Wszystkie wczytywane liczby mieszczą się w typie unsigned int.


### Wyjście

Program powinien na standardowym wyjściu wypisać wczytane wartości (bez zera) w kolejności odwrotnej od kolejności wczytywania.

### Przykład Wejście
1

2

3

5

4

6

0

### Wyjście

6 4 5 3 2 1 

Uwaga:
W programie należy zaimplementować szablon wektor w taki sposób aby wszystkie operacje działały w zamortyzowanym czasie stałym.

Magiczna linijka: ios_base::sync_with_stdio(false);
