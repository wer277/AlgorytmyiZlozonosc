#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

//Jeśli jest z jednej strony to jest operacja zig
//Wypisuje po find w kolejności dodania do bazy danych. Kolejność dodania zapewniona jest przez listę vector

// Struktura węzła drzewa Splay
struct Node {
    Node *left, *right, *parent; // Wskaźniki na lewe i prawe dziecko oraz rodzica
    string key; // Klucz węzła
    vector<string> values; // Wektor przechowujący wartości

    // Konstruktor węzła. Złożoność czasowa: O(1)
    Node(string keys, Node *node = nullptr) {
        key = keys; // Przypisanie klucza
        parent = node; // Przypisanie rodzica
        right = left = nullptr; // Inicjalizacja wskaźników na dzieci jako nullptr
    }
};

Node *root = nullptr; // Inicjalizacja korzenia drzewa jako nullptr

// Funkcja wykonująca prawą rotację. Złożoność czasowa: O(1)
Node* r_right(Node *&root, Node *currentNode){
    Node *childNode = currentNode->left; // Przypisanie lewego dziecka do zmiennej childNode
    currentNode->left = childNode->right; // Przypisanie prawego dziecka childNode jako lewe dziecko currentNode

    if(childNode->right != nullptr){ // Jeśli prawe dziecko childNode istnieje
        childNode->right->parent = currentNode; // Ustawiamy jego rodzica jako currentNode
    }
    childNode->parent = currentNode->parent; // Ustawiamy rodzica childNode jako rodzica currentNode
    if(currentNode->parent == nullptr){ // Jeśli currentNode jest korzeniem
        root = childNode; // Ustawiamy childNode jako nowy korzeń
    } else if(currentNode == currentNode->parent->right){ // Jeśli currentNode jest prawym dzieckiem swojego rodzica
        currentNode->parent->right = childNode; // Ustawiamy childNode jako prawe dziecko rodzica currentNode
    } else{ // Jeśli currentNode jest lewym dzieckiem swojego rodzica
        currentNode->parent->left = childNode; // Ustawiamy childNode jako lewe dziecko rodzica currentNode
    }
    childNode->right = currentNode; // Ustawiamy currentNode jako prawe dziecko childNode
    currentNode->parent = childNode; // Ustawiamy childNode jako rodzica currentNode

    return childNode; // Zwracamy childNode
}

// Funkcja wykonująca lewą rotację. Złożoność czasowa: O(1)
Node* r_left(Node *&root, Node *currentNode){
    Node *childNode = currentNode->right; // Przypisanie prawego dziecka do zmiennej childNode
    currentNode->right = childNode->left; // Przypisanie lewego dziecka childNode jako prawe dziecko currentNode

    if(childNode->left != nullptr){ // Jeśli lewe dziecko childNode istnieje
        childNode->left->parent = currentNode; // Ustawiamy jego rodzica jako currentNode
    }
    childNode->parent = currentNode->parent; // Ustawiamy rodzica childNode jako rodzica currentNode
    if(currentNode->parent == nullptr){ // Jeśli currentNode jest korzeniem
        root = childNode; // Ustawiamy childNode jako nowy korzeń
    } else if(currentNode == currentNode->parent->left){ // Jeśli currentNode jest lewym dzieckiem swojego rodzica
        currentNode->parent->left = childNode; // Ustawiamy childNode jako lewe dziecko rodzica currentNode
    } else{ // Jeśli currentNode jest prawym dzieckiem swojego rodzica
        currentNode->parent->right = childNode; // Ustawiamy childNode jako prawe dziecko rodzica currentNode
    }
    childNode->left = currentNode; // Ustawiamy currentNode jako lewe dziecko childNode
    currentNode->parent = childNode; // Ustawiamy childNode jako rodzica currentNode

    return childNode; // Zwracamy childNode
}

// Funkcja wyszukująca klucz w drzewie. Złożoność czasowa: O(log n)
Node* search(Node *&node, const string &key){
    if(node == nullptr || node->key == key) // Jeśli węzeł jest pusty lub klucz węzła jest równy szukanemu kluczowi
        return node; // Zwracamy węzeł
    if (key < node->key) { // Jeśli szukany klucz jest mniejszy od klucza węzła
        search(node->left, key); // Szukamy klucza w lewym poddrzewie
    } else if (key > node->key) { // Jeśli szukany klucz jest większy od klucza węzła
        search(node->right ,key); // Szukamy klucza w prawym poddrzewie
    }
    return node; // Zwracamy węzeł
}

