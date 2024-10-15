#include <iostream>
#include <queue>
using namespace std;

struct Data{
    int key;
    int id;
    float atr;
    string name;
};

struct Osoba{
    Osoba(Data *data) {
        this->id = data->id;
        this->imie = data->name;
        this->atrakcyjnosc = data->atr;
    }
    int id;
    string imie;
    float atrakcyjnosc;
};

struct Compare{
    bool operator()(const Osoba& o1, const Osoba& o2){
        if(o1.atrakcyjnosc == o2.atrakcyjnosc){
            return o1.id < o2.id;
        }
        return o1.atrakcyjnosc < o2.atrakcyjnosc;
    }
};


struct Node{
    Node *left,*right,*parent;
    int key;
    priority_queue<Osoba, vector<Osoba>, Compare> kolejka;
    Node (int keys, Node *node=nullptr){
        key = keys;
        parent = node;
        left = right = nullptr;
    }
};

void deleteNode(Node *pNode);
Node *root = nullptr;
bool pop = true;

void insertion(Data *data, Node *parent){
    if (root == nullptr){
        root = new Node(data->key, parent);
        root->kolejka.push(Osoba(data));
        return;
    }
    Node *node = root;
    while(node != nullptr){
        if(node->key > data->key) {
            if(node->left == nullptr){
                node->left = new Node(data->key, node);
                node->left->kolejka.push(Osoba(data));
                node = nullptr;
            } else{
                node = node->left;
            }
        } else if(node->key < data->key){
            if(node->right == nullptr){
                node->right = new Node(data->key, node);
                node->right->kolejka.push(Osoba(data));
                node = nullptr;
            } else{
                node = node->right;
            }
        } else if(node->key == data->key){
            node->kolejka.push(Osoba(data));
            node = nullptr;
        }
    }
}
/*void insertion(Data *data, Node *&node, Node *parent){
    if(node == nullptr) {
        node = new Node(data->key, parent);
        node->kolejka.push(Osoba(data));
        return;
    } else if(node->key == data->key) {
        node->kolejka.push(Osoba(data));
        return;
    } else if(node->key < data->key) {
        insertion(data, node->right, node);
    } else {
        insertion(data, node->left, node);
    }
}*/

void search(Data *data, Node *node){
    if(node == nullptr){
        cout<<"-\n";
    } else{
        if(node->key == data->key){
                Osoba o = node->kolejka.top();
                if (o.atrakcyjnosc >= data->atr) {
                    cout << o.imie << "\n";
                    node->kolejka.pop();
                    if (node->kolejka.empty()) {
                        deleteNode(node);                   //usuwamy WSZYTSKO!!!!!!!!!!!
                    }
                } else {
                    cout << "-\n";
                }
        } else if(data->key < node->key){
            node = node->left;
            search(data,node);
        } else if(data->key > node->key){
            node = node->right;
            search(data, node);
        }
    }
}

void deleteNode(Node *node){
    if(node == root) {
        if(node->right == nullptr && node->left == nullptr){
            root = nullptr;
        } else if(node->left != nullptr && node->right != nullptr){
            //tu mam dwoje dzieci
            pop = !pop;
            if(pop){
                Node *nastepnik = node->right;                                  //todo w druga strone
                while(nastepnik->left != nullptr){
                    nastepnik = nastepnik->left;
                }
                node->key = nastepnik->key;
                node->kolejka = nastepnik->kolejka;
                deleteNode(nastepnik);
            } else{
                Node *poprzednik = node->left;
                while(poprzednik->right != nullptr){
                    poprzednik = poprzednik->right;
                }
                node->key = poprzednik->key;
                node->kolejka = poprzednik->kolejka;
                deleteNode(poprzednik);
            }

        } else if(node->left){
            //jeśli ma jedno dziecko, z lewej strony
            Node* leftChild = node->left;
            root = leftChild;
        } else if(node->right){
            //jeśli ma jedno dziecko, z prawej strony
            Node* rightChild = node->right;
            root = rightChild;
        }
        return;
    }
    Node *parent = node->parent;
    bool isLeft = parent->key > node->key;
    if(node->right == nullptr && node->left == nullptr){                    //nie ma dzieci
        if(isLeft){
            parent->left = nullptr;
        } else{
            parent->right = nullptr;
        }
        } else if(node->left != nullptr && node->right != nullptr){         //ma oboje dzieci
        //tu mam dwoje dzieci
        pop = !pop;
        if(pop){
            Node *nastepnik = node->right;//todo w druga strone
            while(nastepnik->left != nullptr){
                nastepnik = nastepnik->left;
            }
            node->key = nastepnik->key;
            node->kolejka = nastepnik->kolejka;
            deleteNode(nastepnik);
        } else{
            Node *poprzednik = node->left;
            while(poprzednik->right != nullptr){
                poprzednik = poprzednik->right;
            }
            node->key = poprzednik->key;
            node->kolejka = poprzednik->kolejka;
            deleteNode(poprzednik);
        }
        } else if(node->left != nullptr && node->right == nullptr){
        //jeśli ma jedno dziecko, z lewej strony
        Node* leftChild = node->left;
        if(isLeft){
                parent->left = leftChild;
                leftChild->parent = parent;
            } else{
                parent->right = leftChild;
                leftChild->parent = parent;
            }

        } else if(node->right != nullptr && node->left == nullptr){
        //jeśli ma jedno dziecko, z prawej strony
        Node* rightChild = node->right;
        if(isLeft){
            //czy aktualny node jest lewym dzieckiem
                parent->left = rightChild;
                rightChild->parent = parent;
            } else{
                parent->right = rightChild;
                rightChild->parent = parent;
            }
    }
    }

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int N,Y,id=1;
    char znak;
    float X;
    Data *data;
    cin >> N;
    data = new Data[N];
    for (int i = 0; i < N; i++) {
        cin>>znak;
        if(znak == 'A'){
            cin >> X >> Y >> data[i].key >> data[i].name;
            data[i].id = id;
            data[i].atr = (X/5) * (Y/1000);
            insertion(data+i, nullptr);
            id++;
        } else if(znak == 'S'){
            cin >> data[i].key >> data[i].atr;
            Node *node = root;
            search(data+i,node);
        }
    }
    delete [] data;
    return 0;
}
