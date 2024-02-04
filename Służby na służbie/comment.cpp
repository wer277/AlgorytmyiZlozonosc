#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

/*Dane i DaneI różnią się od siebie tym że jeden ma nrleg drugi tylko punkty. Spowodowane jest to tym, że gdy we wczytwanych danych użyty jest parametr
 c=1 numery legitymaji nie są nam wcale potrzebne podczas sortowania. Dzięki temu zaoszcżedzamy pamięć.
Druga struktura danych była użyta tylko po to by przejść test, w którym wyrzucało przekroczenie pamięci
Bool operatory w każdej strukturze, są zdefiniowane po to by w łatwy sposób móc porównywać liczbę punktów podczas sortowania*/


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

/*Funkcja zamienia miejscami dwa elementy struktury Dane*/

void swap(Dane *a, Dane *b){    //O(1)
    Dane pom = *a;
    *a = *b;
    *b = pom;
}

/* Funkcja ta odpoiwada za partycjonowanie tablicy w funkcji Quicksort. Wybiera losowo pivot, a następnie dzielą tablicę na dwie części:
 elementy mniejsze od pivota i większe lub równe pivotowi.*/

int pomQuickSort(Dane *tab, int s, int n){      //O(n)
    int index = s + rand() % n; // Wybieramy losowy indeks jako pivot
    swap(tab[index], tab[s + n - 1]); // Zamieniamy pivot z ostatnim elementem
    Dane pivot = tab[s + n - 1]; // Ustawiamy pivot na ostatni element
    int i = s - 1; // Inicjalizujemy indeks mniejszego elementu

    for(int j = s; j < s + n - 1; j++){ // Przechodzimy przez elementy
        if(tab[j] < pivot){ // Jeśli element jest mniejszy od pivot
            i++; // Zwiększamy indeks mniejszego elementu
            swap(tab[i], tab[j]); // Zamieniamy go z elementem na pozycji i
        }
    }
    swap(tab[i + 1], tab[s + n - 1]); // Przesuwamy pivot na właściwe miejsce
    return i + 1; // Zwracamy indeks pivotu
}


