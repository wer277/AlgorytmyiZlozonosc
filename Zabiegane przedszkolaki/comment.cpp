#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int wierzcholek_poczatkowy;
    int wierzcholek_koncowy;
    int waga_krawedzi = 0;
    int odleglosc = 0;
    bool odwiedzony = false;

    Edge() : wierzcholek_poczatkowy(0), wierzcholek_koncowy(0), waga_krawedzi(0.0) {}
    Edge(int poczatkowy, int koncowy, int waga)
            : wierzcholek_poczatkowy(poczatkowy), wierzcholek_koncowy(koncowy), waga_krawedzi(waga) {}
    Edge(int poczatkowy, int koncowy, int odleglosc, bool odwiedzony)
            : wierzcholek_poczatkowy(poczatkowy), wierzcholek_koncowy(koncowy), odleglosc(odleglosc), odwiedzony(odwiedzony) {}
};

struct Graf {
    int liczba_wierzcholkow = 0;  // Liczba wierzchołków
    std::vector<Edge> edges; // Krawędzie grafu
    vector<vector<pair<int, int>>> listaSasiedztwa;

    Graf(int w) : liczba_wierzcholkow(w), listaSasiedztwa(w) {}

    void dodajKrawedz(int poczatkowy, int koncowy, int waga) {
        listaSasiedztwa[poczatkowy].push_back(make_pair(koncowy, waga));
        edges.push_back(Edge(poczatkowy, koncowy, waga)); // Dodanie krawędzi do listy
    }
};

struct Compare {
    bool operator()(const Edge& a, const Edge& b) {
        return a.odleglosc > b.odleglosc;
    }
};

const int INF = 2147483647;

// Funkcja implementująca algorytm Forda-Bellmana
void fordBellman(const Graf& graf, int S) { // O(V*E)
    vector<int> dist(graf.liczba_wierzcholkow, INF); // Inicjalizujemy odległości jako nieskończoność
    dist[S] = 0; // Odległość od źródła do siebie samego jest zawsze 0

    // Relaxacja krawędzi
    for (int i = 0; i < graf.liczba_wierzcholkow - 1; i++) { // Dla każdego wierzchołka
        bool zmiana = false;
        for (const Edge& k : graf.edges) { // Dla każdej krawędzi
            // Jeśli odległość do wierzchołka początkowego nie jest nieskończoność i odległość do wierzchołka końcowego przez wierzchołek początkowy jest mniejsza
            if (dist[k.wierzcholek_poczatkowy] != INF && dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi < dist[k.wierzcholek_koncowy]) {
                dist[k.wierzcholek_koncowy] = dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi; // Aktualizujemy odległość do wierzchołka końcowego
                zmiana = true;
            }
        }
        if(!zmiana) break; // Jeśli nie było żadnej zmiany, przerywamy pętlę
    }

    // Sprawdzanie cyklu ujemnego
    for (const Edge& k : graf.edges) { // Dla każdej krawędzi
        // Jeśli możemy zrelaksować krawędź, to mamy cykl o ujemnej wadze
        if (dist[k.wierzcholek_poczatkowy] != INF && dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi < dist[k.wierzcholek_koncowy]) {
            cout << "Graf zawiera ujemny cykl!" << "\n";
            return;
        }
    }

    // Wyświetlenie dystansów
    for (int i = 0; i < graf.liczba_wierzcholkow; i++) { // Dla każdego wierzchołka
        cout << i << ": " << dist[i] << "\n"; // Wyświetlamy najkrótszą odległość od źródła
    }
}
/*Algorytm Dijkstry, który jest implementowany za pomocą kolejki priorytetowej, ma złożoność czasową O((V+E) log V), gdzie V to liczba wierzchołków, a E to liczba krawędzi w grafie. Oto dlaczego:

O(V log V): Każdy wierzchołek jest dodawany do kolejki priorytetowej, co zajmuje O(log V) czasu (ponieważ operacje wstawiania do kopca binarnego mają złożoność logarytmiczną). Ponieważ robimy to dla V wierzchołków, mamy O(V log V).

O(E log V): Dla każdej krawędzi, sprawdzamy, czy możemy poprawić najkrótszą ścieżkę do wierzchołka docelowego. To zajmuje O(log V) czasu, ponieważ musimy zaktualizować kolejność w kopcu binarnym. Ponieważ robimy to dla E krawędzi, mamy O(E log V).

Dodając te dwie części razem, otrzymujemy złożoność czasową O((V+E) log V) dla algorytmu Dijkstry zaimplementowanego za pomocą kolejki priorytetowej.

*/
// Funkcja implementująca algorytm Dijkstry
void dijkstra(const Graf& graf, int S) { // O((V+E) log V)
    vector<int> odleglosc(graf.liczba_wierzcholkow, INF); // Inicjalizujemy odległości jako nieskończoność
    odleglosc[S] = 0; // Odległość od źródła do siebie samego jest zawsze 0

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> kolejka; // Tworzymy kolejkę priorytetową do przechowywania wierzchołków do przetworzenia
    vector<bool> odwiedzony(graf.liczba_wierzcholkow, false); // Tworzymy wektor odwiedzonych wierzchołków

    kolejka.push({0, S}); // Dodajemy źródło do kolejki z odległością 0

    while (!kolejka.empty()) { // Dopóki kolejka nie jest pusta
        int u = kolejka.top().second; // Pobieramy wierzchołek z najmniejszą odległością
        kolejka.pop(); // Usuwamy go z kolejki

        if (odwiedzony[u]) {
            continue; // Jeśli wierzchołek został już odwiedzony, kontynuuj
        }
        odwiedzony[u] = true; // Oznaczamy wierzchołek jako odwiedzony

        for (const auto& [v, waga] : graf.listaSasiedztwa[u]) { // Dla każdego sąsiada wierzchołka u
            if (odleglosc[u] + waga < odleglosc[v]) { // Jeśli możemy skrócić drogę do v przez u
                odleglosc[v] = odleglosc[u] + waga; // Aktualizujemy odległość do v
                kolejka.push({odleglosc[v], v}); // Dodajemy v do kolejki z nową odległością
            }
        }
    }

    for (int i = 0; i < graf.liczba_wierzcholkow; ++i) { // Dla każdego wierzchołka
        if (odleglosc[i] != INF) // Jeśli odległość do i jest skończona
            cout << i << ": " << odleglosc[i] << "\n"; // Wyświetlamy odległość
        else // W przeciwnym razie
            cout << i << ": " << "2147483647" << "\n"; // Wyświetlamy nieskończoność
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    bool czy_ujemne = false;
    int w, k, wierzcholek_start;
    Edge* krawedzDane;
    cin >> w >> k;
    krawedzDane = new Edge[k];

    Graf graf(w);
    graf.liczba_wierzcholkow = w;
    graf.listaSasiedztwa.resize(w);
    std::vector<int> dist;

    for (int i = 0; i < k; i++) {
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
        dijkstra(graf, wierzcholek_start);
}
