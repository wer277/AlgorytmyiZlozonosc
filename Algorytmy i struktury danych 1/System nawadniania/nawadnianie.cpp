#include <iostream>
#include<stack>
using namespace std;
class nawadnianie{
    int s, c, p;
public:
    nawadnianie(int s, int c, int p);
    int getS() const;
    int getC() const;
    int getP() const;
    nawadnianie();
    void setS(int s);
    void setC(int c);
    void setP(int p);
    void plus(){
        p++;
    }
    void plusS(int l){
        s += l;
    }
    void plusC(int l){
        c += l;
    }
};

int nawadnianie::getS() const {
    return s;
}

int nawadnianie::getC() const {
    return c;
}

int nawadnianie::getP() const {
    return p;
}

void nawadnianie::setS(int s) {
    nawadnianie::s = s;
}

void nawadnianie::setC(int c) {
    nawadnianie::c = c;
}

void nawadnianie::setP(int p) {
    nawadnianie::p = p;
}

nawadnianie::nawadnianie(int s, int c, int p) : s(s), c(c), p(p) {}

nawadnianie::nawadnianie() {

}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t, n, min = 0, Minmax;
    int pomocnik;
    stack<nawadnianie> stos;
    nawadnianie a;
    cin>>t;
    for (int i = 0; i < t; i++)
    {
        cin>>n;
        nawadnianie *opis;
        opis = new nawadnianie[n];
        for (int j = 0; j < n; j++) {
            cin>>pomocnik;
            opis[j].setS(pomocnik);
            cin>>pomocnik;
            opis[j].setC(pomocnik);
            opis[j].setP(j);
            Minmax += opis[j].getC();
        }
        min = Minmax;
        for (int j = n - 1; j > -1; j--)
        {
            stos.push(opis[j]);
            while (!stos.empty()){
                if(stos.top().getC() > min){
                    stos.pop();
                } else{
                    if (stos.top().getS() == 0)
                        if (min > stos.top().getC())
                            min = stos.top().getC();
                    if (stos.top().getP() < n - 1){

                        stos.top().plus();
                        a = opis[stos.top().getP()];
                        a.plusC(stos.top().getC());
                        a.plusS(stos.top().getS());
                        stos.push(a);
                    } else
                         stos.pop();
                }
            }
        }
        if (min != Minmax)
            cout<<min<<"\n";
        else
            cout<<"NIE"<<"\n";
        delete[] opis;
    }
    return 0;
}
