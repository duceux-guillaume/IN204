#include <iostream>
#include "module.hpp"
#include "interval.hpp"
#include "economic.hpp"

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
    Interval i22(2., 1.);

    std::cout << i1 + i2 << " = " << i1 << " + " << i2 << " " << i22 << std::endl;

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

    int valeur = 5;
    int* ptr = &valeur;

    std::cout << ptr << " " << &valeur << " " << valeur << std::endl;

    
    PersonnePhysique moi(0, "Guillaume");
    std::cout << moi << std::endl;
    
    Entreprise monEntreprise(100, "Gogle", "SAS", moi);
    monEntreprise.GagnerDeLaThune(10);
    

    std::cout <<  static_cast<AgentEconomic>(monEntreprise) << " solde: " << monEntreprise.Solde() << std::endl;

    monEntreprise.Recruter(moi);

    {
        std::cout << "scope tmp" << std::endl;
        Entreprise tmp(100, "Gogle", "SAS", moi);
        std::cout << "scope end" << std::endl;
    }
        std::cout << "scope after" << std::endl;

    return EXIT_SUCCESS;
}