#include <iostream>
#include "MyClass.h"

int main() {
  MyClass c;
  int result;

  result = c.foo();
  std::cout << "Test result: "  << result << std::endl;

  return 0;
}
