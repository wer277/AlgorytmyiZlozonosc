#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

struct Dane {
    int nr_legitymacji;          //Numer legitymacji służbowej
    int liczba_punktow;          //Liczba punktow

    Dane(int nr_legitymacji_val = 0, int liczba_punktow_val = 0)
            : nr_legitymacji(nr_legitymacji_val), liczba_punktow(liczba_punktow_val) {}

    bool operator > (const Dane& other) const {
        return liczba_punktow > other.liczba_punktow;
    }

    bool operator < (const Dane& other) const {
        return liczba_punktow < other.liczba_punktow;
    }

    bool operator >= (const Dane& other) const {
        return liczba_punktow >= other.liczba_punktow;
    }

    bool operator <= (const Dane& other) const {
        return liczba_punktow <= other.liczba_punktow;
    }

    bool operator == (const Dane& other) const {
        return liczba_punktow == other.liczba_punktow;
    }
};

struct DaneI {
    int liczba_punktow;          //Liczba punktow
    
    bool operator > (const DaneI& other) const {
        return liczba_punktow > other.liczba_punktow;
    }

    bool operator < (const DaneI& other) const {
        return liczba_punktow < other.liczba_punktow;
    }

    bool operator >= (const DaneI& other) const {
        return liczba_punktow >= other.liczba_punktow;
    }

    bool operator <= (const DaneI& other) const {
        return liczba_punktow <= other.liczba_punktow;
    }

    bool operator == (const DaneI& other) const {
        return liczba_punktow == other.liczba_punktow;
    }
};

void swap(Dane *a, Dane *b){
    Dane pom = *a;
    *a = *b;
    *b = pom;
}

int pomQuickSort(Dane *tab, int s, int n){
    int index = s + rand() % n; // Losowy pivot
    swap(tab[index], tab[s + n - 1]); // Zamiana z ostatnim elementem
    Dane pivot = tab[s + n - 1];
    int i = s - 1;

    for(int j = s; j < s + n - 1; j++){
        if(tab[j] < pivot){
            i++;
            swap(tab[i], tab[j]);
        }
    }
    swap(tab[i + 1], tab[s + n - 1]);
    return i + 1;
}

int pomQuickSort(DaneI *tab, int s, int n){
    int index = s + rand() % n; // Losowy pivot
    swap(tab[index], tab[s + n - 1]); // Zamiana z ostatnim elementem
    DaneI pivot = tab[s + n - 1];
    int i = s - 1;

    for(int j = s; j < s + n - 1; j++){
        if(tab[j] < pivot){
            i++;
            swap(tab[i], tab[j]);
        }
    }
    swap(tab[i + 1], tab[s + n - 1]);
    return i + 1;
}

void insertionSort(Dane *tab, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Dane key = tab[i];
        int j = i - 1;
        while (j >= left && tab[j] > key) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = key;
    }
}

void insertionSortI(DaneI *tab, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        DaneI key = tab[i];
        int j = i - 1;
        while (j >= left && tab[j] > key) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = key;
    }
}

void downheap(Dane *arr_val, int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr_val[left] > arr_val[largest])
        largest = left;

    if (right < n && arr_val[right] > arr_val[largest])
        largest = right;

    if (largest != i) {
        swap(arr_val[i], arr_val[largest]);
        downheap(arr_val, largest, n);
    }
}

void downheap(DaneI *arr_val, int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr_val[left] > arr_val[largest])
        largest = left;

    if (right < n && arr_val[right] > arr_val[largest])
        largest = right;

    if (largest != i) {
        swap(arr_val[i], arr_val[largest]);
        downheap(arr_val, largest, n);
    }
}

void buildHeap(Dane *arr_val, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        downheap(arr_val, i, n);
    }
}

void buildHeap(DaneI *arr_val, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        downheap(arr_val, i, n);
    }
}

void heapSort(Dane *arr_val, int n) {
    buildHeap(arr_val, n);
    for (int i = n - 1; i > 0; i--) {
        swap(arr_val[0], arr_val[i]);
        downheap(arr_val, 0, i);
    }
}

void heapSort(DaneI *arr_val, int n) {
    buildHeap(arr_val, n);
    for (int i = n - 1; i > 0; i--) {
        swap(arr_val[0], arr_val[i]);
        downheap(arr_val, 0, i);
    }
}

void introSortUtil(Dane *tab, int s, int size, int depthLimit) {
    if (size < 16) {
        insertionSort(tab, s, s+size-1);
    }
    else if (depthLimit == 0) {
        heapSort(tab+s, size);
    }
    else {
        int pivot = pomQuickSort(tab, s, size);
        introSortUtil(tab, s, pivot-s, depthLimit - 1);
        introSortUtil(tab, pivot, size-(pivot-s), depthLimit - 1);
    }
}

