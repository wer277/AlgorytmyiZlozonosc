#include <iostream>

using namespace std;

int main(){
    int size = 16;
    int licznik = 0;
    unsigned int liczba;
    unsigned int *tab;
    tab = new unsigned int[size];
    
    cin>>liczba;

    while(liczba != 0){
        if(licznik < size){
            tab[licznik] = liczba;
        } else{
            size = size * 2;
            unsigned int *newTab;
            newTab = new unsigned int [size];
            for(int i = 0; i<licznik; i++){
                newTab[i] = tab[i];
            }
            newTab[licznik] = liczba;

            delete [] tab;

            tab = newTab;
        }
        licznik++;
        cin>>liczba;
    }


    for(int i = licznik - 1; i>=0; i--){
        cout<<tab[i]<<"\n";
    }

    return 0;
}
