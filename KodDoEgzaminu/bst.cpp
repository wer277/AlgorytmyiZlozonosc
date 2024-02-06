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
        cout<<"Nie znaleziono"<<"\n";
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

void minValueNode(Node* node, Node* &minNode) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    minNode = current;
}

void deleteNode(Node* &root, int key) {
    if (root == nullptr) return;
    if (key < root->key)
        deleteNode(root->left, key);
    else if (key > root->key)
        deleteNode(root->right, key);
    else {
        if (root->left == nullptr) {
            Node *temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == nullptr) {
            Node *temp = root->left;
            delete root;
            root = temp;
        } else {
            Node* temp = nullptr;
            minValueNode(root->right, temp);
            root->key = temp->key;
            deleteNode(root->right, temp->key);
        }
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
    deleteNode(tree, 2);
    search(2, tree);
    search(1, tree);
    return 0;
}
