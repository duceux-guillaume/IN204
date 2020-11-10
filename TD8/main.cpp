#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>

#include "main.hpp"

GameObject::~GameObject() {
  for (BaseShape* s : _shapes) {
    if (s) delete s;
  }
}

Circle::Circle(Pointd center, double radius)
    : _center(center), _radius(radius) {
  if (_radius <= 0) {
    throw std::runtime_error("radius <= 0 is not possible ");
  }
}

GameObject& GameObject::Add(BaseShape* shape) {
  _shapes.push_back(shape);
  std::sort(_shapes.begin(), _shapes.end());
  return *this;
}

bool GameObject::DetectHit(Pointd const& bullet) const {
  for (BaseShape* s : _shapes) {
    if (s->Contains(bullet)) return true;
  }
  return false;
}

int main(int /*argc*/, char** /*argv*/) {
  Point<double> p(0, 0);

  Pointd c = p;
  Pointd d(p);

  Pointi z = static_cast<Pointi>(5);
  z = (Pointi)7;
  z = Pointi(6);

  p.x = 10;
  c.x = 7;
  std::cout << p << std::endl;
  std::cout << c.x << " " << c.y << std::endl;
  std::cout << d.x << " " << d.y << std::endl;
  std::cout << z.x << " " << z.y << std::endl;

  std::cout << " p == c? " << (p == c) << std::endl;
  std::cout << " p == p? " << (p == p) << std::endl;

  std::cout << " point == pair? "
            << (Pointd() == std::pair<double, double>(0., 1.)) << std::endl;
  std::cout << " pair == point? "
            << (std::pair<double, double>(0., 1.) == Pointd()) << std::endl;

  std::cout << sizeof(double) << std::endl;
  std::cout << sizeof(Pointd) << std::endl;
  std::cout << sizeof(Point<bool>) << std::endl;

  std::cout << " Pointi == Pointd? " << (Pointi(5, 6) == Pointd(5.3, 6.2))
            << std::endl;
  std::cout << " Pointd == Pointi? " << (Pointd(5.3, 6.2) == Pointd(5, 6))
            << std::endl;

  std::stringstream ss;
  ss << 5 << " " << 6;
  std::cout << ss.str() << std::endl;
  Pointi test;
  ss >> test;
  std::cout << test << std::endl;

  Circle circle(Pointd(), 1.);
  std::cout << circle.Contains(Pointd()) << std::endl;

  GameObject object1;
  object1.Add(new Circle(Pointd(), 1.)).Add(new Circle(Pointd(1., 0.), 1.));
  std::cout << object1.DetectHit(Pointd()) << std::endl;

  circle.setRadius(5.);
  try {
    circle.setRadius(0);
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << circle.getCenter() << " " << circle.radius() << std::endl;
  std::cout << circle.center() << " " << circle.radius() << std::endl;
  circle.center() = Pointd();

  //
  // GameObject object2;
  // object2.Add(new Square()).Add(new Triangle());

  std::vector<int> ints{6, 5};
  std::sort(ints.begin(), ints.end());

  std::vector<std::complex<int>> complex{std::complex<int>(5, 0),
                                         std::complex<int>(0, 1)};

  struct MaComparaison {
    bool operator()(std::complex<int> const& l,
                    std::complex<int> const& r) const {
      return l.real() < r.real();
    };
  };

  std::sort(complex.begin(), complex.end(), MaComparaison());

  auto lambda = [](std::complex<int> const& l,
                   std::complex<int> const& r) -> bool {
    return l.real() < r.real();
  };

  std::sort(complex.begin(), complex.end(), lambda);

  return 0;
}