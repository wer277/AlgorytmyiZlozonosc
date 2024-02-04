struct Node {
    string key; // Klucz węzła
    vector<string> values; // Wartości węzła
    Node *next; // Wskaźnik na następny węzł

    Node(string key, string value) : key(key), next(nullptr) { // Konstruktor węzła
        values.push_back(value); // Dodanie wartości do wektora wartości
    }
}; // Złożoność: O(1)

struct HashTab {
    int size; // Rozmiar tablicy
    vector<Node*> nodes; // Wektor węzłów
    int itemsCount; // Liczba elementów w tablicy

    HashTab(int size) : size(size), itemsCount(0) { // Konstruktor tablicy
        nodes.resize(size, nullptr); // Inicjalizacja wektora węzłów
    } // Złożoność: O(n)

    ~HashTab() { // Destruktor tablicy
        clearNodes(); // Czyszczenie węzłów
    }

    void clearNodes() { // Czyszczenie węzłów
        for (auto& node : nodes) { // Przejście przez wszystkie węzły
            while (node != nullptr) { // Dopóki węzeł nie jest pusty
                Node* temp = node; // Przechowanie aktualnego węzła
                node = node->next; // Przejście do następnego węzła
                delete temp; // Usunięcie aktualnego węzła
            }
        }
    } // Złożoność: O(n)

    int hashFunction(string const& key, int modSize) { // Funkcja haszująca
        int hashValue = 0; // Inicjalizacja wartości haszowania
        for (char c : key) { // Przejście przez wszystkie znaki klucza
            hashValue = (hashValue * 31 + c) % modSize; // Obliczenie wartości haszowania
        }
        return hashValue; // Zwrócenie wartości haszowania
    } // Złożoność: O(k), gdzie k to długość klucza

    void resize() { // Zmiana rozmiaru tablicy
        int newSize = size * 2; // Nowy rozmiar to dwa razy aktualny rozmiar
        vector<Node*> newNodes(newSize, nullptr); // Nowy wektor węzłów

        for (int i = 0; i < size; ++i) { // Przejście przez wszystkie węzły
            Node* node = nodes[i]; // Aktualny węzeł
            while (node != nullptr) { // Dopóki węzeł nie jest pusty
                Node* nextNode = node->next; // Następny węzeł

                int index = hashFunction(node->key, newSize); // Obliczenie indeksu dla nowego rozmiaru
                if (newNodes[index] == nullptr) { // Jeśli nowy węzeł jest pusty
                    node->next = nullptr; // Ustawienie następnego węzła na pusty
                    newNodes[index] = node; // Przypisanie aktualnego węzła do nowego węzła
                } else {
                    // Dodajemy na koniec listy, aby zachować kolejność
                    Node* last = newNodes[index]; // Ostatni węzeł
                    while (last->next != nullptr) { // Dopóki następny węzeł nie jest pusty
                        last = last->next; // Przejście do następnego węzła
                    }
                    last->next = node; // Przypisanie aktualnego węzła do następnego węzła
                    node->next = nullptr; // Ustawienie następnego węzła na pusty
                }

                node = nextNode; // Przejście do następnego węzła
            }
        }

        nodes.swap(newNodes); // Zamiana wektorów węzłów
        size = newSize; // Aktualizacja rozmiaru
    } // Złożoność: O(n)

    void checkAndResizeIfNeeded() { // Sprawdzenie i zmiana rozmiaru jeśli potrzebne
        if (itemsCount >= 0.7 * size) { // Jeśli liczba elementów jest większa lub równa 70% rozmiaru
            resize(); // Zmiana rozmiaru
        }
    } // Złożoność: O(1) w przypadku braku zmiany rozmiaru, O(n) w przypadku zmiany rozmiaru

    void insert(string key, string value) { // Wstawienie elementu do tablicy
        checkAndResizeIfNeeded(); // Sprawdzenie i zmiana rozmiaru jeśli potrzebne

        int index = hashFunction(key, size); // Obliczenie indeksu dla klucza
        Node* prev = nullptr; // Poprzedni węzeł
        Node* node = nodes[index]; // Aktualny węzeł

        while (node != nullptr && node->key != key) { // Dopóki węzeł nie jest pusty i klucz węzła nie jest równy kluczowi
            prev = node; // Przechowanie aktualnego węzła
            node = node->next; // Przejście do następnego węzła
        }

        if (node == nullptr) { // Jeśli węzeł jest pusty
            node = new Node(key, value); // Utworzenie nowego węzła
            if (prev == nullptr) { // Jeśli poprzedni węzeł jest pusty
                nodes[index] = node; // Przypisanie nowego węzła do wektora węzłów
            } else {
                prev->next = node; // Przypisanie nowego węzła do następnego węzła
            }
            itemsCount++; // Zwiększenie liczby elementów
        } else {
            node->values.push_back(value); // Dodanie wartości do wektora wartości
        }
    } // Złożoność: O(1) w przypadku braku kolizji, O(n) w przypadku kolizji

    vector<string> search(string key) { // Wyszukiwanie elementu w tablicy
        int index = hashFunction(key, size); // Obliczenie indeksu dla klucza
        Node* node = nodes[index]; // Aktualny węzeł

        while (node != nullptr) { // Dopóki węzeł nie jest pusty
            if (node->key == key) { // Jeśli klucz węzła jest równy kluczowi
                return node->values; // Zwrócenie wartości węzła
            }
            node = node->next; // Przejście do następnego węzła
        }

        return vector<string>(); // Zwrócenie pustego wektora, jeśli nie znaleziono
    } // Złożoność: O(1) w przypadku braku kolizji, O(n) w przypadku kolizji
};

int main() {
    int s = 16; // początkowy rozmiar tablicy
    int n;
    cin >> n;
    cin.ignore();

    HashTab nameToSurname(s); // Utworzenie tablicy dla imion i nazwisk
    HashTab surnameToName(s); // Utworzenie tablicy dla nazwisk i imion

    char op;
    string name, surname;

    for (int i = 0; i < n; i++) { // Przejście przez wszystkie operacje
        cin >> op; // Wczytanie operacji
        cin.ignore();
        if (op == 'd') { // Jeśli operacja to 'd'
            getline(cin, name); // Wczytanie imienia
            getline(cin, surname); //
