#include"math.hpp"
#include<iostream>
int main()
{
	try
	{
		divide(2, 3);
	}
	catch (...) { std::cout << "Exception raised" << std::endl; }
	try
	{
		divide(2, 0);
	}
	catch (...) { std::cout << "Exception raised" << std::endl; }
	return 0;
}