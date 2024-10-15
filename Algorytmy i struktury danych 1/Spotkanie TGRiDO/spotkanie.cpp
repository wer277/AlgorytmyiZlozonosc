#include <iostream>
#include <vector>
using namespace std;

void upheap(int*, int*, int);
void downheap(int*, int*, int);
int read_array(int*, int*, int);


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t, counter = 0;
    cin >> t;
    vector <int> result;
    for (int T = 0; T < t; T++) {
        int n;
        cin >> n;
        int* arr_val = new int[n + 1]; // 🙂
        int* arr_i = new int[n + 1];
        int last_index = n - read_array(arr_val, arr_i, n);
        /*        cout << endl;
                for (int i = 1; i <= last_index; i++) {
                    cout << arr_val[i] << "(" << arr_i[i] << ") ";
                }
                cout << endl;*/
        while (last_index > 1 && arr_val[2] > 0) {
            int rozmowca1_val = arr_val[1];             //// wybierz 1 rozmówcę
            int rozmowca1_i = arr_i[1];
            arr_val[1] = arr_val[last_index];           // wstaw ostatni element na pierwszy
            arr_i[1] = arr_i[last_index];
            last_index--;
            downheap(arr_val, arr_i, last_index);       // przywróć kopiec
            int rozmowca2_val = arr_val[1];             //// wybierz 2 rozmówcę
            int rozmowca2_i = arr_i[1];
            // if last_index == 1 ?
            arr_i[1] = arr_i[last_index];               // wstaw ostatni element na pierwszy
            arr_val[1] = arr_val[last_index];
            last_index--;
            downheap(arr_val, arr_i, last_index);      // przywróć kopiec

            rozmowca1_val--;
            rozmowca2_val--;
            counter++;

            if (rozmowca1_val > 0) {
                last_index++;
                arr_val[last_index] = rozmowca1_val;
                arr_i[last_index] = rozmowca1_i;
                upheap(arr_val, arr_i, last_index);
            }

            if (rozmowca2_val > 0) {
                last_index++;
                arr_val[last_index] = rozmowca2_val;
                arr_i[last_index] = rozmowca2_i;
                upheap(arr_val, arr_i, last_index);
            }
            if (rozmowca1_i <= rozmowca2_i) {
                result.push_back(rozmowca1_i);
                result.push_back(rozmowca2_i);
            }
            else {
                result.push_back(rozmowca2_i);
                result.push_back(rozmowca1_i);
            }
        }
        cout << counter << "\n";
        for (int i = 0; i < counter; i++) {
            cout << result[i * 2] << " " << result[i * 2 + 1] << "\n";
        }
        counter = 0;
        result.clear();
        delete[] arr_val;
    }
    return 0;
}

void upheap(int* arr_val, int* arr_i, int last_index) {
    int j = last_index;
    while (j > 1) {

        if (arr_val[j] > arr_val[j / 2] ||
            (arr_val[j] == arr_val[j / 2] && arr_i[j] < arr_i[j / 2]))
        {
            swap(arr_i[j], arr_i[j / 2]);
            swap(arr_val[j], arr_val[j / 2]);
            j = j / 2;
        }
        else break;
    }
}

void downheap(int* arr_val, int* arr_i, int last_index) {                  //last_index rozmiar tablicy k pozycja elementu od którego zaczynamy
    int k = 1;
    int j = 2;
    while (j <= last_index) {                                //rodzic to k a jego synowie znajdują się na j i j+1

        if (j + 1 <= last_index &&
            (arr_val[j] < arr_val[j + 1] ||
             (arr_val[j] == arr_val[j + 1] && arr_i[j] > arr_i[j + 1])))
            j++;


        if (arr_val[k] < arr_val[j] ||
            (arr_val[k] == arr_val[j] && arr_i[k] > arr_i[j]))
        {
            swap(arr_val[k], arr_val[j]);
            swap(arr_i[k], arr_i[j]);
            k = j;
            j = k * 2;
        }
        else break;
    }
}

int read_array(int* arr_val, int* arr_i, int n) {
    int counter = 0;
    for (int i = 1; i < n + 1; i++) {
        arr_i[i - counter] = i;
        cin >> arr_val[i - counter];
        if (arr_val[i - counter] > 0)
            upheap(arr_val, arr_i, i - counter);
        else
            counter++;
    }
    return counter;
}
