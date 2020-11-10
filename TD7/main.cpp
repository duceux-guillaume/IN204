
#include "Counter.hpp"
#include "Drawing.hpp"
#include "td3.hpp"
#include <cassert>
#include <iostream>
#include <vector>

// Slide 1
class BaseClass {
public:
  BaseClass() { std::cout << "Construct BaseClass" << std::endl; }
  void printClassName() const { std::cout << "BaseClass" << std::endl; }
  ~BaseClass() { std::cout << "Delete BaseClass" << std::endl; }
};

class DerivedClass : public BaseClass {
public:
  DerivedClass() { std::cout << "Construct DerivedClass" << std::endl; }
  ~DerivedClass() { std::cout << "Delete DerivedClass" << std::endl; }
  void printClassName() const { std::cout << " DerivedClass" << std::endl; }
};

// Slide 2
void PrintClassName(BaseClass const &anObject) {
  std::cout << "Nom de la classe: ";
  anObject.printClassName();
}

// Slide 3
class VirtualBaseClass {
public:
  virtual void printClassName() const {
    std::cout << "VirtualBaseClass" << std::endl;
  }
  VirtualBaseClass() { std::cout << "Construct VirtualBaseClass" << std::endl; }
  virtual ~VirtualBaseClass() {
    std::cout << "Delete VirtualBaseClass" << std::endl;
  }
};

class VirtualDerivedClass : public VirtualBaseClass {
public:
  void printClassName() const override {
    std::cout << " VirtualDerivedClass" << std::endl;
  }
  VirtualDerivedClass() {
    std::cout << "Construct VirtualDerivedClass" << std::endl;
  }
  ~VirtualDerivedClass() {
    std::cout << "Delete VirtualDerivedClass" << std::endl;
  }
};

void PrintVirtualClassName(VirtualBaseClass const &anObject) {
  std::cout << "Nom de la classe: ";
  anObject.printClassName();
}

// Real Life exemple: All the design patterns

// Pure virtual class are called interfaces
class ICallback {
public:
  virtual ~ICallback() {}
  virtual void onSuccess(/*some result type*/) = 0;
  virtual void onError(/*some result type*/) = 0;
};

// Callback design used a lot for async application like over network or between
// threads and processes
void BigAsyncFunction(ICallback *caller) {
  /* do stuff */
  caller->onSuccess(/*result*/);
}

class SomeManager {
private:
  // Collection of base class for handling subscribers, workers or services
  std::vector<ICallback *> _listeners;
  // std::vector<IStuffOrBaseStuff *> _workers;

public:
};

int main(int /*argc*/, char ** /*argv*/) {

  {
    // Slide 1
    std::cout << "Ex 1" << std::endl;
    std::cout << "-----" << std::endl;
    {
      BaseClass base;
      std::cout << "BaseClass dit: " << std::endl;
      base.printClassName();
    }
    std::cout << "-----" << std::endl;
    {
      DerivedClass *derived = new DerivedClass();
      std::cout << "DerivedClass dit: " << std::endl;
      derived->printClassName();
      delete derived;
    }
    std::cout << "-----" << std::endl;
    {
      // Should not do that is not polymorphic, leaks some memory
      BaseClass *inrealderived = new DerivedClass();
      std::cout << "BaseClass pointer storing DerivedClass dit: " << std::endl;
      inrealderived->printClassName();
      delete inrealderived;
    }
    std::cout << "-----" << std::endl;

    // Not ok, source is not polymorphic
    // DerivedClass *tmp = dynamic_cast<DerivedClass *>(inrealderived);
    // std::cout << "DerivedClass pointer: " << std::endl;
    // tmp->printClassName();
    {
      // This cast work but it is a bad design, stuffs are leaked
      BaseClass *inrealderived = new DerivedClass();
      DerivedClass *tmp = static_cast<DerivedClass *>(inrealderived);
      std::cout << "DerivedClass pointer dit: " << std::endl;
      tmp->printClassName();
      delete inrealderived;
    }
    std::cout << "-----" << std::endl;
  }

  {
    // Slide 2
    std::cout << "Ex 2" << std::endl;
    std::cout << "Not polymorphic" << std::endl;
    PrintClassName(BaseClass());
    std::cout << "-----" << std::endl;
    PrintClassName(DerivedClass());
    std::cout << "-----" << std::endl;
  }

  {
    // Slide 3
    std::cout << "Ex 3" << std::endl;
    std::cout << "Polymorphic" << std::endl;
    PrintVirtualClassName(VirtualBaseClass());
    std::cout << "-----" << std::endl;
    PrintVirtualClassName(VirtualDerivedClass());
    std::cout << "-----" << std::endl;
    {
      VirtualBaseClass base;
      std::cout << "BaseClass dit: " << std::endl;
      base.printClassName();
    }
    std::cout << "-----" << std::endl;
    {
      VirtualDerivedClass derived;
      std::cout << "DerivedClass dit: " << std::endl;
      derived.printClassName();
    }
    std::cout << "-----" << std::endl;
    {
      // This is ok, that's the point of polymorphism
      VirtualBaseClass *inrealderived = new VirtualDerivedClass();
      std::cout << "BaseClass pointer storing DerivedClass dit: " << std::endl;
      inrealderived->printClassName();
      delete inrealderived;
    }
    std::cout << "-----" << std::endl;
    {
      // Ok now, source is  polymorphic
      VirtualBaseClass *inrealderived = new VirtualDerivedClass();
      VirtualDerivedClass *tmp =
          dynamic_cast<VirtualDerivedClass *>(inrealderived);
      std::cout << "DerivedClass pointer dit: " << std::endl;
      tmp->printClassName();
      delete inrealderived;
    }
    std::cout << "-----" << std::endl;
    {
      // This work but it is a bad design, dynamic_cast is meant for this
      VirtualBaseClass *inrealderived = new VirtualDerivedClass();
      VirtualDerivedClass *tmp2 =
          static_cast<VirtualDerivedClass *>(inrealderived);
      std::cout << "DerivedClass pointer dit: " << std::endl;
      tmp2->printClassName();
      delete inrealderived;
    }
    std::cout << "-----" << std::endl;
  }

  // Impossible
  // TestCount(BaseCounter())
  std::cout << "-----" << std::endl;
  ForwardCounter forward(10);
  TestCount(forward);
  std::cout << "-----" << std::endl;
  BackwardCounter backward(10, 0);
  TestCount(backward);
  std::cout << "-----" << std::endl;
  BiDiCounter bidi(0, 10);
  TestCount(bidi);
  std::cout << "-----" << std::endl;
  VerboseForwardCounter verbose(0, 1);
  TestCount(verbose);
  std::cout << "-----" << std::endl;

  auto graphicalObjects = createGraphicalObjects(10);
  drawGraphicalObjects(graphicalObjects);
  deleteGraphicalObjects(graphicalObjects);
  std::cout << "-----" << std::endl;

  std::vector<Base *> vector = CreateRandomNumbers(50, 0, 100);
  print(vector);
  insertion_sort(vector);
  print(vector);

  return 0;
}