void introSortUtil(DaneI *tab, int s, int size, int depthLimit) {
    if (size < 16) {
        insertionSortI(tab, s, s+size-1);
    }
    else if (depthLimit == 0) {
        heapSort(tab+s, size);
    }
    else {
        int pivot = pomQuickSort(tab, s, size);
        introSortUtil(tab, s, pivot-s, depthLimit - 1);
        introSortUtil(tab, pivot, size-(pivot-s), depthLimit - 1);
    }
}

void introSort(Dane *tab, int s, int n) {
    int depthLimit = 2 * static_cast<int>(std::log2(n));
    introSortUtil(tab, s, n, depthLimit);
}

void introSortI(DaneI *tab, int s, int n) {
    int depthLimit = 2 * static_cast<int>(std::log2(n));
    introSortUtil(tab, s, n, depthLimit);
}

void countingSort(Dane *tab, int maxValue, int n){
    int *countTab;
    int size = maxValue + 1;
    countTab = new int[size]();

    for (int i = 0; i < n; i++) {
        countTab[tab[i].liczba_punktow]++;
    }

    for (int i = 1; i < size; i++) {
        countTab[i] += countTab[i - 1];
    }

    Dane *sortedTab = new Dane[n];

    for (int i = n - 1; i >= 0; i--) {
        int pom = countTab[tab[i].liczba_punktow] - 1;
        sortedTab[pom] = tab[i];
        countTab[tab[i].liczba_punktow]--;
    }

    for (int i = 0; i < n; i++) {
        tab[i] = sortedTab[i];
    }

//    for(int i = 0; i < n; i++)
//        cout << tab[i].nr_legitymacji << " : " << tab[i].liczba_punktow<<endl;

    delete[] countTab;
    delete[] sortedTab;
}

void countingSort(DaneI *tab, int maxValue, int n){
    int *countTab;
    int size = maxValue + 1;
    countTab = new int[size]();

    for (int i = 0; i < n; i++) {
        countTab[tab[i].liczba_punktow]++;
    }

    for (int i = 1; i < size; i++) {
        countTab[i] += countTab[i - 1];
    }

    DaneI *sortedTab = new DaneI[n];

    for (int i = n - 1; i >= 0; i--) {
        int pom = countTab[tab[i].liczba_punktow] - 1;
        sortedTab[pom] = tab[i];
        countTab[tab[i].liczba_punktow]--;
    }

    for (int i = 0; i < n; i++) {
        tab[i] = sortedTab[i];
    }

    delete[] countTab;
    delete[] sortedTab;
}

const int RUN = 32;

void merge(Dane *tab, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Dane *L = new Dane[n1];
    Dane *R = new Dane[n2];

    for (int i = 0; i < n1; i++)
        L[i] = tab[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = tab[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            tab[k] = L[i];
            i++;
        } else {
            tab[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tab[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        tab[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void timSortMerge(Dane *tab, int n) {
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
            if(mid < right) {
                merge(tab, left, mid, right);
            }
        }
    }
}

void timSort(Dane *tab, int n) {
    for (int i = 0; i < n; i += RUN) {
        insertionSort(tab, i, std::min((i + RUN - 1), (n - 1)));
    }
    timSortMerge(tab, n);
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, p, k, c, maxValue = 0;
    cin >> n >> p >> k >> c;
    if(c == 0){
        auto* tab = new Dane[n]();

        for (int i = 0; i < n; i++){
            cin >> tab[i].nr_legitymacji >> tab[i].liczba_punktow;
            if(maxValue < tab[i].liczba_punktow)
                maxValue = tab[i].liczba_punktow;
        }

        if(k-p < 500){
            countingSort(tab, maxValue, n);
        } else{
            if(c == 0){
                timSort(tab, n);
            } else{
                introSort(tab, 0, n);
            }
        }

        // Wyświetlanie wyników
        if (c == 1) {
            // Sortowanie według liczby punktów
            for (int i = 0; i < n; i++) {
                cout << tab[i].liczba_punktow << " ";
            }
        } else if(c == 0){

            // Sortowanie według numeru legitymacji
            for (int i = 0; i < n; i++) {
                cout << tab[i].nr_legitymacji << " ";
            }
        }
//    for (int i = 0; i < n; i++) {
//        cout << tab[i].nr_legitymacji << " " <<  tab[i].liczba_punktow << endl;
//    }
        delete [] tab;
        return 0;
    } else{
        auto* tab = new DaneI[n]();

        for (int i = 0; i < n; i++){
            cin >> tab[i].liczba_punktow >> tab[i].liczba_punktow;
            if(maxValue < tab[i].liczba_punktow)
                maxValue = tab[i].liczba_punktow;
        }

        if(k-p < 500){
            countingSort(tab, maxValue, n);
        } else{
            introSortI(tab, 0, n);
        }

        // Wyświetlanie wyników
        if (c == 1) {
            // Sortowanie według liczby punktów
            for (int i = 0; i < n; i++) {
                cout << tab[i].liczba_punktow << " ";
            }
        }
        delete [] tab;
        return 0;
    }
    
}
