#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Dane{
    int nr_leg;
    int liczba_punktow;


    bool operator > (const Dane &other) const{
        return liczba_punktow > other.liczba_punktow;
    }

    bool operator < (const Dane &other) const{
        return liczba_punktow < other.liczba_punktow;
    }

    bool operator <= (const Dane &other) const{
        return liczba_punktow <= other.liczba_punktow;
    }

    bool operator >= (const Dane &other) const{
        return liczba_punktow >= other.liczba_punktow;
    }

    bool operator == (const Dane &other) const{
        return liczba_punktow == other.liczba_punktow;
    }
};

void swap (Dane *a, Dane *b){
    Dane pom = *a;
    *a = *b;
    *b = pom;
}

int pomQuickSort(Dane *tab, int s, int n){
    int index = s + rand() % n;
    swap(tab[index], tab[s+n-1]);
    Dane pivot = tab[s+n-1];
    int i = s-1;

    for(int j = s; j<s+n-1;j++){
        if(tab[j] < pivot){
            i++;
            swap(tab[i], tab[j]);
        }
    }
    swap(tab[i+1], tab[s+n-1]);
    return i+1;
}

void quickSort(Dane *tab, int s, int n){
    if(n<=1) return;
    int pivot = pomQuickSort(tab,s,n);
    quickSort(tab,s,pivot-s);
    quickSort(tab,pivot+1,s+n-pivot-1);
}

void insertioSort(Dane *tab, int s, int n){
    for(int i = s+1; i<=n; i++){
        Dane key = tab[i];
        int j = i - 1;
        while(j>=s && tab[j]>key){
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = key;
    }
}

void countingSort(Dane *tab, int maxValue, int n){
    int *countTab;
    int size = maxValue+1;
    countTab = new int[size]();
    for(int i = 0; i<n;i++){
        countTab[tab[i].liczba_punktow]++;
    }
    for(int i = 1; i<size;i++){
        countTab[i] += countTab[i-1];
    }

    Dane *sortedTab = new Dane[n];
    for(int i = n-1; i>=0; i--){
        int pom = countTab[tab[i].liczba_punktow]-1;
        sortedTab[pom] = tab[i];
        countTab[tab[i].liczba_punktow]--;
    }
    for(int i = 0; i<n; i++)
        tab[i] = sortedTab[i];

    delete [] countTab;
    delete [] sortedTab;
}

void downHeap(Dane *tab, int s, int n){
    int largest = s;
    int left = 2*s+1;
    int right = 2*s+2;

    if(left<n && tab[left]>tab[largest])
        largest = left;

    if(right<n && tab[right]>tab[largest])
        largest = right;

    if(largest != s){
        swap(tab[s], tab[largest]);
        downHeap(tab,largest,n);
    }
}

void buildHeap(Dane *tab, int n){
    for(int i = n/2-1; i>=0; i--){
        downHeap(tab,i,n);
    }
}

void heapSort(Dane *tab, int n){
    buildHeap(tab,n);
    for(int i = n-1; i>0; i--){
        swap(tab[0], tab[i]);
        downHeap(tab,0,i);
    }
}

int main() {
//    Dane dane[] = {
//            Dane(1, 45),
//            Dane(2, 55),
//            Dane(3, 35),
//            Dane(4, 25),
//            Dane(5, 65),
//            Dane(6, 75),
//            Dane(7, 85),
//            Dane(8, 15),
//            Dane(9, 95),
//            Dane(10, 5)
//    };
//   int n = sizeof(dane) / sizeof(dane[0]);
//    insertioSort(dane, 0, n-1);
//
//    // Wywołanie quickSort
//    quickSort(dane, 0, n);
//
    // Wyświetlanie posortowanych danych
//    for (int i = 0; i < n; i++) {
//        std::cout << "Nr legitymacji: " << dane[i].nr_leg << ", Liczba punktów: " << dane[i].liczba_punktow << std::endl;
//    }
    return 0;
}
