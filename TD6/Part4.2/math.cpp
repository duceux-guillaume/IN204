#include"math.hpp"
#include<iostream>

double divide(double theNumerator, double theDivisor) noexcept(false)
{
    double result;
    try
    {
        if (theDivisor == 0)
            throw division_by_zero();
        result = theNumerator / theDivisor;
    }
    catch (...)
    {
        std::cout << "Fonction termin�e" << std::endl;
        throw;
    }
    std::cout << "Fonction termin�e" << std::endl;
    return result;
}

