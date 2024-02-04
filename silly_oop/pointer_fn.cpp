#include <iostream>

void foo() {
  std::cout << "Foo" << std::endl;
}

void bar() {
  std::cout << "Bar" << std::endl;
}

int main() {
  void (*fn_ptr[])() = { foo, bar, foo, bar, foo, foo, foo, 0, bar, foo };
  for (uint8_t c=0; c<sizeof(fn_ptr)/sizeof(fn_ptr[0]); c++) {
    if (fn_ptr[c]) {
      fn_ptr[c]();
    } else {
      std::cout << "(null pointer)" << std::endl;
    }
  }
  return 0;
}
