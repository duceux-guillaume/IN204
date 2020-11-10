#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <iostream>

class BaseCounter {
protected:
  unsigned counter;
  unsigned max;

public:
  virtual std::string getClassName() const {
    return std::string("BaseCounter");
  }
  unsigned getCounter() const { return counter; }
  unsigned getMax() const { return max; }
  void reset() { counter = 0; }
  void set(unsigned value) { counter = value; }
  void setMax(unsigned value) {
    max = value;
    if (value > counter)
      counter = counter % max;
  }

  virtual void next() = 0;
  virtual void next(unsigned nb) = 0;
  virtual BaseCounter &operator++() {
    next();
    return *this;
  }
  virtual BaseCounter &operator++(int) {
    next();
    return *this;
  }
  virtual void onMaxReached() { counter = 0; }

protected:
  BaseCounter() : counter(0), max(0) {}
  BaseCounter(unsigned theCounter, unsigned theMax)
      : counter(theCounter), max(theMax) {}
  explicit BaseCounter(unsigned theMax) : counter(0), max(theMax) {}
  BaseCounter(const BaseCounter &anotherCounter)
      : counter(anotherCounter.counter), max(anotherCounter.max) {}
  ~BaseCounter() {}
};

static std::ostream &operator<<(std::ostream &out, BaseCounter const &base) {
  out << base.getClassName() << ":" << base.getCounter() << "/"
      << base.getMax();
  return out;
}

class ForwardCounter : public virtual BaseCounter {
public:
  std::string getClassName() const override {
    return std::string("ForwardCounter");
  }
  void increment() {
    if (counter < max)
      counter = counter + 1;
    else
      onMaxReached();
  }

  ForwardCounter() : BaseCounter() {}
  ForwardCounter(const ForwardCounter &aCounter) : BaseCounter(aCounter) {}
  explicit ForwardCounter(unsigned theMaxValue)
      : ForwardCounter(0, theMaxValue) {}
  ForwardCounter(unsigned theCounter, unsigned theMaxValue)
      : BaseCounter(theCounter, theMaxValue) {}

  void next() override { increment(); }
  void next(unsigned nb) override {
    for (unsigned i = 0; i < nb; ++i) {
      increment();
    }
  }
};

class BackwardCounter : public virtual BaseCounter {
public:
  std::string getClassName() const override {
    return std::string("BackwardCounter");
  }
  void decrement() {
    if (counter > 0)
      counter = counter - 1;
    else
      counter = max;
  }
  BackwardCounter() : BaseCounter() {}
  BackwardCounter(const ForwardCounter &aCounter) : BaseCounter(aCounter) {}
  explicit BackwardCounter(unsigned theMaxValue)
      : BackwardCounter(0, theMaxValue) {}
  BackwardCounter(unsigned theCounter, unsigned theMaxValue)
      : BaseCounter(theCounter, theMaxValue) {}

  void next() override { decrement(); }
  void next(unsigned nb) override {
    for (unsigned i = 0; i < nb; ++i) {
      decrement();
    }
  }
};

class BiDiCounter : public ForwardCounter, public BackwardCounter {
public:
  std::string getClassName() const override {
    return std::string("BiDiCounter");
  }
  BiDiCounter() : ForwardCounter(), BackwardCounter() {}
  BiDiCounter(const BiDiCounter &aCounter)
      : BaseCounter(aCounter), ForwardCounter(aCounter),
        BackwardCounter((const BackwardCounter &)aCounter) {}
  BiDiCounter(unsigned theMaxValue) : BiDiCounter(0, theMaxValue) {}
  BiDiCounter(unsigned theCounter, unsigned theMaxValue)
      : BaseCounter(theCounter, theMaxValue),
        ForwardCounter(theCounter, theMaxValue),
        BackwardCounter(theCounter, theMaxValue) {}

  void next() override { ForwardCounter::next(); }
  void next(unsigned nb) override { ForwardCounter::next(nb); }
};

class VerboseForwardCounter : public ForwardCounter {
public:
  VerboseForwardCounter() : VerboseForwardCounter(0, 0) {}
  explicit VerboseForwardCounter(unsigned theMaxValue)
      : VerboseForwardCounter(0, theMaxValue) {}
  VerboseForwardCounter(unsigned theCounter, unsigned theMaxValue)
      : BaseCounter(theCounter, theMaxValue) {}

  void onMaxReached() override {
    std::cout << "max reached" << std::endl;
    ForwardCounter::onMaxReached();
  }

  std::string getClassName() const override {
    return std::string("VerboseForwardCounter");
  }
};

void TestCount(BaseCounter &counter) {
  std::cout << counter << std::endl;
  std::cout << ++counter << std::endl;
  counter.next(2);
  std::cout << counter << std::endl;
}

#endif // COUNTER_HPP