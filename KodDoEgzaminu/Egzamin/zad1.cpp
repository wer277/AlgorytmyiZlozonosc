#include <iostream>

using namespace std;

struct Dane{
    int key;
    int value;

    Dane(int key = 0, int value = 0): key(key), value(value){}

    bool operator > (const Dane &other) const{
        return value > other.value;
    }

    bool operator < (const Dane &other) const{
        return value < other.value;
    }

    bool operator <= (const Dane &other) const{
        return value <= other.value;
    }

    bool operator >= (const Dane &other) const{
        return value >= other.value;
    }
};

void insertionSort(Dane *tab, int s, int n){
    for(int i = s+1; i<=n; i++){
        Dane key = tab[i];
        int j = i-1;
        while(j>=s && tab[j] > key){
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = key;
    }
}

void countingSort(Dane *tab, int maxValue, int n){
    int *countingTab;
    int size = maxValue + 1;
    countingTab = new int [size](); 

    for(int i = 0; i<n; i++){
        countingTab[tab[i].value]++;
    }

    for(int i = 1; i<size; i++){
        countingTab[i] += countingTab[i - 1];
    }

    Dane *sortedTab = new Dane[n];

    for(int i = n-1; i>=0; i--){
        int pom = countingTab[tab[i].value]-1;
        sortedTab[pom] = tab[i];
        countingTab[tab[i].value]--;
    }

    for(int i = 0; i<n; i++){
        tab[i] = sortedTab[i];
    }

    delete [] countingTab;
    delete [] sortedTab;

}

int main(){
    int n,p,k,l,w;
    cin>>n>>p>>k;
    Dane *tab = new Dane[n];
    for(int i = 0; i<n; i++){
        cin>>l>>w;
        tab[i].key = w;
        tab[i].value = l;
    }
    //insertionSort(tab, 0, n-1);
    countingSort(tab, k, n);
    for(int i = 0; i<n; i++){
        cout<<tab[i].key<<" ";
    }
    return 0;
}
