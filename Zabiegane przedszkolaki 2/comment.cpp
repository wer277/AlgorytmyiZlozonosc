#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Edge { // Struktura reprezentująca krawędź w grafie
    int wierzcholek_poczatkowy; // Wierzchołek początkowy krawędzi
    int wierzcholek_koncowy; // Wierzchołek końcowy krawędzi
    int waga_krawedzi = 0; // Waga krawędzi
    int odleglosc = 0; // Odległość od źródła do wierzchołka końcowego
    bool odwiedzony = false; // Flaga odwiedzin

    Edge(int poczatkowy, int koncowy, int waga) // Konstruktor z parametrami
            : wierzcholek_poczatkowy(poczatkowy), wierzcholek_koncowy(koncowy), waga_krawedzi(waga) {}

    Edge() : wierzcholek_poczatkowy(0), wierzcholek_koncowy(0), waga_krawedzi(0.0) {} // Domyślny konstruktor

    Edge(int poczatkowy, int koncowy, int odleglosc, bool odwiedzony) // Konstruktor z parametrami
            : wierzcholek_poczatkowy(poczatkowy), wierzcholek_koncowy(koncowy), odleglosc(odleglosc), odwiedzony(odwiedzony) {}
};

struct Graf { // Struktura reprezentująca graf
    int liczba_wierzcholkow = 0;  // Liczba wierzchołków
    std::vector<Edge> edges; // Krawędzie grafu
    vector<vector<pair<int, int>>> listaSasiedztwa; // Lista sąsiedztwa dla grafu

    Graf() : liczba_wierzcholkow(0), listaSasiedztwa(0) {} // Domyślny konstruktor
    Graf(int w) : liczba_wierzcholkow(w), listaSasiedztwa(w) {} // Konstruktor z parametrami

    void dodajKrawedz(int poczatkowy, int koncowy, int waga) { // Metoda dodająca krawędź do grafu
        listaSasiedztwa[poczatkowy].push_back(make_pair(koncowy, waga)); // Dodajemy krawędź do listy sąsiedztwa
        edges.push_back(Edge(poczatkowy, koncowy, waga)); // Dodajemy krawędź do listy krawędzi
    }
};

struct Compare { // Struktura do porównywania krawędzi (używana w kolejce priorytetowej)
    bool operator()(const Edge& a, const Edge& b) {
        return a.odleglosc > b.odleglosc; // Porównujemy odległości krawędzi
    }
};


const int INF = 2147483647;

void fordBellman(const Graf& graf, int S) {
    vector<int> dist(graf.liczba_wierzcholkow, INF);
    dist[S] = 0;

    for (int i = 0; i < graf.liczba_wierzcholkow - 1; i++) {
        bool zmiana = false;
        for (const Edge& k : graf.edges) {
            if (dist[k.wierzcholek_poczatkowy] != INF && dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi < dist[k.wierzcholek_koncowy]) {
                dist[k.wierzcholek_koncowy] = dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi;
                zmiana = true;
            }
        }
        if(!zmiana) break;
    }

    // Sprawdzanie cyklu ujemnego
    for (const Edge& k : graf.edges) {
        if (dist[k.wierzcholek_poczatkowy] != INF && dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi < dist[k.wierzcholek_koncowy]) {
            cout << "Graf zawiera ujemny cykl!" << "\n";
            return;
        }
    }

    // Wyświetlenie dystansów
    for (int i = 0; i < graf.liczba_wierzcholkow; i++) {
        cout << i << ": " << dist[i] << "\n";
    }
}
struct FibonacciNode { // Struktura reprezentująca węzeł w kopcu Fibonacciego
    int key; // Klucz węzła, który jest używany do porządkowania węzłów w kopcu
    int vertex; // Wierzchołek, który jest przechowywany w węźle
    FibonacciNode* left; // Wskaźnik na lewego sąsiada węzła
    FibonacciNode* right; // Wskaźnik na prawego sąsiada węzła
    FibonacciNode* parent; // Wskaźnik na rodzica węzła
    FibonacciNode* child; // Wskaźnik na jedno z dzieci węzła
    int degree; // Stopień węzła, czyli liczba jego dzieci
    bool marked; // Flaga oznaczająca, czy węzeł został zmniejszony od czasu ostatniego usunięcia jednego z jego dzieci

