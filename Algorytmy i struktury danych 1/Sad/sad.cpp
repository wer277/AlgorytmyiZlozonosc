#include <iostream>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    int liczba, index = 0;
    cin >> n >> m;
    int **tab = new int *[2];
    for (int i = 0; i < 2; i++)
        tab[i] = new int[m];

    if(m == 1){
        for(int i = 0; i < n; i++ ){
            cin>>liczba;
            index +=liczba;
        }
        cout<<0<<" "<<index;
        return 0;
    }
    for (int j = 0; j < m; j++)
        cin >> tab[0][j];
    int k = 0;
    for (int i = 1; i < n; i++, k = (i - 1) % 2) {
            cin >> liczba;
            if (tab[k][0] > tab[k][1])
                tab[(k + 1) % 2][0] = tab[k][0] + liczba;       //dla j = 0
            else
                tab[(k + 1) % 2][0] = tab[k][1] + liczba;
            for (int j = 1; j < m - 1; j++) {                     //dla j>0
                cin >> liczba;
                if (tab[k][j - 1] >= tab[k][j] && tab[k][j - 1] >= tab[k][j + 1])
                    tab[(k + 1) % 2][j] = tab[k][j - 1] + liczba;
                else if (tab[k][j] >= tab[k][j + 1] && tab[k][j] >= tab[k][j - 1])
                    tab[(k + 1) % 2][j] = tab[k][j] + liczba;
                else
                    tab[(k + 1) % 2][j] = tab[k][j + 1] + liczba;

            }
            cin >> liczba;
            tab[(k + 1) % 2][m - 1] = tab[k][m - 1] > tab[k][m - 2] ? tab[k][m - 1] + liczba : tab[k][m - 2] + liczba;

        
    }
    int wynik = tab[k][0];
    for (int i = 1; i < m; i++) {
        if (wynik < tab[k][i]){
            wynik = tab[k][i];
            index = i;
        }
    }
    cout<<index<<" "<<wynik;
        for (int i = 0; i < 2; i++) {
            delete tab[i];
        }

        delete[] tab;
        return 0;
    }
