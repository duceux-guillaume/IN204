#include <iostream>

double divide(double a, double b);
void test_divide();

void test_divide()
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

double divide(double a, double b)
{
    try {
        if (!b) throw b;
    }
    catch (double b) {
        std::cout << "Ne peut pas diviser par zero.\n";
        return b;
    }
    return a / b;
}


int main()
{
    test_divide();
    return 0;
}