#ifndef mathHPP
#define mathHPP

#include<exception>
#include<stdexcept>

class division_by_zero : public std::runtime_error
{
public:
    division_by_zero() : std::runtime_error("Division by zero")
    {}
};

double divide(double a, double b);

#endif