int pomQuickSort(DaneI *tab, int s, int n){     //O(n)
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

/*Implementują algorytm sortowania przez wstawianie dla tablicy obiektów typu */
void insertionSort(Dane *tab, int left, int right) { //najlepsza O(n) najgorsza O(n^2)
    for (int i = left + 1; i <= right; i++) { // Iterujemy przez elementy od drugiego do ostatniego
        Dane key = tab[i]; // Wybieramy element do wstawienia
        int j = i - 1; // Rozpoczynamy porównywanie z elementem poprzedzającym
        while (j >= left && tab[j] > key) { // Przesuwamy elementy większe od klucza o jedną pozycję do przodu
            tab[j + 1] = tab[j]; // Przesuwamy element
            j--; // Przechodzimy do następnego elementu
        }
        tab[j + 1] = key; // Wstawiamy klucz na odpowiednie miejsce
    }
}


void insertionSortI(DaneI *tab, int left, int right) { //najlepsza O(n) najgorsza O(n^2)
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

/*Służą do utworzenia kopca, przenosząc większe elementy w górę kopca.*/
void downheap(Dane *arr_val, int i, int n) {        //O(log n)
    int largest = i; // Ustawiamy największy element jako korzeń
    int left = 2 * i + 1; // Indeks lewego dziecka
    int right = 2 * i + 2; // Indeks prawego dziecka

    // Jeśli lewe dziecko jest większe niż korzeń
    if (left < n && arr_val[left] > arr_val[largest])
        largest = left;

    // Jeśli prawe dziecko jest większe niż dotychczas największy
    if (right < n && arr_val[right] > arr_val[largest])
        largest = right;

    // Jeśli największy element nie jest korzeniem
    if (largest != i) {
        swap(arr_val[i], arr_val[largest]); // Zamieniamy korzeń z największym
        downheap(arr_val, largest, n); // Rekurencyjnie naprawiamy poddrzewo
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

/*Budują kopiec z tablicy elementów.*/
void buildHeap(Dane *arr_val, int n) { // O(n)
    for (int i = n / 2 - 1; i >= 0; i--) { // Iterujemy od ostatniego węzła, który nie jest liściem do korzenia
        downheap(arr_val, i, n); // Wywołujemy funkcję downheap, aby utworzyć podkopiec z korzeniem w i
    }
}


void buildHeap(DaneI *arr_val, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        downheap(arr_val, i, n);
    }
}

/*Implementują sortowanie przez kopcowanie.*/
void heapSort(Dane *arr_val, int n) { //O(n log n)
    buildHeap(arr_val, n); // Budujemy kopiec z nieposortowanej tablicy

    // Jeden po drugim wyjmujemy elementy z kopca
    for (int i = n - 1; i > 0; i--) {
        // Przenosimy obecny korzeń do końca
        swap(arr_val[0], arr_val[i]);

        // Wywołujemy funkcję downheap na zmniejszonym kopcu
        downheap(arr_val, 0, i);
    }
}

/*Są to pomocnicze funkcje dla algorytmu IntroSort, który jest hybrydą QuickSort, HeapSort i InsertionSort.
 Wykorzystuje różne algorytmy w zależności od rozmiaru sortowanego segmentu i głębokości rekurencji.*/

void introSortUtil(Dane *tab, int s, int size, int depthLimit) { // O(n log n)
    if (size < 16) { // Jeśli rozmiar podtablicy jest mniejszy od 16
        insertionSort(tab, s, s+size-1); // Używamy sortowania przez wstawianie
    }
    else if (depthLimit == 0) { // Jeśli osiągnięto limit głębokości rekursji
        heapSort(tab+s, size); // Używamy sortowania przez kopcowanie
    }
    else { // W przeciwnym razie
        int pivot = pomQuickSort(tab, s, size); // Wybieramy pivot za pomocą funkcji pomocniczej QuickSort
        introSortUtil(tab, s, pivot-s, depthLimit - 1); // Sortujemy elementy na lewo od pivotu
        introSortUtil(tab, pivot, size-(pivot-s), depthLimit - 1); // Sortujemy elementy na prawo od pivotu
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

/*Implementują algorytm IntroSort dla obiektów Dane i DaneI.*/

void introSort(Dane *tab, int s, int n) { // O(n log n)
    int depthLimit = 2 * static_cast<int>(std::log2(n)); // Obliczamy maksymalną głębokość rekursji
    introSortUtil(tab, s, n, depthLimit); // Wywołujemy funkcję pomocniczą introSortUtil
}


void introSortI(DaneI *tab, int s, int n) {
    int depthLimit = 2 * static_cast<int>(std::log2(n));
    introSortUtil(tab, s, n, depthLimit);
}

/*Implementuje sortowanie przez zliczanie.*/
void countingSort(Dane *tab, int maxValue, int n){ // O(n) lub O(n + k) k maksymaln wartość elementu
    int *countTab; // Tworzymy tablicę do zliczania
    int size = maxValue + 1; // Rozmiar tablicy zliczającej to maksymalna wartość + 1
    countTab = new intsize; // Inicjalizujemy tablicę zliczającą zerami

    for (int i = 0; i < n; i++) { // Dla każdego elementu w tablicy wejściowej
        countTab[tab[i].liczba_punktow]++; // Zwiększamy odpowiednią wartość w tablicy zliczającej
    }

    for (int i = 1; i < size; i++) { // Dla każdego elementu w tablicy zliczającej
        countTab[i] += countTab[i - 1]; // Dodajemy wartość poprzedniego elementu
    }

    Dane *sortedTab = new Dane[n]; // Tworzymy tablicę na posortowane elementy

    for (int i = n - 1; i >= 0; i--) { // Dla każdego elementu w tablicy wejściowej, zaczynając od końca
        int pom = countTab[tab[i].liczba_punktow] - 1; // Obliczamy indeks w tablicy posortowanej
        sortedTab[pom] = tab[i]; // Umieszczamy element w odpowiednim miejscu w tablicy posortowanej
        countTab[tab[i].liczba_punktow]--; // Zmniejszamy wartość w tablicy zliczającej
    }

    for (int i = 0; i < n; i++) { // Dla każdego elementu w tablicy posortowanej
        tab[i] = sortedTab[i]; // Kopiujemy elementy z tablicy posortowanej do tablicy wejściowej
    }

    delete[] countTab; // Usuwamy tablicę zliczającą
    delete[] sortedTab; // Usuwamy tablicę posortowaną
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

/*Łączy dwa posortowane segmenty tablicy w jedną posortowaną sekwencję. Uzywamy w tim sort merge*/
void merge(Dane *tab, int l, int m, int r) { // O(n)
    int n1 = m - l + 1; // Obliczamy rozmiar lewej podtablicy
    int n2 = r - m; // Obliczamy rozmiar prawej podtablicy

    Dane *L = new Dane[n1]; // Tworzymy lewą podtablicę
    Dane *R = new Dane[n2]; // Tworzymy prawą podtablicę

    for (int i = 0; i < n1; i++) // Kopiujemy dane do lewej podtablicy
        L[i] = tab[l + i];
    for (int j = 0; j < n2; j++) // Kopiujemy dane do prawej podtablicy
        R[j] = tab[m + 1 + j];

    int i = 0; // Inicjalizujemy indeks lewej podtablicy
    int j = 0; // Inicjalizujemy indeks prawej podtablicy
    int k = l; // Inicjalizujemy indeks scalanej tablicy

    // Scalamy podtablice
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

    // Kopiujemy pozostałe elementy lewej podtablicy, jeśli są jakieś
    while (i < n1) {
        tab[k] = L[i];
        i++;
        k++;
    }

    // Kopiujemy pozostałe elementy prawej podtablicy, jeśli są jakieś
    while (j < n2) {
        tab[k] = R[j];
        j++;
        k++;
    }

    delete[] L; // Usuwamy lewą podtablicę
    delete[] R; // Usuwamy prawą podtablicę
}


/*Łączy posortowane segmenty tablicy w większe posortowane segmenty.*/
void timSortMerge(Dane *tab, int n) { // O(n log n)
    for (int size = RUN; size < n; size = 2 * size) { // Dla każdego rozmiaru podtablicy, który jest potęgą 2
        for (int left = 0; left < n; left += 2 * size) { // Dla każdej podtablicy o danym rozmiarze
            int mid = left + size - 1; // Obliczamy środek podtablicy
            int right = std::min((left + 2 * size - 1), (n - 1)); // Obliczamy prawy koniec podtablicy
            if(mid < right) { // Jeśli środek jest mniejszy od prawego końca
                merge(tab, left, mid, right); // Scalamy dwie podtablice
            }
        }
    }
}


/*Implementuje algorytm TimSort, który jest hybrydą InsertionSort i MergeSort.*/
void timSort(Dane *tab, int n) { // O(n log n)
    for (int i = 0; i < n; i += RUN) { // Dla każdego segmentu o rozmiarze RUN
        insertionSort(tab, i, std::min((i + RUN - 1), (n - 1))); // Sortujemy segment za pomocą sortowania przez wstawianie
    }
    timSortMerge(tab, n); // Scalamy posortowane segmenty
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
