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
    Edge(int poczatkowy, int koncowy, int waga)
            : wierzcholek_poczatkowy(poczatkowy), wierzcholek_koncowy(koncowy), waga_krawedzi(waga) {}

    Edge() : wierzcholek_poczatkowy(0), wierzcholek_koncowy(0), waga_krawedzi(0.0) {}

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

struct HeapNode {
    int vertex;
    int distance;

    HeapNode(int v, int d) : vertex(v), distance(d) {}

    // Operator porównania dla min-kopca
    bool operator<(const HeapNode& that) const {
        return this->distance < that.distance;
    }
    bool operator>(const HeapNode& that) const {
        return this->distance > that.distance;
    }
};

void swap(HeapNode& a, HeapNode& b) {
    HeapNode temp = a;
    a = b;
    b = temp;
}

void heapify(vector<HeapNode>& heap, int i, int n) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] < heap[smallest])
        smallest = left;

    if (right < n && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapify(heap, smallest, n);
    }
}

void insertHeap(vector<HeapNode>& heap, HeapNode node) {
    heap.push_back(node);
    int i = heap.size() - 1;
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) { //>
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode extractMin(vector<HeapNode>& heap) {
    if (heap.size() <= 1) {
        HeapNode top = heap[0];
        heap.pop_back();
        return top;
    }

    HeapNode root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify(heap, 0, heap.size());
    return root;
}

void decreaseKey(vector<HeapNode>& heap, int vertex, int distance) {
    // Znajdź wierzchołek w kopcu i zaktualizuj jego odległość
    int i;
    for (i = 0; i < heap.size(); ++i) {
        if (heap[i].vertex == vertex) {
            heap[i].distance = distance;
            break;
        }
    }

    // Przywróć własności kopca
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {         //<
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void dijkstra(const Graf& graf, int S) {
    vector<int> odleglosc(graf.liczba_wierzcholkow, INF);
    vector<bool> odwiedzony(graf.liczba_wierzcholkow, false);
    vector<HeapNode> heap;
    vector<int> indexInHeap(graf.liczba_wierzcholkow, -1); // Dodane do śledzenia pozycji wierzchołków w kopcu

    odleglosc[S] = 0;
    insertHeap(heap, {S, 0});
    indexInHeap[S] = 0; // Ustawienie pozycji startowej w kopcu

    while (!heap.empty()) {
        HeapNode node = extractMin(heap);
        int u = node.vertex;
        indexInHeap[u] = -1; // Usunięcie wierzchołka z kopca
        odwiedzony[u] = true;

        for (const auto& [v, waga] : graf.listaSasiedztwa[u]) {
            if (!odwiedzony[v] && odleglosc[u] + waga < odleglosc[v]) {
                odleglosc[v] = odleglosc[u] + waga;
                if (indexInHeap[v] != -1) {
                    // Jeśli wierzchołek jest już w kopcu, zmniejsz jego klucz
                    decreaseKey(heap, v, odleglosc[v]);
                } else {
                    // W przeciwnym razie dodaj wierzchołek do kopca
                    insertHeap(heap, {v, odleglosc[v]});
                    indexInHeap[v] = heap.size() - 1;
                }
            }
        }
    }

    // Wyświetlenie wyników
    for (int i = 0; i < graf.liczba_wierzcholkow; ++i) {
        if (odleglosc[i] != INF)
            cout << i << ": " << odleglosc[i] << "\n";
        else
            cout << i << ": " << "2147483647" << "\n";
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
        dijkstra(graf, wierzcholek_start);
}
