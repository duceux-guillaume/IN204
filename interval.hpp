#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <iostream>

class Interval {  
private:  
    double _min;
    double _max;

public:
    Interval();
    
    Interval(double a, double b);

    Interval(double a);

    Interval(Interval const& autre);

    ~Interval();

    Interval plus(Interval const& autre) const;

    void print() const;

    double min() const {
        return _min;
    }

    double max() const {
        return _max;
    }
};

void print(Interval const& i);

Interval operator+(Interval const& l, Interval r);

std::ostream& operator<<(std::ostream& out, Interval const& r);

struct Image {
    char* _data;

    Image() {
        _data = new char[1000];
    }

    ~Image() {
        if (_data) {
            delete _data;
        }
    }
};

#endif // !INTERVAL_HPP


