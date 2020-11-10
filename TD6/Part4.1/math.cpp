#include"math.hpp"
#include<iostream>


class finally
{
public:
    finally() {}
    ~finally() { std::cout << "Fonction terminée" << std::endl; }
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


