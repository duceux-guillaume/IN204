#include"math.hpp"
#include<iostream>


class finally
{
public:
    finally() {}
    ~finally() { std::cout << "Fonction termin�e" << std::endl; }
};
 
double divide(double theNumerator, double theDivisor) noexcept(false)
{
    finally finally();
    double result;
    if (theDivisor == 0)
        throw division_by_zero();
    result = theNumerator / theDivisor;
    return result;
}


