#include"math.hpp"
#include<iostream>

void test_divide() noexcept
{
    double i, j;
    for (;;) {
        std::cout << "Le numerateur (0 pour arreter): ";
        std::cin >> i;
        if (i == 0)
            break;
        std::cout << " Le denominateur : ";
        std::cin >> j;
        std::cout << "Resultat: " << divide(i, j) << std::endl;
    }
}

int main()
{
    test_divide();
    return 0;
}