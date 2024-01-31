#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

//Jeśli jest z jednej strony to jest operacja zig
//Wypisuje po find w kolejności dodania do bazy danych. Kolejność dodania zapewniona jest przez listę vector

struct Node {
    Node *left, *right, *parent;
    string key;
    vector<string> values;

    Node(string keys, Node *node = nullptr) {
        key = keys;
        parent = node;
        right = left = nullptr;
    }
};

Node *root = nullptr;

Node* r_right(Node *&root, Node *currentNode){
    Node *childNode = currentNode->left;
    currentNode->left = childNode->right;

    if(childNode->right != nullptr){
        childNode->right->parent = currentNode;
    }
    childNode->parent = currentNode->parent;
    if(currentNode->parent == nullptr){
        root = childNode;
    } else if(currentNode == currentNode->parent->right){
        currentNode->parent->right = childNode;
    } else{
        currentNode->parent->left = childNode;
    }
    childNode->right = currentNode;
    currentNode->parent = childNode;

    return childNode;
}

Node* r_left(Node *&root, Node *currentNode){
    Node *childNode = currentNode->right;
    currentNode->right = childNode->left;

    if(childNode->left != nullptr){
        childNode->left->parent = currentNode;
    }
    childNode->parent = currentNode->parent;
    if(currentNode->parent == nullptr){
        root = childNode;
    } else if(currentNode == currentNode->parent->left){
        currentNode->parent->left = childNode;
    } else{
        currentNode->parent->right = childNode;
    }
    childNode->left = currentNode;
    currentNode->parent = childNode;

    return childNode;
}

Node* search(Node *&node, const string &key){
    if(node == nullptr || node->key == key)
        return node;
    if (key < node->key) {
        // Idź w lewo, jeśli klucz jest mniejszy
        search(node->left, key);
    } else if (key > node->key) {
        // Idź w prawo, jeśli klucz jest większy
        search(node->right ,key);
    }
    return node;
}

void splay(Node *&root, Node *node) {
    //Node* node = search(root, key);
    while(node != nullptr && node->parent != nullptr){
        if(node->parent->parent == nullptr){
            //Rotacja Zig lub Zag
            if(node->parent->left == node){
                r_right(root, node->parent);
            } else{
                r_left(root, node->parent);
            }
        } else if(node->parent->left == node && node->parent->parent->left == node->parent){
            //Rotacja Zig-Zig
            r_right(root, node->parent->parent);
            r_right(root, node->parent);
        } else if(node->parent->right == node && node->parent->parent->right == node->parent){
            //Rotacja Zag-Zag
            r_left(root, node->parent->parent);
            r_left(root, node->parent);
        } else if(node->parent->left == node && node->parent->parent->right == node->parent){
            //Rotacja Zag-Zig
            r_right(root, node->parent->parent);
            r_left(root, node->parent);
        } else{
            //Rotacja Zig-Zag
            r_left(root, node->parent->parent);
            r_right(root, node->parent);
        }
    }
}

void insertion(const string &key, const string &value, Node *&node) {
    if (node == nullptr) {
        node = new Node(key);
        node->values.push_back(value);
    } else if (node->key == key) {
        node->values.push_back(value);
    } else if (key < node->key) {
        insertion(key, value, node->left);
    } else {
        insertion(key, value, node->right);
    }
}

void search_splay(const string &key, Node *&root) {
    if (root == nullptr) {
        // Klucz nie znaleziony, nie robimy splay
        return;
    }
    if (key < root->key) {
        // Idź w lewo, jeśli klucz jest mniejszy
        search_splay(key, root->left);
    } else if (key > root->key) {
        // Idź w prawo, jeśli klucz jest większy
        search_splay(key, root->right);
    } else {
        // Klucz znaleziony
        // Wykonaj operację splay na znalezionym węźle
        splay(root, root);

        // Wypisz wszystkie values z wektora
        for (const string &osoba: root->values) {
            cout << osoba << "\n";
        }
    }
}

void inorder(Node* node) {
    if (node == nullptr) {
        return;
    }

    // Najpierw odwiedź lewe poddrzewo
    inorder(node->left);

    // Następnie wydrukuj dane węzła
    cout << "Klucz: " << node->key << "\n";
    cout << "Osoby: ";
    for (const string &osoba : node->values) {
        cout << osoba << " ";
    }
    cout << "\n";

    // Na końcu odwiedź prawe poddrzewo
    inorder(node->right);
}

void printVectorValues(Node* node) {
    if (node == nullptr) {
        return;
    }

    // Wypisz wartości z vectora w bieżącym węźle
    cout << "Klucz: " << node->key << "\n";
    cout << "Osoby: ";
    for (const string &osoba : node->values) {
        cout << osoba << " ";
    }
    cout << "\n";

    // Przejdź do lewego i prawego poddrzewa
    printVectorValues(node->left);
    printVectorValues(node->right);
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
