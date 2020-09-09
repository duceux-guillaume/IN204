#include <iostream>
#include "module.hpp"
#include "interval.hpp"

int unevariable = 0;
const static int MAXIMUM = 1000;

void FaitQuelquechose() {
    unevariable++;
    int a;
}

int main(int argc, char** argv) {
    std::cout << "Hello IN204" << std::endl;

    FaitQuelquechose();

    InitModule();

    Interval i1;
    Interval i2(1., 2.);

    std::cout << i1 + i2 << " = " << i1 << " + " << i2 << std::endl;

    auto i3 = i1.plus(i2);
    auto i4 = i1 + i2;

    i1.print();
    print(i1);

    Interval* pt = nullptr;
    { 
        pt = new Interval();
    }

    { 
        Interval tt;
    }

    // 
    pt->print();

    std::cout << pt << std::endl;

    delete pt;

    std::cout << i1 + 4. << " = " << i1 << " + " << 4. << std::endl;
    std::cout << Interval(i1) << std::endl;


    return EXIT_SUCCESS;
}