#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>

template <typename T>
struct Point {
  T x;
  T y;

  Point(T x, T y);
  Point();  // Not generated because another argument constructor exists
  explicit Point(T z);  // Conversion constructor
  // Point(Point const& p); // Copy constructor is generated

  bool operator==(Point<T> const& p) const;  // Left side of operator is Point
  bool operator!=(Point<T> const& p) const;

  bool operator==(std::pair<double, double> const& p) const {
    return x == p.first && y == p.second;
  }
  bool operator!=(std::pair<double, double> const& p) const {
    return !(*this == p);
  }

  template <typename G>
  bool operator==(Point<G> const& p) const;
};

template <typename G>
bool Point<G>::operator==(Point<G> const& p) const {
  return x == p.x && y == p.y;
}

template <typename T>
bool Point<T>::operator!=(Point<T> const& p) const {
  return !(p == *this);
}

template <typename T>
Point<T>::Point() : Point<T>(T(0), T(0)) {}

template <typename T>
Point<T>::Point(T z) : Point<T>(z, z) {
  std::cout << "conversion" << std::endl;
}

template <typename T>
Point<T>::Point(T a, T b) : x(a), y(b) {}

template <typename T>
bool operator==(std::pair<double, double> const& pair,
                Point<T> const& p);  // Declaration pair == point

// Definition pair == point
template <typename T>
bool operator==(std::pair<double, double> const& pair, Point<T> const& p) {
  return pair.first == p.x && pair.second == p.y;
}

template <typename T>
template <typename G>
bool Point<T>::operator==(Point<G> const& p) const {
  bool r1 = (x == (T)p.x && y == (T)p.y);
  bool r2 = ((G)x == p.x && (G)y == p.y);
  return r1 && r2;
}

template <class T, class charT, class traits = std::char_traits<charT>>
std::basic_ostream<charT, traits>& operator<<(
    std::basic_ostream<charT, traits>& stream, Point<T> const& p) {
  stream << "(" << p.x << ", " << p.y << ")";
  return stream;
}

// template <typename T>
// std::ostream& operator<<(std::ostream& stream, Point<T> const& p) {
//  stream << "(" << p.x << ", " << p.y << ")";
//  return stream;
//}

template <typename T>
std::istream& operator>>(std::istream& stream, Point<T>& p) {
  stream >> p.x >> p.y;
  return stream;
}

using Pointd = Point<double>;
typedef Point<int> Pointi;

template <typename T>
class IShape {
 public:
  virtual bool Contains(Point<T> const& p) const = 0;
  virtual T Area() const = 0;
  virtual ~IShape() {}
};

class BaseShape : public IShape<double> {
 public:
  bool Contains(Point<double> const& /*p*/) const { return false; }
  ~BaseShape() {}
};

class Circle : public BaseShape {
 private:
  Pointd _center;
  double _radius;

 public:
  Circle(Pointd center, double radius);

  bool Contains(Point<double> const&) const override {
    // return (_center - p).dot(_center - p) <= _radius;
    return false;
  }

  Pointd const& getCenter() const { return _center; }
  Pointd const& center() const { return _center; }

  void setCenter(Pointd const& p) { _center = p; }
  Pointd& center() { return _center; }

  void setRadius(double d) {
    _radius = d;
    if (_radius <= 0) {
      //_radius = -_radius;
      throw std::runtime_error("radius <= 0 is not possible ");
    }
  }

  double radius() { return _radius; }
};

class Polygon : public BaseShape {
 protected:
  std::vector<Pointd> _vertex;

 public:
};

class Square : public Polygon {
 private:
 public:
};

class GameObject {
 private:
  std::vector<BaseShape*> _shapes;

 public:
  ~GameObject();

  GameObject& Add(BaseShape* shape);

  bool DetectHit(Pointd const& bullet) const;
};

#endif  // !MAIN_HPP
