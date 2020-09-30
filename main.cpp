#include "graph.hpp"
#include "math.hpp"
#include <iostream>
#include <list>
#include <set>

struct MyNode {
  int key;
  std::string payload;

  MyNode(int k, std::string const &p) : key(k), payload(p) {}
};

template <> struct Equal<MyNode> {
  bool operator()(const MyNode &k1, const MyNode &k2) const {
    return k1.key == k2.key;
  }
};

std::ostream &operator<<(std::ostream &out, MyNode const &node) {
  out << node.key << " " << node.payload;
  return out;
}

template <typename T> struct Comparaison {
  bool operator()(T const &l, T const &r) const { return l < r; }
};

template <typename T, typename G = Comparaison<T>>
void Triage(std::vector<T> &input, G comp = G()) {
  for (int i = 0; i < input.size() - 1; ++i) {
    for (int j = i + 1; j < input.size(); ++j) {
      if (comp(input[i], input[j])) {
        std::swap(input[i], input[j]);
      }
    }
  }
}

void TriageDouble(std::vector<double> &input) {
  for (int i = 0; i < input.size() - 1; ++i) {
    for (int j = i + 1; j < input.size(); ++j) {
      if (input[i] < input[j]) {
        std::swap(input[i], input[j]);
      }
    }
  }
}

template <typename T> void AfficheVector(std::vector<T> const &v) {
  std::cout << "DEBUT" << std::endl;
  for (auto const &var : v) {
    std::cout << var << std::endl;
  }
  std::cout << "FIN" << std::endl;
}

void AfficheVectorDouble(std::vector<double> const &v) {
  std::cout << "DEBUT" << std::endl;
  for (auto const &var : v) {
    std::cout << var << std::endl;
  }
  std::cout << "FIN" << std::endl;
}

struct Chaussette {
  int taille;

  Chaussette(int t) : taille(t) {}
};

std::ostream &operator<<(std::ostream &out, Chaussette const &r) {
  out << r.taille;
  return out;
}

template <> struct Comparaison<Chaussette> {
  bool operator()(Chaussette const &l, Chaussette const &r) const {
    return l.taille < r.taille;
  }
};

struct MaComparaison {
  bool operator()(Chaussette const &l, Chaussette const &r) const {
    return l.taille < r.taille;
  }
  // blabla
};

template <typename T, typename IteratorOrPointer, typename ConditionOperator>
IteratorOrPointer
FirstElementWithCondition(IteratorOrPointer begin, IteratorOrPointer end,
                          ConditionOperator condition = ConditionOperator()) {
  if (begin == end) {
    return end;
  }

  for (auto iterator = begin; iterator != end; ++iterator) {
    if (condition(*iterator)) {
      return iterator;
    }
  }
  return end;
}

template <typename T, typename IteratorOrPointer>
IteratorOrPointer FirstElementGreaterThan(IteratorOrPointer begin,
                                          IteratorOrPointer end,
                                          T const &condition) {
  auto lambda_condition = [condition](T const &val) {
    if (val > condition) {
      return true;
    }
    return false;
  };
  return FirstElementWithCondition<T, IteratorOrPointer>(begin, end,
                                                         lambda_condition);
}

template <typename T, typename It>
It FirstElementPositiv(It begin, It end, T &result) {
  It res = FirstElementGreaterThan(begin, end, T(0));
  result = *res;
  return res;
}

struct MonIteratorDeMonConteneur {
  int _val;
  int _max;
  MonIteratorDeMonConteneur(int v, int m) : _val(v), _max(m) { Next(); }

  int operator*() { return _val; }

  bool operator==(MonIteratorDeMonConteneur const &other) {
    if (_val >= _max && other._val >= other._max)
      return true;
    return _val == other._val;
  }

  bool operator!=(MonIteratorDeMonConteneur const &other) {
    return !(*this == other);
  }

  MonIteratorDeMonConteneur &operator++() {
    Next();
    return *this;
  }
  MonIteratorDeMonConteneur operator++(int) {
    MonIteratorDeMonConteneur tmp(*this); // copy
    ++(*this);                            // pre-increment
    return tmp;                           // return old value
  }

  bool IsPrime() const {
    if (_val <= 1) {
      return false;
    }
    if (_val == 2) {
      return true;
    }
    for (int diviseur = 2; diviseur < _val - 1; ++diviseur) {
      if (_val % diviseur == 0) {
        return false;
      }
    }
    return true;
  }

  void Next() {
    if (_val >= _max) {
      return;
    }
    do {
      ++_val;
    } while (!IsPrime());
  }
};

struct MonConteneurDeNombrePremier {
  int _borne_inferieur;
  int _borne_superieur;

  MonConteneurDeNombrePremier(int inf, int sup)
      : _borne_inferieur(inf), _borne_superieur(sup) {}

  MonIteratorDeMonConteneur begin() const {
    return MonIteratorDeMonConteneur(_borne_inferieur, _borne_superieur);
  }

  MonIteratorDeMonConteneur end() const {
    return MonIteratorDeMonConteneur(_borne_superieur, _borne_superieur);
  }
};

int main(int argc, char **argv) {
  { // INTS VECT
    std::vector<int> list{-5, 5, 8, 100, 10, 25, 35};
    int result;
    auto argmax = FirstElementPositiv<int>(list.begin(), list.end(), result);
    std::cout << *argmax << std::endl;
  }

  { // DOUBLE LIST
    std::vector<double> list{-5.0, 0., 8., 100., 10., 25., 35.};
    double result;
    auto argmax = FirstElementPositiv<double>(list.begin(), list.end(), result);
    std::cout << *argmax << std::endl;
  }

  { // DOUBLE LIST
    std::list<double> conteneur{-5.0, 0., 8., 100., 10., 25., 35.};
    double result;
    auto argmax =
        FirstElementPositiv<double>(conteneur.begin(), conteneur.end(), result);
    std::cout << *argmax << std::endl;
  }

  { // DOUBLE SET
    std::set<double> conteneur{-5.0, 0., 8., 100., 10., 25., 35.};
    double result;
    auto argmax =
        FirstElementPositiv<double>(conteneur.begin(), conteneur.end(), result);
    std::cout << *argmax << std::endl;
  }

  { // DOUBLE TAB
    double conteneur[] = {-5.0, 0., 8., 100., 10., 25., 35.};
    double result;
    auto argmax =
        FirstElementPositiv<double>(&conteneur[0], &conteneur[6], result);
    std::cout << *argmax << std::endl;
  }

  { // DOUBLE TAB
    double conteneur[] = {-5.0, 0., 8., 100., 10., 25., 35.};
    double result;
    auto argmax =
        FirstElementGreaterThan<double>(&conteneur[0], &conteneur[6], 10.);
    std::cout << *argmax << std::endl;
  }

  { // INT MonConteneurDeNombrePremier
    MonConteneurDeNombrePremier conteneur(0, 100);
    std::cout << "nb premier" << std::endl;
    for (auto p : conteneur) {
      std::cout << p << std::endl;
    }
    std::cout << "fin" << std::endl;
    auto argmax =
        FirstElementGreaterThan<int>(conteneur.begin(), conteneur.end(), 10);
    std::cout << *argmax << std::endl;
  }

  return EXIT_SUCCESS;
}