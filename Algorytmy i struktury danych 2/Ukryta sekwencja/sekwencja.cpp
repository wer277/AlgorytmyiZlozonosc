#include <iostream>
#include <cmath>
using namespace std;

int fibonacci(int *index, int N){\
    int suma = 0;
    while(suma < N){
        suma = index[0] + index[1];
        index[0] = index[1];
        index[1] = suma;
    }
    return suma-N;
}


void algorytm(int *tab, int *wzor, int N, int M){
    bool b;
    int index[2];
    int P=0, ti=0, d=101, q=173, k = 0, t0=0;
    int h = 1;
    for(int i = 0; i < M - 1; ++i)
        h = (h * d) % q;
    for(int i = 0; i<M; i++){
       P = (d * P + wzor[i])%q;
       t0 = (d * t0 + tab[i])%q;
    }
    if(t0 == P){
        b = true;
        for(int j = 0; j<M; j++){
            if(wzor[j] != tab[j]){
                b = false;
                break;
            }
        }
        if(b){
            index[k] = 0;
            k++;
        }
    }
    for(int i = 1; i <= N - M; i++){
        ti = (d * (t0 - tab[i-1] * h) + tab[i-1+M])%q;
        if(ti < 0){
            ti = (ti+q);
        }
        t0 = ti;
        if(ti == P){
            b = true;
            for(int j = 0; j<M; j++){
                if(wzor[j] != tab[i+j]){
                    b = false;
                    break;
                }
            }
            if(b){
                index[k] = i;
                k++;
                if(k == 2){
                    break;
                }
            }
        }
    }
    if(k != 2){
        return;
    }
    cout<<fibonacci(index,N);
}

int main() {
    int N, M;
    cin>>N;
    int *tekst;
    tekst = new int[N];
    for (int i = 0; i < N; ++i) {
        cin>>tekst[i];
    }
    cin>>M;
    int *wzor = new int[M];
    for(int i = 0; i<M; i++){
        cin>>wzor[i];
    } 

    algorytm(tekst,wzor,N,M);
    return 0;
}
