#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    string key;
    vector<string> values;
    Node *next;

    Node(string key, string value) : key(key), next(nullptr) {
        values.push_back(value);
    }
};

struct HashTab {
    int size;
    vector<Node*> nodes;
    int itemsCount;

    HashTab(int size) : size(size), itemsCount(0) {
        nodes.resize(size, nullptr);
    }

    ~HashTab() {
        clearNodes();
    }

    void clearNodes() {
        for (auto& node : nodes) {
            while (node != nullptr) {
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }

    int hashFunction(string const& key, int modSize) {
        int hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % modSize;
        }
        return hashValue;
    }

    void resize() {
        int newSize = size * 2;
        vector<Node*> newNodes(newSize, nullptr);

        for (int i = 0; i < size; ++i) {
            Node* node = nodes[i];
            while (node != nullptr) {
                Node* nextNode = node->next;

                int index = hashFunction(node->key, newSize);
                if (newNodes[index] == nullptr) {
                    node->next = nullptr;
                    newNodes[index] = node;
                } else {
                    // Dodajemy na koniec listy, aby zachować kolejność
                    Node* last = newNodes[index];
                    while (last->next != nullptr) {
                        last = last->next;
                    }
                    last->next = node;
                    node->next = nullptr;
                }

                node = nextNode;
            }
        }

        nodes.swap(newNodes);
        size = newSize;
    }


    void checkAndResizeIfNeeded() {
        if (itemsCount >= 0.7 * size) { // współczynnik ładownia 70%
            resize();
        }
    }

    void insert(string key, string value) {
        checkAndResizeIfNeeded();

        int index = hashFunction(key, size);
        Node* prev = nullptr;
        Node* node = nodes[index];

        while (node != nullptr && node->key != key) {
            prev = node;
            node = node->next;
        }

        if (node == nullptr) {
            node = new Node(key, value);
            if (prev == nullptr) {
                nodes[index] = node;
            } else {
                prev->next = node;
            }
            itemsCount++;
        } else {
            node->values.push_back(value);
        }
    }

    vector<string> search(string key) {
        int index = hashFunction(key, size);
        Node* node = nodes[index];

        while (node != nullptr) {
            if (node->key == key) {
                return node->values;
            }
            node = node->next;
        }

        return vector<string>(); // Pusty wektor, jeśli nie znaleziono
    }
};

int main() {
    int s = 16; // początkowy rozmiar tablicy
    int n;
    cin >> n;
    cin.ignore();

    HashTab nameToSurname(s);
    HashTab surnameToName(s);

    char op;
    string name, surname;

    for (int i = 0; i < n; i++) {
        cin >> op;
        cin.ignore();
        if (op == 'd') {
            getline(cin, name);
            getline(cin, surname);
            nameToSurname.insert(name, surname);
            surnameToName.insert(surname, name);
        } else if (op == 'i') {
            getline(cin, name);
            for (const auto& surname : nameToSurname.search(name)) {
                cout << surname << endl;
            }
        } else if (op == 'n') {
            getline(cin, surname);
            for (const auto& name : surnameToName.search(surname)) {
                cout << name << endl;
            }
        }
    }

    return 0;
}
