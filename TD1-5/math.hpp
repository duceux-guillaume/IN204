#ifndef MATH_HPP
#define MATH_HPP

#include <iostream>
#include <limits>
#include <algorithm>

template <typename T> T identity(T x) { 
    std::cout << "generique" << std::endl;
    return x; 
}
template <> bool identity<bool>(bool x) { 
    std::cout << "bool" << std::endl;
    return x; 
}


template <typename T> int constant(T x) { return 0; }

template <typename T, typename G> T addition(T x, G y) {
  std::cout << "Addition generique" << std::endl;
  return x + y;
}

template <typename T> class IntervalGen {
private:
  T _min;
  T _max;

public:
  IntervalGen();
  IntervalGen(T a, T b) : _min(a), _max(b) {
    if (_min > _max) {
      std::swap(_min, _max);
    }
  }

  static IntervalGen<T> IntervalRightOpen(T a) {
      return IntervalGen<T>(a, std::numeric_limits<T>::max());
  }

  IntervalGen<T> operator+=(IntervalGen<T> const &autre) const;
  IntervalGen<T> operator-=(IntervalGen<T> const &autre) const;

  void print() const;

  T min() const { return _min; }

  T max() const { return _max; }
};

template <typename T>
IntervalGen<T> IntervalGen<T>::operator+=(IntervalGen<T> const &autre) const {
  return IntervalGen<T>(_min + autre._min, _max + autre._max);
}

template <typename T>
IntervalGen<T> IntervalGen<T>::operator-=(IntervalGen<T> const &autre) const {
  return IntervalGen<T>(_min - autre._min, _max - autre._max);
}

template <typename T, typename G>
IntervalGen<T> operator+(IntervalGen<T> const &l, IntervalGen<G> const &r) {
  return l += IntervalGen<T>(r.min(), r.max());
}

template <typename T, typename G>
IntervalGen<T> operator-(IntervalGen<T> const &l, IntervalGen<G> const &r) {
  return l -= IntervalGen<T>(r.min(), r.max());
}

template <typename T>
std::ostream &operator<<(std::ostream &out, IntervalGen<T> const &r) {
  out << "[" << r.min() << ", " << r.max() << "]";
  return out;
}

using Intervali = IntervalGen<int>;
using Intervald = IntervalGen<double>;

#endif //  MATH_HPP
