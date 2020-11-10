#include "math.hpp"
#include<iostream>

double divide(double theNumerator, double theDivisor) noexcept(false)
{
    if(theDivisor == 0)
        throw division_by_zero();
    return theNumerator / theDivisor;
}
