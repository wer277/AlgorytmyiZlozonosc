#include <iostream>

using namespace std;

class Vector{
public:
    unsigned int *tab; // Tablica przechowująca elementy
    int maxRozmiar = 10; // Maksymalny rozmiar tablicy
    int licznik = 0; // Licznik przechowujący aktualną liczbę elementów

    // Konstruktor klasy Vector. Złożoność czasowa: O(1)
    Vector(){
        tab = new unsigned int [10]; // Inicjalizacja tablicy o rozmiarze 10
    }

    // Funkcja dodająca element na koniec tablicy. Złożoność czasowa: O(1) średnio, w przypadku realokacji O(n)
    void push_back(unsigned int dane){
        if(licznik < maxRozmiar){ // Jeśli jest jeszcze miejsce w tablicy
            if(dane != 0){ // Jeśli dane nie są zerem
                tab[licznik] = dane; // Dodajemy dane na koniec tablicy
                licznik++; // Zwiększamy licznik
            }
        } else { // Jeśli tablica jest pełna
            if (maxRozmiar == 0) maxRozmiar = 1; // Jeśli maxRozmiar jest zerem, ustawiamy go na 1
            else maxRozmiar *= 2; // W przeciwnym razie podwajamy maxRozmiar

            unsigned int *nowaTablica = new unsigned int [maxRozmiar]; // Tworzymy nową tablicę o podwojonym rozmiarze

            for (int i = 0; i < licznik; ++i) { // Przenosimy elementy ze starej tablicy do nowej
                nowaTablica[i] = tab[i];
            }

            delete[] tab; // Usuwamy starą tablicę
            tab = nowaTablica; // Przypisujemy nową tablicę do wskaźnika tab

            tab[licznik] = dane; // Dodajemy dane na koniec nowej tablicy
            licznik++; // Zwiększamy licznik
        }
    }

    // Funkcja zwracająca rozmiar tablicy. Złożoność czasowa: O(1)
    int size(){
        return licznik;
    }

    // Operator indeksowania. Złożoność czasowa: O(1)
    unsigned int& operator {
        if (index >= 0 && index < licznik) { // Jeśli indeks jest prawidłowy
            return tab[index]; // Zwracamy element o danym indeksie
        } else { // W przeciwnym razie
            cout << 0; // Wyświetlamy 0
        }
    }
};

int main() {
    unsigned int dane = 2147483647; // Inicjalizacja danych
    Vector vector; // Tworzenie obiektu klasy Vector
    while (dane != 0) { // Dopóki dane nie są zerem
        std::cin >> dane; // Wczytujemy dane
        vector.push_back(dane); // Dodajemy dane do wektora
    }

    for (int i = vector.size() - 1; i >= 0; --i) { // Dla każdego elementu wektora
        std::cout << vector.tab[i] << " "; // Wyświetlamy element
    }
    std::cout << std::endl; // Wyświetlamy nową linię

    return 0; // Zwracamy 0
}
