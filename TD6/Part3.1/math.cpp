#include"math.hpp"
#include<iostream>

double divide(double theNumerator, double theDivisor) noexcept(false)
{
	if (theDivisor == 0)
		throw division_by_zero();
	return theNumerator / theDivisor;
}

double successive_division(double i) noexcept(false)
{
	double j;
	std::cout << "Next divisor (-1 to stop sequence): ";
	std::cin >> j;
	if (j == -1)
		return i;
	try {
		successive_division(j);
		return divide(i, j);
	}
	catch (division_by_zero e)
	{
		throw extended_exception("Division by zero");
	}
	catch (extended_exception e)
	{
		e.catched();
		throw e;
	}
}


void test_succesive_division() noexcept
{
	double i;
	std::cout << "The numerator: ";
	std::cin >> i;
	try {
		successive_division(i);
	}
	catch (extended_exception e) {
		e.catched();
		std::cout << e.what() << " occurred after "
			<< e.getCatchNumber()
			<< " divisions" << std::endl;
	}
}