// Funkcja wykonująca operację splay na danym węźle. Złożoność czasowa: O(log n)
void splay(Node *&root, Node *node) {
    while(node != nullptr && node->parent != nullptr){ // Dopóki węzeł i jego rodzic istnieją
        if(node->parent->parent == nullptr){ // Jeśli rodzic węzła jest korzeniem
            //Rotacja Zig lub Zag
            if(node->parent->left == node){ // Jeśli węzeł jest lewym dzieckiem swojego rodzica
                r_right(root, node->parent); // Wykonujemy prawą rotację na rodzicu węzła
            } else{ // Jeśli węzeł jest prawym dzieckiem swojego rodzica
                r_left(root, node->parent); // Wykonujemy lewą rotację na rodzicu węzła
            }
        } else if(node->parent->left == node && node->parent->parent->left == node->parent){ // Jeśli węzeł i jego rodzic są lewymi dziećmi swoich rodziców
            //Rotacja Zig-Zig
            r_right(root, node->parent->parent); // Wykonujemy prawą rotację na dziadku węzła
            r_right(root, node->parent); // Wykonujemy prawą rotację na rodzicu węzła
        } else if(node->parent->right == node && node->parent->parent->right == node->parent){ // Jeśli węzeł i jego rodzic są prawymi dziećmi swoich rodziców
            //Rotacja Zag-Zag
            r_left(root, node->parent->parent); // Wykonujemy lewą rotację na dziadku węzła
            r_left(root, node->parent); // Wykonujemy lewą rotację na rodzicu węzła
        } else if(node->parent->left == node && node->parent->parent->right == node->parent){ // Jeśli węzeł jest lewym dzieckiem swojego rodzica, a rodzic węzła jest prawym dzieckiem swojego rodzica
            //Rotacja Zag-Zig
            r_right(root, node->parent->parent); // Wykonujemy prawą rotację na dziadku węzła
            r_left(root, node->parent); // Wykonujemy lewą rotację na rodzicu węzła
        } else{ // Jeśli węzeł jest prawym dzieckiem swojego rodzica, a rodzic węzła jest lewym dzieckiem swojego rodzica
            //Rotacja Zig-Zag
            r_left(root, node->parent->parent); // Wykonujemy lewą rotację na dziadku węzła
            r_right(root, node->parent); // Wykonujemy prawą rotację na rodzicu węzła
        }
    }
}

// Funkcja wstawiająca klucz do drzewa. Złożoność czasowa: O(log n)
void insertion(const string &key, const string &value, Node *&node) {
    if (node == nullptr) { // Jeśli węzeł jest pusty
        node = new Node(key); // Tworzymy nowy węzeł z kluczem
        node->values.push_back(value); // Dodajemy wartość do wektora wartości węzła
    } else if (node->key == key) { // Jeśli klucz węzła jest równy wstawianemu kluczowi
        node->values.push_back(value); // Dodajemy wartość do wektora wartości węzła
    } else if (key < node->key) { // Jeśli wstawiany klucz jest mniejszy od klucza węzła


// Funkcja wyszukująca klucz w drzewie i wykonująca operację splay. Złożoność czasowa: O(log n)
        void search_splay(const string &key, Node *&root) {
            if (root == nullptr) { // Jeśli korzeń jest pusty
                // Klucz nie znaleziony, nie robimy splay
                return;
            }
            if (key < root->key) { // Jeśli szukany klucz jest mniejszy od klucza korzenia
                // Idź w lewo, jeśli klucz jest mniejszy
                search_splay(key, root->left); // Szukamy klucza w lewym poddrzewie
            } else if (key > root->key) { // Jeśli szukany klucz jest większy od klucza korzenia
                // Idź w prawo, jeśli klucz jest większy
                search_splay(key, root->right); // Szukamy klucza w prawym poddrzewie
            } else { // Jeśli klucz korzenia jest równy szukanemu kluczowi
                // Klucz znaleziony
                // Wykonaj operację splay na znalezionym węźle
                splay(root, root); // Wykonujemy operację splay na korzeniu

                // Wypisz wszystkie values z wektora
                for (const string &osoba: root->values) { // Dla każdej osoby w wektorze wartości korzenia
                    cout << osoba << "\n"; // Wyświetlamy osobę
                }
            }
        }
        }
int main() {
    Node *rootNames = nullptr; // Drzewo dla imion
    Node *rootSurnames = nullptr; // Drzewo dla nazwisk
    vector<string> dane;
    int n;
    cin >> n;
    cin.ignore();
    char op;
    for(int i = 0; i < n; i++) {
        cin >> op;
        cin.ignore(); // Ignoruje znak nowej linii po odczytaniu opcji
        string name, surname;
        if(op == 'd') {
            getline(cin, name);
            getline(cin, surname);
            insertion(name, surname, rootNames);
            insertion(surname, name, rootSurnames);
        } else if(op == 'i'){
            getline(cin, name);
            search_splay(name, rootNames);
        } else if(op =='n'){
            getline(cin, surname);
            search_splay(surname, rootSurnames);
        }
    }
//    cout<<"Names:"<<endl;
//    inorder(rootNames);
//    cout<<"Surnames"<<endl;
//    inorder(rootSurnames);
    return 0;

}
