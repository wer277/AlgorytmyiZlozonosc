#include <iostream>

using namespace std;

template <typename T>
class Vector{
public:
    T *tab;
    int maxRozmiar = 10;
    int licznik = 0;

    Vector(){
        tab = new T [maxRozmiar];
    }

    void push_back(const T &dane){
        if(licznik < maxRozmiar){
            if(dane != 0){
                tab[licznik] = dane;
                licznik++;
            }
        } else {
            if (maxRozmiar == 0) maxRozmiar = 1;
            else maxRozmiar *= 2;

            T *nTab = new unsigned int [maxRozmiar];

            for (int i = 0; i < licznik; ++i) {
                nTab[i] = tab[i];
            }

            delete[] tab;
            tab = nTab;

            tab[licznik] = dane;
            licznik++;
        }
    }

    T pop() {
        if (licznik <= 0) {
            return T();
        }

        T lEl = tab[licznik - 1];
        licznik--;

        if (licznik < maxRozmiar / 2 && maxRozmiar > 1) {
            maxRozmiar /= 2;
            T *nTab = new T[maxRozmiar];

            for (int i = 0; i < licznik; ++i) {
                nTab[i] = tab[i];
            }

            delete[] tab;
            tab = nTab;
        }

        return lEl;
    }


    void push(const T &dane, int index) {
        if (index < 0 || index > licznik) {
            cout<<"Indek jest za zakresem"<<"\n";
            return;
        }

        if (licznik >= maxRozmiar) {
            if (maxRozmiar == 0) maxRozmiar = 1;
            else maxRozmiar *= 2;

            T *nTab = new T[maxRozmiar];

            for (int i = 0; i < index; ++i) {
                nTab[i] = tab[i];
            }

            nTab[index] = dane;

            for (int i = index; i < licznik; ++i) {
                nTab[i + 1] = tab[i];
            }

            delete[] tab;
            tab = nTab;
            licznik++;
        } else {
            for (int i = licznik; i > index; --i) {
                tab[i] = tab[i - 1];
            }

            tab[index] = dane;
            licznik++;
        }
    }

    void swap(T * &a, T* &b){
        T *c;
        c = a;
        a = b;
        b = c;
    }

    void clear() {
        licznik = 0;
        if (tab != nullptr) {
            delete[] tab;
            tab = nullptr;
            maxRozmiar = 0;
        }
    }

    int size(){
        return licznik;
    }

    T& operator[](int index) {
        if (index >= 0 && index < licznik) {
            return tab[index];
        } else {
            cout << 0;
        }
    }
};



int main() {
    unsigned int dane = 2147483647;
    Vector<unsigned int> vector;
    while (dane != 0) {
        std::cin >> dane;
        vector.push_back(dane);
    }

    for (int i = vector.size() - 1; i >= 0; --i) {
        std::cout << vector.tab[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
