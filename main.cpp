#include "graph.hpp"
#include "math.hpp"
#include <iostream>

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

template <typename T, typename YourComparaison = Comparaison<T>>
void Triage(std::vector<T> &input, YourComparaison comp = YourComparaison()) {
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

int main(int argc, char **argv) {
  {
    auto test = std::vector<int>{5, 3, 6, 4};
    AfficheVector(test);
    Triage(test);
    AfficheVector(test);
  }
  {
    auto test = std::vector<double>{5.0, 3.0, 6.0, 4.0};
    AfficheVector(test);
    Triage(test);
    AfficheVector(test);
  }
  {
    auto test = std::vector<Chaussette>{Chaussette(5.0), Chaussette(3.0),
                                        Chaussette(6.0), Chaussette(4.0)};
    AfficheVector(test);
    Triage<Chaussette, MaComparaison>(test);
    AfficheVector(test);
  }
  {
    auto test = std::vector<Chaussette>{Chaussette(5.0), Chaussette(3.0),
                                        Chaussette(6.0), Chaussette(4.0)};
    AfficheVector(test);
    Triage(test);
    AfficheVector(test);
  }
  return EXIT_SUCCESS;
}