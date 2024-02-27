#include <iostream>
struct warzywo {
    std::string nazwa;
    float z;
    int d, m;
};
bool cmp(int kryteria, const warzywo& a, const warzywo& b) {
    switch (kryteria)
    {
        case 1:
            if (a.z > b.z)return true;
            else return false;
        case 2:
            if (a.d > b.d)return true;
            else return false;
        case 3:
            if (a.m > b.m)return true;
            else return false;
    }
}
void wedlugKryterii(warzywo* tab, int kryteria[], int n) {
    for (int k = 0; k < 3; k++) {
        for (int i = 1; i < n; i++)
        {
            int j;
            warzywo temp = tab[i];
            j = i - 1;
            while (cmp(kryteria[k],temp,tab[j])&& j >= 0)
            {
                tab[j + 1] = tab[j];
                j = j - 1;
            }
            tab[j + 1] = temp;
        }
    }
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);


    int n;
    std::cin >> n;
    warzywo *pWarzywo, *niepwarzywo;
    pWarzywo = new warzywo[n];
    niepwarzywo = new warzywo[n];
    int tab[3];
    for (int i = 0; i < 3; i++) {//podawanie kolejności kryteriów
        std::cin >> tab[2 - i];
    }
    for (int i = 0; i < n; i++) { //wczytywanie danych do listy
        std::cin >> pWarzywo[i].nazwa >> pWarzywo[i].z >> pWarzywo[i].d >> pWarzywo[i].m;
    }


    for (int i = 0; i < n; i++) {
        std::cin >> niepwarzywo[i].nazwa >> niepwarzywo[i].z >> niepwarzywo[i].d >> niepwarzywo[i].m;
    }

    wedlugKryterii(pWarzywo, tab, n);
    wedlugKryterii(niepwarzywo, tab, n);

    for (int i = 0; i < n; i++) {
        std::cout << pWarzywo[i].nazwa << '-' << niepwarzywo[i].nazwa << ' ';
    }

    delete[] niepwarzywo;
    delete[] pWarzywo;
    return 0;
}
