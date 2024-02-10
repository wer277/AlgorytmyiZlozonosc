#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Dane{\
    int nr_legitymacji, liczba_punktow;

    Dane(int nr_legitymacji = 0, int liczba_punktow = 0): nr_legitymacji(nr_legitymacji), liczba_punktow(liczba_punktow){}

    bool operator > (const Dane &other) const{
        return liczba_punktow > other.liczba_punktow;
    }
    bool operator < (const Dane &other) const{
        return liczba_punktow < other.liczba_punktow;
    }
    bool operator >= (const Dane &other) const{
        return liczba_punktow >= other.liczba_punktow;
    }
    bool operator <= (const Dane &other) const{
        return liczba_punktow <= other.liczba_punktow;
    }

    bool operator == (const Dane &other) const{
        return liczba_punktow == other.liczba_punktow;
    }
};

void swap(Dane *a, Dane *b){
    Dane temp = *a;
    *a = *b;
    *b = temp;
}

int pomQuickSort(Dane *tab, int s, int n) {
    int index = s + rand() % n; // Losowy pivot
    swap(tab[index], tab[s + n - 1]); // Zamiana z ostatnim elementem
    Dane pivot = tab[s + n - 1];
    int i = s - 1;

    for(int j = s; j < s + n - 1; j++) {
        if(tab[j] < pivot) {
            i++;
            swap(tab[i], tab[j]);
        }
    }
    swap(tab[i + 1], tab[s + n - 1]);
    return i + 1;
}

void quickSort(Dane *tab, int s, int n) {
    if (n <= 1) return; // Warunek bazowy

    int pivotIndex = pomQuickSort(tab, s, n);
    quickSort(tab, s, pivotIndex - s); // Sortowanie lewej podtablicy
    quickSort(tab, pivotIndex + 1, s + n - pivotIndex - 1); // Sortowanie prawej podtablicy
}

void insertioSort(Dane *tab, int s, int n){
    for(int i = s+1; i<=n; i++){
        Dane key = tab[i];
        int j = i - 1;
        
        while(j >= s && tab[j] > key){
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = key;
    }
}

int main() {
    Dane dane[] = {
            Dane(1, 45),
            Dane(2, 55),
            Dane(3, 35),
            Dane(4, 25),
            Dane(5, 65),
            Dane(6, 75),
            Dane(7, 85),
            Dane(8, 15),
            Dane(9, 95),
            Dane(10, 5)
    };
    int n = sizeof(dane) / sizeof(dane[0]);

    // Wywołanie quickSort
    quickSort(dane, 0, n);

    // Wyświetlanie posortowanych danych
    for (int i = 0; i < n; i++) {
        std::cout << "Nr legitymacji: " << dane[i].nr_legitymacji << ", Liczba punktów: " << dane[i].liczba_punktow << std::endl;
    }
    return 0;
}