    FibonacciNode(int vertex, int key) // Konstruktor węzła
            : vertex(vertex), key(key), left(this), right(this), parent(nullptr), child(nullptr), degree(0), marked(false) {}
};


void cascadingCut(FibonacciNode *&pNode, FibonacciNode *pNode1);

void cut(FibonacciNode *&pNode, FibonacciNode *pNode1, FibonacciNode *pNode2);

void consolidate(FibonacciNode *&pNode, int liczba_wierzcholkow);

void link(FibonacciNode *pNode, FibonacciNode *pNode1);


// Funkcja dodająca węzeł do kopca
void insert(FibonacciNode*& min, FibonacciNode* node) { //O(1)
    if (min == nullptr) { // Jeśli kopiec jest pusty
        min = node; // Węzeł staje się jedynym węzłem w kopcu
    } else {
        // Wstaw node do listy cyklicznej korzeni.
        node->right = min; // Prawym sąsiadem węzła staje się obecne minimum
        node->left = min->left; // Lewym sąsiadem węzła staje się lewy sąsiad obecnego minimum
        min->left->right = node; // Prawym sąsiadem lewego sąsiada obecnego minimum staje się węzeł
        min->left = node; // Lewym sąsiadem obecnego minimum staje się węzeł

        if (node->key < min->key) { // Jeśli klucz węzła jest mniejszy niż klucz obecnego minimum
            min = node; // Węzeł staje się nowym minimum
        }
    }
}


// Funkcja usuwająca węzeł o najmniejszym kluczu z kopca
FibonacciNode* extractMin(FibonacciNode*& min, int liczba_wierzcholkow) { //O(log n)
    FibonacciNode* minNode = min; // Przechowujemy węzeł o najmniejszym kluczu
    if (minNode != nullptr) { // Jeśli kopiec nie jest pusty

        // Przenieś każde dziecko minNode do listy korzeni.
        if (minNode->child != nullptr) { // Jeśli minNode ma dzieci
            FibonacciNode* current = minNode->child; // Zaczynamy od pierwszego dziecka
            do {
                FibonacciNode* next = current->right; // Przechowujemy prawe dziecko obecnego węzła
                insert(min, current); // Dodajemy obecne dziecko do listy korzeni
                current->parent = nullptr; // Usuwamy rodzica obecnego dziecka
                current = next; // Przechodzimy do następnego dziecka
            } while (current != minNode->child); // Kontynuujemy, dopóki nie przejdziemy przez wszystkie dzieci
        }

        // Usuń minNode z listy korzeni.
        if (minNode == minNode->right) { // Jeśli minNode jest jedynym węzłem w liście korzeni
            min = nullptr; // Lista korzeni staje się pusta
        } else { // W przeciwnym razie
            minNode->left->right = minNode->right; // Usuwamy minNode z listy korzeni
            minNode->right->left = minNode->left;
            min = minNode->right; // Nowym minimalnym węzłem staje się prawy sąsiad minNode
            consolidate(min, liczba_wierzcholkow); // Konsolidujemy kopiec
        }
    }
    return minNode; // Zwracamy usunięty węzeł
}

// Funkcja zmniejszająca klucz danego węzła
void decreaseKey(FibonacciNode*& min, FibonacciNode* node, int newKey) { //O(1)
    if (newKey > node->key) { // Jeśli nowy klucz jest większy niż obecny
        // Błąd: nowy klucz jest większy niż obecny.
        return; // Zwracamy błąd i kończymy funkcję
    }

    node->key = newKey; // Ustawiamy nowy klucz dla węzła
    FibonacciNode* parent = node->parent; // Pobieramy rodzica węzła

    if (parent != nullptr && node->key < parent->key) { // Jeśli węzeł ma rodzica i jego klucz jest mniejszy niż klucz rodzica
        // "Odcinanie" (cut) i "kaskadowe odcinanie" (cascading cut).
        cut(min, node, parent); // Wykonujemy operację "cut", która odcina węzeł od jego rodzica i dodaje go do listy korzeni
        cascadingCut(min, parent); // Wykonujemy operację "cascading cut", która rekurencyjnie odcina rodziców, jeśli są oznaczone
    }

    if (node->key < min->key) { // Jeśli klucz węzła jest mniejszy niż klucz obecnego minimum
        min = node; // Węzeł staje się nowym minimum
    }
}


