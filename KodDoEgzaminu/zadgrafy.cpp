#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Edge {
    int wierzcholek_poczatkowy;
    int wierzcholek_koncowy;
    long long int waga_krawedzi = 0;
    Edge() : wierzcholek_poczatkowy(0), wierzcholek_koncowy(0), waga_krawedzi(0.0) {}

    Edge(int poczatkowy, int koncowy, long long int waga)
            : wierzcholek_poczatkowy(poczatkowy), wierzcholek_koncowy(koncowy), waga_krawedzi(waga) {}

};

struct Graf {
    int liczba_wierzcholkow = 0;  // Liczba wierzchołków
    std::vector<Edge> edges; // Krawędzie grafu
    vector<vector<pair<int, long long int>>> listaSasiedztwa;
    vector<vector<pair<int, long long int>>> wynik;
    std::vector<Edge> odleglosc;
    Graf(int w) : liczba_wierzcholkow(w), listaSasiedztwa(w), wynik(w) {}

    void dodajKrawedz(int poczatkowy, int koncowy, long long int waga) {
        listaSasiedztwa[poczatkowy].push_back(make_pair(koncowy, waga));
        edges.push_back(Edge(poczatkowy, koncowy, waga)); // Dodanie krawędzi do listy
    }
    void dodajWynik(int poczatkowy, int koncowy, long long int waga) {
        wynik[poczatkowy].push_back(make_pair(koncowy, waga));
    }
};

const long long INF = numeric_limits<long long>::max();

void fordBellman(Graf& graf, int S) {
    vector<long long int> dist(graf.liczba_wierzcholkow, INF);
    dist[S] = 0;

    for (int i = 0; i < graf.liczba_wierzcholkow - 1; i++) {
        bool zmiana = false;
        for (const Edge &k: graf.edges) {
            if (dist[k.wierzcholek_poczatkowy] != INF &&
                dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi < dist[k.wierzcholek_koncowy]) {
                dist[k.wierzcholek_koncowy] = dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi;
                zmiana = true;
            }
        }
        if (!zmiana) break;
    }
    for (const Edge &k: graf.edges) {
        if (dist[k.wierzcholek_poczatkowy] != INF && dist[k.wierzcholek_poczatkowy] + k.waga_krawedzi < dist[k.wierzcholek_koncowy]) {
            cout << "Wykryto cykl o ujemnej wadze. Nie można jednoznacznie znaleźć najkrótszej ścieżki." << endl;
            return;
        }
    } // Zwraca true, jeśli nie wykryto cyklu o ujemnej wadze

    int wierzcholek = 0, dystans = 0;
    // Zapisz wyniki dla wierzchołka startowego
    for (int i = 0; i < graf.liczba_wierzcholkow; ++i) {
        if(dystans<dist[i]){
            dystans = dist[i];
            wierzcholek = i;
        }
    }
    graf.dodajWynik(S,wierzcholek,dystans);
    // Wyświetlenie dystansów
    for (int i = 0; i < graf.liczba_wierzcholkow; i++) {
        cout << i << ": " << dist[i] << "\n";
    }
}

int main() {
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
    }
    fordBellman(graf,1);
    for(int i = 0; i<w;i++){
        fordBellman(graf,i);
    }
    long long int najdluzszyDystans = -1;
    int startWierzcholek = -1;
    int wierzcholekKoniec = -1;

    for(int i = 0; i<graf.wynik.size(); i++){
        for(const auto& para : graf.wynik[i]){
            if(para.second > najdluzszyDystans){
                najdluzszyDystans = para.second;
                startWierzcholek = i;
                wierzcholekKoniec = para.first;
            }
        }
    }
    if(najdluzszyDystans != -1) { // Jeśli znaleziono jakąś ścieżkę
        cout << startWierzcholek << " " << wierzcholekKoniec << endl;
    } else {
        cout << "Nie znaleziono żadnej ścieżki." << endl;
    }
    return 0;
}
