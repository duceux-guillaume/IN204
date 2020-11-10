#ifndef MATH_HPP
#define MATH_HPP

#include <cstdint>
#include <vector>

template <typename T> struct Point {
  T x, y;

  Point(T const &x, T const &y) : x(x), y(y) {}
};

using Pointf = Point<float>;
using Pointd = Point<double>;
using Pointi = Point<int>;

class AbstractShape {
public:
  /*
  template <typename T>
  virtual Contains(Point<T> const &p) = 0;
  */

  // Outisde of class
  virtual bool Contains(Point<int> const &p);

  // Inline, to avoid for complexe functions
  virtual bool Contains(Pointf const &p) {
    return Contains(Point<double>(p.x, p.y));
  }

  virtual bool Contains(Point<double> const &p) const = 0; // Pure virtual
};

bool AbstractShape::Contains(Point<int> const &p) {
  return Contains(Point<double>(p.x, p.y));
}

class Circle : public AbstractShape {
private:
  Pointd _center;
  double _radius;

public:
  bool Contains(Point<double> const &p) const override;
};

class BasePolygon : public AbstractShape {
protected:
  std::vector<Point<double>> _vertex;

public:
  virtual std::size_t NumberOfEdges() const { return _vertex.size() - 1; }
  virtual std::size_t NumberOfVertex() const { return _vertex.size(); }
};

class Triangle : public BasePolygon {};

class Square : public BasePolygon {};

class GameObjectHitBox {
private:
  std::vector<AbstractShape *> _hit_boxes;

public:
  void DetectHit(Pointd bullet);
};

#endif // !MATH_HPP