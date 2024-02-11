#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int pomQuickSort(int *tab, int s, int n){
    int index = s+rand()%n;
    swap(tab[index], tab[s+n-1]);
    int pivot = tab[s+n-1];
    int i = s-1;

    for(int j = s; j<s+n-1; j++){
        if(tab[j] < pivot){
            i++;
            swap(tab[i], tab[j]);
        }
    }
    swap(tab[i+1], tab[s+n-1]);
    return i+1;
}

void quickSort(int *tab, int s, int n){
    if(n<=1) return;
    int pivot = pomQuickSort(tab,s,n);
    quickSort(tab,s,pivot-s);
    quickSort(tab,pivot+1,s+n-pivot-1);
}

void downHeap(int *tab, int s, int n){
    int largest = s;
    int left = 2*s+1;
    int right = 2*s+2;

    if(left<n && tab[left] > tab[largest])
        largest = left;
    if(right<n && tab[right] > tab[largest])
        largest = right;

    if(largest != s){
        swap(tab[s], tab[largest]);
        downHeap(tab, largest,n);
    }
}

void buildHeap(int *tab, int n){
    for(int i = n/2-1; i>=0; i--){
        downHeap(tab,i,n);
    }
}

void heapSorted(int *tab, int n){
    buildHeap(tab,n);
    for(int i = n-1; i>0; i--){
        swap(tab[0], tab[i]);
        downHeap(tab, 0, i);
    }
}

void insertionSort(int *tab, int s, int n){
    for(int i = s + 1; i<=n; i++){
        int key = tab[i];
        int j = i - 1;
        while(j>=s && tab[j] > key){
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = key;
    }
}

void introSort(int *tab, int s, int n){
    int depthLimit = 2*static_cast<int>(std::log2(n));
    if(depthLimit<16)
        insertionSort(tab,s,s+n-1);
    else if(depthLimit == 0){
        heapSorted(tab+s, n);
    } else{
        int pivot = pomQuickSort(tab, s, n);
        introSort(tab, s, pivot-s);
        introSort(tab,pivot+1,s+n-pivot-1);
    }
}


const int RUN = 32;

void merge(int *tab, int l, int n, int r){
    int n1 = n-l+1;
    int n2 = n-r;
    int *L = new int [n1];
    int *R = new int [n2];

    for(int i = 0; i<n1; i++)
        L[i] = tab[l+i];
    for(int j = 0; j<n2; j++)
        R[j] = tab[n+j+1];

    int i = 0;
    int j = 0;
    int k = l;
    while(i<n1 && j<n2){
        if(L[i] <= R[j]){
            tab[k] = L[i];
            i++;
        } else{
            tab[k] = R[i];
            i++;
        }
        k++;
    }
    while(i<n1){
        tab[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        tab[k] = R[j];
        j++;
        k++;
    }
}

void timsortmerge(int *tab, int n){
    for(int size = RUN; size<n; size = 2*size){
        for(int left = 0; left<n; left+=2*size){
            int mid = left + size -1;
            int right = std::min((left+2*size-1), (n-1));
            if(mid < right){
                merge(tab,left,mid,right);
            }
        }
    }
}

void timSort(int *tab, int n){
    for(int i =0; i<n; i+=RUN){
        insertionSort(tab,i,std::min((i+RUN-1), (n-1)));
    }
    timsortmerge(tab,n);
}

int main() {
    int tab[] = {1,1,9,3,18,16,12};
    int n = 7;

    quickSort(tab,0,n);
    for(int i = 0; i<n; i++){
        cout<<tab[i]<<"\n";
    }
    return 0;
}
