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

Node* rightRotation(Node *&root, Node *&node){
    Node *childNode = node->left;
    node->left = childNode->right;
    if(childNode->right != nullptr){
        childNode->right->parent = node;
    }
    childNode->parent = node->parent;
    if(node->parent == nullptr){
        root = childNode;
    } else if(node == node->parent->right){
        node->parent->right = childNode;
    } else{
        node->parent->left = childNode;
    }
    childNode->right = node;
    node->parent = childNode;

    return childNode;
}

Node* leftRotation(Node *&root, Node *&node){
    Node *childNode = node->right;
    node->right = childNode->left;
    if(childNode->left != nullptr){
        childNode->left->parent = node;
    }
    childNode->parent = node->parent;
    if(node->parent == nullptr){
        root = childNode;
    } else if(node == node->parent->left){
        node->parent->left = childNode;
    } else{
        node->parent->right = childNode;
    }
    childNode->left = node;
    node->parent = childNode;

    return childNode;
}

void splay(Node *&root, Node *&node){
    while(node != nullptr && node->parent != nullptr){
        if(node->parent->parent == nullptr){
            //Rotacja Zig lub Zag
            if(node->parent->left == node){
                rightRotation(root, node->parent);
            } else{
                leftRotation(root, node->parent);
            }
        } else if(node->parent->left == node && node->parent->parent->left == node->parent){
            //Rotacja Zig-Zig
            rightRotation(root, node->parent->parent);
            rightRotation(root, node->parent);
        } else if(node->parent->right == node && node->parent->parent->right == node->parent){
            //Rotacja Zag-Zag
            leftRotation(root, node->parent->parent);
            leftRotation(root, node->parent);
        } else if(node->parent->left == node && node->parent->parent->right == node->parent){
            //Rotacja Zag-Zig
            rightRotation(root, node->parent->parent);
            leftRotation(root, node->parent);
        } else{
            //Rotacja Zig-Zag
            leftRotation(root, node->parent->parent);
            rightRotation(root, node->parent);
        }
    }
}

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
        splay(node, node);
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
    insert(2, 2, tree);
    search(2, tree);
    return 0;
}
