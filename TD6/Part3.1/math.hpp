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

class extended_exception : public std::runtime_error
{
private:    
    unsigned m_catched = 0;

public:
    explicit extended_exception(const std::string& aMessage) :
        runtime_error(aMessage)
    {}
    explicit extended_exception(const char* aMessage) :
        runtime_error(aMessage)
    {}
    void catched() { m_catched++; }
    // Est appelé chaque fois que l’on souhaite indiqué à la classe qu’elle a été
    // capturée. 
    int getCatchNumber() const { return m_catched; }
    // Retourne le nombre de fois que l’exception a été capturée.
};

double divide(double a, double b);
double successive_division(double i) noexcept(false);
void test_succesive_division() noexcept;

#endif



