#include <iostream>

class MyClass {
public:
  int foo();
};

int MyClass::foo() {
  return 123;
}

int main() {
  MyClass c;
  int result;

  result = c.foo();
  std::cout << "Test result: "  << result << std::endl;

  return 0;
}
