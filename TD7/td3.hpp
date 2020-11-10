#ifndef TD3_HPP
#define TD3_HPP

#include <chrono>
#include <functional>
#include <random>
#include <vector>

class Base {
private:
  /* data */
public:
  virtual ~Base() = default;
  virtual bool isGreater(Base const &other) const = 0;
  virtual void print() const = 0;
};

class Entier : public Base {
private:
  int _val;

public:
  Entier() : _val(0) {}
  Entier(int v) : Base(), _val(v) {}
  operator int() { return _val; }

  bool isGreater(Base const &other) const {
    if (Entier const *entier = dynamic_cast<Entier const *>(&other)) {
      return _val > entier->_val;
    }
    return false;
  }
  void print() const { std::cout << "Entier:" << _val; }
};

template <typename T> class Number : public Base {
private:
  T _val;

public:
  Number() : _val(0) {}
  Number(T v) : Base(), _val(v) {}
  operator int() { return _val; }

  bool isGreater(Base const &other) const {
    if (Number const *num = dynamic_cast<Number const *>(&other)) {
      return _val > num->_val;
    }
    return false;
  }
  void print() const { std::cout << "Number:" << _val; }
};

void insertion_sort(std::vector<Base *> &anArray) {
  for (std::size_t i = 0u; i < anArray.size(); i++) {
    for (std::size_t j = i + 1u; j < anArray.size(); j++) {
      if (anArray[i]->isGreater(*anArray[j]))
        std::swap(anArray[i], anArray[j]);
    }
  }
}

void print(std::vector<Base *> &anArray) {
  std::cout << "{\n";
  for (auto el : anArray) {
    el->print();
    std::cout << ",\n";
  }
  std::cout << "}\n";
}

std::vector<Base *> CreateRandomNumbers(size_t theNumberOfValues,
                                        int theMinValue, int theMaxValue) {
  auto time_seed = static_cast<long unsigned>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count());
  static auto type_rand = std::bind(std::uniform_int_distribution<int>{0, 1},
                                    std::default_random_engine{time_seed});
  std::vector<Base *> array(theNumberOfValues);
  for (size_t i = 0; i < theNumberOfValues; i++) {
    auto type = type_rand();
    switch (type) {
    case 1: {
      // Whatever
      static auto real_rand = std::bind(
          std::uniform_real_distribution<double>{
              static_cast<double>(theMinValue),
              static_cast<double>(theMaxValue)},
          std::default_random_engine{time_seed});
      array[i] = new Number<double>(real_rand());
      break;
    }
    default: {
      // Entier
      static auto int_rand = std::bind(
          std::uniform_int_distribution<int>{theMinValue, theMaxValue},
          std::default_random_engine{time_seed});
      array[i] = new Entier(int_rand());
      break;
    }
    }
  }
  return array;
}

#endif // !TD3_HPP