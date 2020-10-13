
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using MyPair = std::pair<std::string, std::size_t>;

struct MySort {
  bool operator()(MyPair const &l, MyPair const &r) const {
    return l.second < r.second;
  }
};

void print_usage() {
  std::cout << "usage: ./count.exe nom_de_fichier" << std::endl;
}

int main(int argc, char **argv) {
  if (argc <= 1) {
    print_usage();
    return -1;
  }

  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open()) {
    std::cerr << "couldn't open: " << argv[1] << std::endl;
    return -1;
  }

  std::string word;
  std::map<std::string, std::size_t> word_count;
  while (file >> word) {
    word_count[word]++;
  }

  std::vector<std::pair<std::string, std::size_t>> output;
  for (auto var : word_count) {
    output.push_back(var);
  }
  std::sort(output.begin(), output.end(), MySort());

  for (auto var : output) {
    std::cout << var.first << " " << var.second << std::endl;
  }

  return 0;
}