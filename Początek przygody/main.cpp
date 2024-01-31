#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    int a;
    std::cin >> a;
    if(a == 0)
        std::cout << "Helo Wold\n";
    else if (a == 1) {
        std::cout << "Czesc Swece\n";
    }
}
