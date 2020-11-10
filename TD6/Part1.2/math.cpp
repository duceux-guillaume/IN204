#include "math.hpp"
#include<iostream>

double divide(double a, double b)
{
    try {
        if (b == 0)
            throw division_by_zero();
    }
    catch (division_by_zero) {
        std::cout << "Ne peut pas diviser par zero.\n";
        return 0;
    }
    return a / b;
}