// Funkcja konsolidująca kopiec
void consolidate(FibonacciNode*& min, int liczba_wierzcholkow) { //O (log n)
    if (min == nullptr) return; // Jeśli kopiec jest pusty, kończymy funkcję

    // Inicjalizacja wektora A stopni drzew.
    vector<FibonacciNode*> A(log2(liczba_wierzcholkow) + 1, nullptr); // Tworzymy wektor A o rozmiarze logarytmu z liczby wierzchołków

    vector<FibonacciNode*> roots; // Tworzymy wektor korzeni
    FibonacciNode* current = min; // Zaczynamy od obecnego minimum
    do {
        roots.push_back(current); // Dodajemy obecny węzeł do wektora korzeni
        current = current->right; // Przechodzimy do prawego sąsiada obecnego węzła
    } while (current != min); // Kontynuujemy, dopóki nie wrócimy do początkowego minimum

    // Przechodzenie przez listę korzeni i konsolidacja drzew.
    for (FibonacciNode* node : roots) { // Dla każdego węzła w wektorze korzeni
        int d = node->degree; // Pobieramy stopień węzła
        while (A[d] != nullptr) { // Dopóki istnieje inne drzewo o tym samym stopniu
            FibonacciNode* y = A[d]; // Pobieramy to drzewo
            if (node->key > y->key) { // Jeśli klucz węzła jest większy niż klucz y
                swap(node, y); // Zamieniamy węzły miejscami
            }
            link(y, node); // Łączymy y z węzłem
            A[d] = nullptr; // Usuwamy y z wektora A
            d++; // Zwiększamy stopień
        }
        A[d] = node; // Dodajemy węzeł do wektora A
    }
}

// Funkcja łącząca dwa węzły kopca Fibonacciego
void link(FibonacciNode* y, FibonacciNode* x) { // O(1)
    // Usunięcie y z listy korzeni i dodanie jako dziecko do x
    y->left->right = y->right; // Usuwamy y z listy korzeni
    y->right->left = y->left;
    y->parent = x; // Ustawiamy x jako rodzica y
    if (x->child == nullptr) { // Jeśli x nie ma dzieci
        x->child = y; // Ustawiamy y jako dziecko x
        y->right = y; // Ustawiamy y jako prawego sąsiada y
        y->left = y; // Ustawiamy y jako lewego sąsiada y
    } else { // Jeśli x ma dzieci
        y->left = x->child; // Ustawiamy dziecko x jako lewego sąsiada y
        y->right = x->child->right; // Ustawiamy prawego sąsiada dziecka x jako prawego sąsiada y
        x->child->right->left = y; // Ustawiamy y jako lewego sąsiada prawego sąsiada dziecka x
        x->child->right = y; // Ustawiamy y jako prawego sąsiada dziecka x
    }
    x->degree++; // Zwiększamy stopień x
    y->marked = false; // Oznaczamy y jako nieoznaczone
}


// Funkcja wykonująca "kaskadowe odcinanie"
void cascadingCut(FibonacciNode*& min, FibonacciNode* node) { //O(1) gdy 1 wywólane a gdy rekurencja więc w najgorszym O(log n) n to liczba wierzcholkow kopca
    FibonacciNode* parent = node->parent; // Pobieramy rodzica węzła
    if (parent != nullptr) { // Jeśli węzeł ma rodzica
        if (node->marked) { // Jeśli węzeł jest oznaczony
            cut(min, node, parent); // Wykonujemy operację "cut", która odcina węzeł od jego rodzica i dodaje go do listy korzeni
            cascadingCut(min, parent); // Wykonujemy operację "cascading cut" na rodzicu węzła
        } else {
            node->marked = true; // W przeciwnym razie oznaczamy węzeł
        }
    }
}

