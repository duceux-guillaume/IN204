#include "interval.hpp"
#include <iostream>

Interval Interval::plus(Interval const& autre) const {
    Interval resultat;
    resultat._min = this->_min + autre._min;
    resultat._max = this->_max + autre._max;
    return resultat;
}

Interval::Interval(Interval const& autre): _min(autre._min), _max(autre._max) {
    std::cout << "constructeur copie ref" << std::endl;
}


Interval::Interval(): _min(0), _max(0) {
    std::cout << "constructeur 1" << std::endl;
}

Interval::Interval(double a, double b): _min(a), _max(b) {
    std::cout << "constructeur 2" << std::endl;
}

Interval::Interval(double a): _min(a), _max(0) {
    std::cout << "constructeur 3" << std::endl;
}


void Interval::print() const {
    std::cout << "[" << _min << ", " << _max << "]" << std::endl; 
}

void print(Interval const& i) {
    i.print();
}

Interval operator+(Interval const& l, Interval r) {
    return l.plus(r);
}

std::ostream& operator<<(std::ostream& out, Interval const& r) {
    out << "[" << r.min() << ", " << r.max() << "]";
    return out;
}

Interval::~Interval() {
    std::cout << "destructeur " << *this << std::endl;
}