#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Dane {
    int A, B;
    double I, J;
};

struct Node {
    double kosztA{}, kosztB{};
    bool odwiedzony1{}, odwiedzony2{};
};


using namespace std;
Node *node;

struct CompareB {
    bool operator()(int const &p1, int const &p2) {
        return node[p1].kosztB < node[p2].kosztB;
    }
};

struct CompareA {
    bool operator()(int const &p1, int const &p2) {
        return node[p1].kosztA < node[p2].kosztA;
    }
};


void algorytm(vector<int> *listaSasiedztwa, Dane *pDane, int x, int M, int *tab, int N) {
    node = new Node[x];
    double koszt;
    priority_queue<int, vector<int>, CompareA> kolejka1;
    priority_queue<int, vector<int>, CompareB> kolejka2;
    for (int i = 0; i < x; ++i) {
        node[i].kosztB = node[i].kosztA = 0;
    }
    node[M].kosztB = node[M].kosztA = 1.;
    kolejka1.push(M);
    //Dijkstry 1
    while (!kolejka1.empty()) {
        int index;
        index = kolejka1.top();
        kolejka1.pop();
        if (node[index].odwiedzony1 == false) {
            node[index].odwiedzony1 = true;
            for (int i = 0; i < listaSasiedztwa[index].size(); i++) {
                int dane_id = listaSasiedztwa[index][i];
                int sasiad_ID = pDane[dane_id].B;
                koszt = node[index].kosztA * pDane[dane_id].I;
                if (node[sasiad_ID].kosztA <= koszt) {
                    node[sasiad_ID].kosztA = koszt;
                    kolejka1.push(sasiad_ID);
                }
            }
            /*for (int i = 0; i < listaSasiedztwa[index+N-1].size(); i++) {
                int dane_id = listaSasiedztwa[index+N-1][i];
                int sasiad_ID = pDane[dane_id].B;
                koszt = node[index].kosztA * pDane[dane_id].I;
                if (node[sasiad_ID].kosztA < koszt) {
                    node[sasiad_ID].kosztA = koszt;
                    kolejka1.push(sasiad_ID);

                }
            }*/
        }
    }
        kolejka2.push(M);
        while (!kolejka2.empty()) {
            int index;
            index = kolejka2.top();
            kolejka2.pop();
            if (node[index].odwiedzony2 == false) {
                node[index].odwiedzony2 = true;
                for (int i = 0; i < listaSasiedztwa[index].size(); i++) {
                    int dane_id = listaSasiedztwa[index][i];
                    int sasiad_ID = pDane[dane_id].B;
                    koszt = node[index].kosztB * pDane[dane_id].J;
                    if (node[sasiad_ID].kosztB <= koszt) {
                        node[sasiad_ID].kosztB = koszt;
                        kolejka2.push(sasiad_ID);
                    }
                }
                /*for (int i = 0; i < listaSasiedztwa[index+N-1].size(); i++) {
                    int dane_id = listaSasiedztwa[index+N-1][i];
                    int sasiad_ID = pDane[dane_id].A;
                    koszt = node[index].kosztB * pDane[dane_id].J;
                    if (node[sasiad_ID].kosztB < koszt) {
                        node[sasiad_ID].kosztB = koszt;
                        kolejka2.push(sasiad_ID);
                    }
                }*/
            }
        }

    double odp = 0;
    for (int i = 0;i < x;++i) {
        if (tab[i] == 1) {
            node[i].kosztA = node[i].kosztA * node[i].kosztB * 120000.0;
            if (odp < node[i].kosztA)
                odp = node[i].kosztA;
        }
    }
    long long int wynik = odp;
    cout << wynik;
}

int main() {
    int X, N, M;                                                  //ilość giełd czyli liczba wierzchołków //n połączeń między giełdami liczba krawędzi
    int *tab;                                                   //tablic wrtości 0 i 1, które pokazuję status czy na giełdzie jest bajtcoin
    cin >> X;
    tab = new int[X];

    for (int i = 0; i < X; i++) {                                   //wczytywanie wartości 0 i 1
        cin >> tab[i];
    }
    cin >> N;
    vector<int> *listaSasiedztwa = new vector<int>[X];
    Dane *dane;
    dane = new Dane[2 * N];
    for (int i = 0; i < N; i++) {
        cin >> dane[i].A >> dane[i].B >> dane[i].I >> dane[i].J;
        dane[i].I = 1. - dane[i].I;
        dane[i].J = 1. - dane[i].J;
        dane[i + N].A = dane[i].B;
        dane[i + N].B = dane[i].A;
        dane[i + N].I = dane[i].I;
        dane[i + N].J = dane[i].J;
        listaSasiedztwa[dane[i].A].push_back(i);
        listaSasiedztwa[dane[i].B].push_back(i + N);   //na liste sąsiedztwa o indexie danego wierzchołka dodaje sąsiada
    }
    cin >> M;
    algorytm(listaSasiedztwa, dane, X, M, tab, N);

    delete[] tab;
    return 0;
}