// Funkcja "odcinająca" węzeł od jego rodzica
void cut(FibonacciNode*& min, FibonacciNode* child, FibonacciNode* parent) { //O (1)
    // Usuń child z listy dzieci parent.
    if (child->right != child) { // Jeśli child ma sąsiadów
        child->right->left = child->left; // Usuwamy child z listy dzieci parent
        child->left->right = child->right;
    }
    if (parent->child == child) { // Jeśli child jest wskazywany przez parent jako jedno z jego dzieci
        if (child->right != child) { // Jeśli child ma sąsiadów
            parent->child = child->right; // Teraz parent wskazuje na prawego sąsiada child
        } else {
            parent->child = nullptr; // Parent nie ma już dzieci
        }
    }
    parent->degree--; // Zmniejszamy stopień parent

    // Dodaj child do listy korzeni kopca.
    child->left = min; // Lewym sąsiadem child staje się obecne minimum
    child->right = min->right; // Prawym sąsiadem child staje się prawy sąsiad obecnego minimum
    min->right->left = child; // Lewym sąsiadem prawego sąsiada obecnego minimum staje się child
    min->right = child; // Prawym sąsiadem obecnego minimum staje się child
    child->parent = nullptr; // Child nie ma już rodzica

    // Oznacz child jako nienaznaczony.
    child->marked = false; // Child nie jest oznaczony
}

// Funkcja implementująca algorytm Dijkstry z użyciem kopca Fibonacciego
void dijkstraFibonacciHeap(const Graf& graf, int S) { //O(O(E + V log V))
    vector<int> odleglosc(graf.liczba_wierzcholkow, INF); // Inicjalizujemy odległości jako nieskończoność
    vector<FibonacciNode*> nodes(graf.liczba_wierzcholkow, nullptr); // Tworzymy wektor węzłów
    FibonacciNode* min = nullptr; // Inicjalizujemy minimum jako puste

    odleglosc[S] = 0; // Odległość od źródła do siebie samego jest zawsze 0
    nodes[S] = new FibonacciNode(S, 0); // Tworzymy nowy węzeł dla źródła
    insert(min, nodes[S]); // Dodajemy źródło do kopca

    while (min != nullptr) { // Dopóki kopiec nie jest pusty
        FibonacciNode* node = extractMin(min, graf.liczba_wierzcholkow); // Usuwamy węzeł o najmniejszym kluczu z kopca
        int u = node->vertex; // Pobieramy wierzchołek z usuniętego węzła

        for (const auto& [v, waga] : graf.listaSasiedztwa[u]) { // Dla każdego sąsiada wierzchołka u
            if (odleglosc[u] + waga < odleglosc[v]) { // Jeśli możemy skrócić drogę do v przez u
                odleglosc[v] = odleglosc[u] + waga; // Aktualizujemy odległość do v
                if (nodes[v] == nullptr) { // Jeśli v nie jest jeszcze w kopcu
                    nodes[v] = new FibonacciNode(v, odleglosc[v]); // Tworzymy nowy węzeł dla v
                    insert(min, nodes[v]); // Dodajemy v do kopca
                } else { // Jeśli v jest już w kopcu
                    decreaseKey(min, nodes[v], odleglosc[v]); // Zmniejszamy klucz v w kopcu
                }
            }
        }
    }

    for (int i = 0; i < graf.liczba_wierzcholkow; ++i) { // Dla każdego wierzchołka
        if (odleglosc[i] != INF) // Jeśli odległość do i jest skończona
            cout << i << ": " << odleglosc[i] << "\n"; // Wyświetlamy odległość
        else // W przeciwnym razie
            cout << i << ": " << "2147483647" << "\n"; // Wyświetlamy nieskończoność
    }

    for (FibonacciNode* node : nodes) { // Dla każdego węzła
        if (node) delete node; // Usuwamy węzeł
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int w, k, wierzcholek_start;
    cin >> w >> k;
    bool czy_ujemne = false;
    Graf graf(w);
    for (int i = 0; i < k; ++i) {
        int poczatkowy, koncowy, waga;
        cin >> poczatkowy >> koncowy >> waga;
        graf.dodajKrawedz(poczatkowy, koncowy, waga);
        if(waga < 0)
            czy_ujemne = true;
    }
    cin >> wierzcholek_start;
    if (czy_ujemne)
        fordBellman(graf, wierzcholek_start);
    else
        dijkstraFibonacciHeap(graf, wierzcholek_start);
}
