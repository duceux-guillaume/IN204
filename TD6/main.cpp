
#include <algorithm>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

struct Pixel {
  uint8_t r, g, b;
};

class ImageIterator {
private:
  Pixel *_pos;

public:
  ImageIterator(Pixel *p) : _pos(p) {}

  bool operator!=(ImageIterator const &o) const {
    return _pos && (_pos != o._pos);
  }

  ImageIterator &operator++() {
    if (_pos) {
      _pos++;
    }
    return *this;
  }
  ImageIterator operator++(int) {
    ImageIterator tmp(*this); // copy
    ++(*this);                // pre-increment
    return tmp;               // return old value
  }

  Pixel *operator*() { return _pos; }
  Pixel const *operator*() const { return _pos; }
};

class Image {
public:
  typedef ImageIterator iterator_t;
  typedef const ImageIterator const_iterator_t;

private:
  Pixel *_data_ptr;
  std::size_t _rows;
  std::size_t _cols;

public:
  Image() : _data_ptr(NULL), _rows(0), _cols(0) {}

  ~Image() {
    if (_data_ptr) {
      delete[] _data_ptr;
    }
  }

  std::size_t Size() const noexcept { return _rows * _cols; }

  static Image Load(std::string const &filename);

  iterator_t begin() { return iterator_t(_data_ptr); }
  const_iterator_t begin() const { return iterator_t(_data_ptr); }
  iterator_t end() { return iterator_t(_data_ptr + Size()); }
  const_iterator_t end() const { return iterator_t(_data_ptr + Size()); }
};

Image Image::Load(std::string const &filename) {
  assert(filename.size() != 0);

  if (filename.empty()) {
    throw std::invalid_argument("empty filename");
  }
  std::ifstream file;
  file.open(filename, std::ios::binary);
  if (!file.is_open()) {
    throw std::invalid_argument("file not found: " + filename);
  }
  // TODO: read file
  Image result;
  result._data_ptr = new Pixel[100 * 100];
  result._rows = 100;
  result._cols = 100;
  return result;
}

std::string print_usage() { return std::string("img_prog filename"); }

int main(int argc, char **argv) {
  if (argc <= 1) {
    std::cerr << print_usage() << std::endl;
    // return -1;
  }

  Image img;
  try {
    img = Image::Load(argv[1]);
  } catch (std::exception const &ex) {
    std::cerr << ex.what() << std::endl;
    return -1;
  }

  try {
    std::cout << "Size: " << img.Size() << std::endl;
  } catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }
  /*
    for (auto pix : img) {
      if (pix) {
        std::cout << "rgb: " << pix->r << " " << pix->g << " " << pix->b
                  << std::endl;
        pix->r = 100;
        pix->g = 100;
        pix->b = 100;
      }
    }
  */

  return 0;
}