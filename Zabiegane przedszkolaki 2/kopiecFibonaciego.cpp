#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

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

    Graf() : liczba_wierzcholkow(0), listaSasiedztwa(0) {}
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
struct FibonacciNode {
    int key;
    int vertex;
    FibonacciNode* left;
    FibonacciNode* right;
    FibonacciNode* parent;
    FibonacciNode* child;
    int degree;
    bool marked;

    FibonacciNode(int vertex, int key)
            : vertex(vertex), key(key), left(this), right(this), parent(nullptr), child(nullptr), degree(0), marked(false) {}
};

void cascadingCut(FibonacciNode *&pNode, FibonacciNode *pNode1);

void cut(FibonacciNode *&pNode, FibonacciNode *pNode1, FibonacciNode *pNode2);

void consolidate(FibonacciNode *&pNode, int liczba_wierzcholkow);

void link(FibonacciNode *pNode, FibonacciNode *pNode1);

void insert(FibonacciNode*& min, FibonacciNode* node) {
    if (min == nullptr) {
        min = node;
    } else {
        // Wstaw node do listy cyklicznej korzeni.
        node->right = min;
        node->left = min->left;
        min->left->right = node;
        min->left = node;

        if (node->key < min->key) {
            min = node;
        }
    }
}
FibonacciNode* extractMin(FibonacciNode*& min, int liczba_wierzcholkow) {
    FibonacciNode* minNode = min;
    if (minNode != nullptr) {
        // Przenieś każde dziecko minNode do listy korzeni.
        if (minNode->child != nullptr) {
            FibonacciNode* current = minNode->child;
            do {
                FibonacciNode* next = current->right;
                insert(min, current);
                current->parent = nullptr;
                current = next;
            } while (current != minNode->child);
        }

        // Usuń minNode z listy korzeni.
        if (minNode == minNode->right) {
            min = nullptr;
        } else {
            minNode->left->right = minNode->right;
            minNode->right->left = minNode->left;
            min = minNode->right;
            consolidate(min, liczba_wierzcholkow); // Zmodyfikowane wywołanie
        }
    }
    return minNode;
}

void decreaseKey(FibonacciNode*& min, FibonacciNode* node, int newKey) {
    if (newKey > node->key) {
        // Błąd: nowy klucz jest większy niż obecny.
        return;
    }

    node->key = newKey;
    FibonacciNode* parent = node->parent;

    if (parent != nullptr && node->key < parent->key) {
        // "Odcinanie" (cut) i "kaskadowe odcinanie" (cascading cut).
        cut(min, node, parent);
        cascadingCut(min, parent);
    }

    if (node->key < min->key) {
        min = node;
    }
}
void consolidate(FibonacciNode*& min, int liczba_wierzcholkow) {
    if (min == nullptr) return;

    // Inicjalizacja wektora A stopni drzew.
    vector<FibonacciNode*> A(log2(liczba_wierzcholkow) + 1, nullptr); //log

    vector<FibonacciNode*> roots;
    FibonacciNode* current = min;
    do {
        roots.push_back(current);
        current = current->right;
    } while (current != min);

    // Przechodzenie przez listę korzeni i konsolidacja drzew.
    for (FibonacciNode* node : roots) {
        int d = node->degree;
        while (A[d] != nullptr) {
            FibonacciNode* y = A[d];
            if (node->key > y->key) {
                swap(node, y);
            }
            link(y, node);
            A[d] = nullptr;
            d++;
        }
        A[d] = node;
    }

    // Odbudowa listy korzeni kopca z konsolidowanych drzew.
    min = nullptr;
    for (FibonacciNode* node : A) {
        if (node != nullptr) {
            if (min == nullptr) {
                min = node;
                min->left = min->right = min;
            } else {
                node->left = min;
                node->right = min->right;
                min->right->left = node;
                min->right = node;
                if (node->key < min->key) {
                    min = node;
                }
            }
        }
    }
}

void link(FibonacciNode* y, FibonacciNode* x) {
    // Usunięcie y z listy korzeni i dodanie jako dziecko do x
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == nullptr) {
        x->child = y;
        y->right = y;
        y->left = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->marked = false;
}


void cascadingCut(FibonacciNode*& min, FibonacciNode* node) {
    FibonacciNode* parent = node->parent;
    if (parent != nullptr) {
        if (node->marked) {
            cut(min, node, parent);
            cascadingCut(min, parent);
        } else {
            node->marked = true;
        }
    }
}

void cut(FibonacciNode*& min, FibonacciNode* child, FibonacciNode* parent) {
    // Usuń child z listy dzieci parent.
    if (child->right != child) {
        child->right->left = child->left;
        child->left->right = child->right;
    }
    if (parent->child == child) {
        if (child->right != child) {
            parent->child = child->right;
        } else {
            parent->child = nullptr;
        }
    }
    parent->degree--;

    // Dodaj child do listy korzeni kopca.
    child->left = min;
    child->right = min->right;
    min->right->left = child;
    min->right = child;
    child->parent = nullptr;

    // Oznacz child jako nienaznaczony.
    child->marked = false;
}




void dijkstraFibonacciHeap(const Graf& graf, int S) {
    vector<int> odleglosc(graf.liczba_wierzcholkow, INF);
    vector<FibonacciNode*> nodes(graf.liczba_wierzcholkow, nullptr);
    FibonacciNode* min = nullptr;

    odleglosc[S] = 0;
    nodes[S] = new FibonacciNode(S, 0);
    insert(min, nodes[S]);

    while (min != nullptr) {
        FibonacciNode* node = extractMin(min, graf.liczba_wierzcholkow); //Czy dobrze?
        int u = node->vertex;

        for (const auto& [v, waga] : graf.listaSasiedztwa[u]) {
            if (odleglosc[u] + waga < odleglosc[v]) {
                odleglosc[v] = odleglosc[u] + waga;
                if (nodes[v] == nullptr) {
                    nodes[v] = new FibonacciNode(v, odleglosc[v]);
                    insert(min, nodes[v]);
                } else {
                    decreaseKey(min, nodes[v], odleglosc[v]);
                }
            }
        }
    }

    for (int i = 0; i < graf.liczba_wierzcholkow; ++i) {
        if (odleglosc[i] != INF)
            cout << i << ": " << odleglosc[i] << "\n";
        else
            cout << i << ": " << "2147483647" << "\n";
    }

    for (FibonacciNode* node : nodes) {
        if (node) delete node;
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
