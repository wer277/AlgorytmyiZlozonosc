#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

struct Edge{
    int wierzcholek_poczatkowy, wierzcholek_koncowy;
    long long int waga = 0;
    long long int odleglosc = 0;
    bool odwiedzony = false;

    Edge(): wierzcholek_poczatkowy(0), wierzcholek_koncowy(0), waga(0){}

    Edge(int poczatek, int koniec, long long int waga): wierzcholek_poczatkowy(poczatek), wierzcholek_koncowy(koniec), waga(waga){}

    Edge(int poczatek, int koniec, long long int odleglosc, bool odwiedzony): wierzcholek_poczatkowy(poczatek), wierzcholek_koncowy(koniec), odleglosc(odleglosc), odwiedzony(odwiedzony){}
};

struct Graf{
    int liczba_wierzcholkow = 0;
    vector<Edge> edges;
    vector<vector<pair<int, long long int>>> listaSasiedztwa;
    vector<Edge> bellmanOdp;
    vector<Edge> dikstryOdp;

    Graf(int w): liczba_wierzcholkow(w), listaSasiedztwa(w){}

    void dodajKrawedz(int poczatek, int koniec, long long int waga){
        listaSasiedztwa[poczatek].push_back(make_pair(koniec, waga));
        edges.push_back(Edge(poczatek, koniec, waga));
    }
};

const long long int INF = numeric_limits<long long int>::max();

void bellman(Graf &graf, int s){
    vector<long long int> dist(graf.liczba_wierzcholkow, INF);
    dist[s] = 0;

    for(int i = 0; i<graf.liczba_wierzcholkow-1; i++){
        bool zmiana = false;
        for(const Edge &k : graf.edges){
            if(dist[k.wierzcholek_poczatkowy] != INF && dist[k.wierzcholek_poczatkowy] + k.waga < dist[k.wierzcholek_koncowy]){
                dist[k.wierzcholek_koncowy] = dist[k.wierzcholek_poczatkowy] + k.waga;
                zmiana = true;
            }
        }
        if(!zmiana) break;
    }

    int wierzcholek = -1;
    long long int odleglosc = -1;
    for(int i = 0; i<graf.liczba_wierzcholkow; i++){
        if(odleglosc < dist[i] && dist[i] != INF){
            odleglosc = dist[i];
            wierzcholek = i;
        } else if(dist[i] == INF){
            graf.bellmanOdp.push_back(Edge(s, i, INF));
        }
    }
    graf.bellmanOdp.push_back(Edge(s, wierzcholek, odleglosc));
}

void dikstry(Graf &graf, int s){
    vector<long long int> dist(graf.liczba_wierzcholkow, INF);
    dist[s] = 0;
    priority_queue<pair<long long int, int>, vector<pair<long long int, int>>, greater<>> kolejka;
    vector<bool> odwiedzony(graf.liczba_wierzcholkow, false);

    kolejka.push({0,s});

    while(!kolejka.empty()){
        int u = kolejka.top().second;

        if(odwiedzony[u]){
            continue;
        }

        odwiedzony[u] = true;

        for(const auto &[v,waga] : graf.listaSasiedztwa[u]){
            if(dist[u] + waga < dist[v]){
                dist[v] = dist[u] + waga;
                kolejka.push({dist[v], v});
            }
        }
    }

    int wierzcholek = -1;
    long long int odleglosc = -1;

    for(int i = 0; i<graf.liczba_wierzcholkow; i++){
        if(odleglosc < dist[i] && dist[i] != INF){
            odleglosc = dist[i];
            wierzcholek = i;
        } else if(dist[i] == INF){
            graf.dikstryOdp.push_back(Edge(s, i, INF));
        }
    }
    graf.dikstryOdp.push_back(Edge(s, wierzcholek, odleglosc));
}

int main(){
    int n, m;
    cin>>n>>m;
    bool czy_ujemne = false;
    Graf graf(n);
    int poczatek, koniec;
    long long int waga;
    int wierzcholekA = -1, wierzcholekB = -1;
    long long int odleglosc = -1;
    for(int i = 0; i<m; i++){
        cin>>poczatek>>koniec>>waga;
        graf.dodajKrawedz(poczatek,koniec,waga);
        if(waga < 0){
            czy_ujemne = true;
        }
    }

    if(czy_ujemne){
        for(int i = 0; i<n; i++){
            bellman(graf, i);
        }
        for(int i = 0; i<graf.bellmanOdp.size(); i++){
            if(odleglosc < graf.bellmanOdp[i].waga && graf.bellmanOdp[i].waga != INF){
                odleglosc = graf.bellmanOdp[i].waga;
                wierzcholekA = graf.bellmanOdp[i].wierzcholek_poczatkowy;
                wierzcholekB = graf.bellmanOdp[i].wierzcholek_koncowy;
            }
        }

        for(int i = 0; i<graf.bellmanOdp.size(); i++){
            if(graf.bellmanOdp[i].wierzcholek_poczatkowy == wierzcholekA && graf.bellmanOdp[i].waga == INF){
                wierzcholekB = graf.bellmanOdp[i].wierzcholek_koncowy;
                break;
            }
        }

        cout<<wierzcholekA<<" "<<wierzcholekB<<"\n";
    } else{
        for(int i = 0; i<n; i++){
            dikstry(graf, i);
        }

        for(int i = 0; i<graf.dikstryOdp.size(); i++){
            if(odleglosc < graf.dikstryOdp[i].waga && graf.dikstryOdp[i].waga != INF){
                odleglosc = graf.dikstryOdp[i].waga;
                wierzcholekA = graf.dikstryOdp[i].wierzcholek_poczatkowy;
                wierzcholekB = graf.dikstryOdp[i].wierzcholek_koncowy;
            }
        }

        for(int i = 0; i<graf.dikstryOdp.size(); i++){
            if(graf.dikstryOdp[i].wierzcholek_poczatkowy == wierzcholekA && graf.dikstryOdp[i].waga == INF){
                wierzcholekB = graf.dikstryOdp[i].wierzcholek_koncowy;
                break;
            }
        }

        cout<<wierzcholekA<<" "<<wierzcholekB<<"\n";
    }
    /*for(int i = 0; i<graf.bellmanOdp.size(); i++){
            cout<<graf.bellmanOdp[i].wierzcholek_poczatkowy<<" "<<graf.bellmanOdp[i].wierzcholek_koncowy<<" "<<graf.bellmanOdp[i].waga<<"\n";
    }*/
    return 0;
}
