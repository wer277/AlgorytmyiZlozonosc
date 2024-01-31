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

//void fordBellman(Graf g, int S, int n, vector<int>& dist) {
//    dist.resize(n, INF);
//    dist[S] = 0;
//
//
//    for (int i = 0; i < n - 1; i++) {
//        bool zmiana = false;
//        for (const Edge& k : g.edges) {
//            if (dist[k.wierzcholek_poczatkowy] != INF && dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi < dist[k.wierzcholek_koncowy]) {
//                dist[k.wierzcholek_koncowy] = dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi;
//                zmiana = true;
//            }
//        }
//        if(!zmiana) break;
//    }
//
//    // Sprawdzanie cyklu ujemnego
//    for (const Edge& k : g.edges) {
//        if (dist[k.wierzcholek_poczatkowy] != INF && dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi < dist[k.wierzcholek_koncowy]) {
//            cout << "Graf zawiera ujemny cykl!" << "\n";
//            return;
//        }
//    }
//
//    // Wyświetlenie dystansów
//    for (int i = 0; i < n; i++) {
//        cout << i << ": " << dist[i] << "\n";
//    }
//}

void dijkstra(const Graf& graf, int S) {
    vector<int> odleglosc(graf.liczba_wierzcholkow, INF);
    odleglosc[S] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> kolejka;
    vector<bool> odwiedzony(graf.liczba_wierzcholkow, false);

    kolejka.push({0, S});

    while (!kolejka.empty()) {
        int u = kolejka.top().second;
        kolejka.pop();

        if (odwiedzony[u]) {
            continue; // Jeśli wierzchołek został już odwiedzony, kontynuuj
        }
        odwiedzony[u] = true;

        for (const auto& [v, waga] : graf.listaSasiedztwa[u]) {
            if (odleglosc[u] + waga < odleglosc[v]) {
                odleglosc[v] = odleglosc[u] + waga;
                kolejka.push({odleglosc[v], v});
            }
        }
    }

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
//        cin >> krawedzDane[i].wierzcholek_poczatkowy >> krawedzDane[i].wierzcholek_koncowy >> krawedzDane[i].waga_krawedzi;
//        graf.listaSasiedztwa[krawedzDane[i].wierzcholek_poczatkowy].push_back({krawedzDane[i].wierzcholek_koncowy, krawedzDane[i].waga_krawedzi});
//        graf.edges.push_back(krawedzDane[i]);
//        if (krawedzDane[i].waga_krawedzi < 0)
//            czy_ujemne = true;
    }

    cin >> wierzcholek_start;
    if (czy_ujemne)
//        fordBellman(graf, wierzcholek_start, w, dist);
    fordBellman(graf, wierzcholek_start);
    else
        dijkstra(graf, wierzcholek_start);
}
