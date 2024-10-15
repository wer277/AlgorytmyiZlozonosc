#include <iostream>

using namespace std;
int main() {
std::ios_base::sync_with_stdio(false);
std::cin.tie(nullptr);
std::cout.tie(nullptr);
    int n,m,k;
    cin>>n>>k>>m;
    int *tab;
    tab = new int[n];
    int *tab2;
    tab2 = new int[n];
    char *tmp;
    tmp = new char[k];
    for(int i = 0; i<n; i++){
        cin>>tmp;
        tab[i] = 0;
        for (int j = 0; j < k; j++) {
            if(tmp[k-j-1] == 'X')
                tab[i] += 1<<j;
        }
    }
    int x,o;
    for (int i = 0; i < k; ++i) {
        x = 0;
        for (int j = 0; j < n; ++j) {
            if(tab[j] &(1<<i))
                x++;
        }
        o = n - x - 1;
        x = n-1;
        for(int j = n-1; j>=0; j--){
            if(tab[j] &(1<<i)){
                tab2[x] = tab[j];
                x--;
            } else{
                tab2[o] = tab[j];
                o--;
            }
        }
        for (int j = 0; j < n; ++j) {
            tab[j] = tab2[j];
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            if(tab[n-i-1] &(1<<k-1-j))
                cout<<"X";
            else
                cout<<"o";
        }
        cout<<"\n";
    }
}
