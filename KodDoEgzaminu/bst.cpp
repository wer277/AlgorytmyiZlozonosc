#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key;
    Node *left, *right, *parent;
    vector<int> values;

    Node(int keys, Node *node = nullptr) {
        key = keys;
        parent = node;
        left = right = nullptr;
    }
};

void insert(const int &key, const int value, Node *&node) {
    if (node == nullptr) {
        node = new Node(key);
        node->values.push_back(value);
    } else if (node->key == key) {
        node->values.push_back(key);
    } else if (key < node->key) {
        insert(key, value, node->left);
    } else {
        insert(key, value, node->right);
    }
}

void search(int key, Node *node) {
    if (node == nullptr) {
        return;
    }
    if (key < node->key) {
        search(key, node->left);
    } else if (key > node->key) {
        search(key, node->right);
    } else {
        for(int i=0; i<node->values.size(); i++){
            cout<<node->values[i]<<"\n";
        }
//        for (const int &liczba: node->values) {
//            cout << liczba << "\n";
//        }
//        cout<<node->key<<"\n";
    }
}


int main() {
    Node *tree = nullptr;
    int n, liczba, set;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>liczba >> set;
        insert(liczba, set, tree);
    }

    int key;
    cin>>key;
    cout<<"Znalezione"<<"\n";
    search(key,tree);
    return 0;
}
