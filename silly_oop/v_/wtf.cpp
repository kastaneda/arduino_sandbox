#include <stdio.h>

// char *arr[] = { "foo", "bar", "baz" };

struct MyStruct {
  const char *msg;
  void (*func)();
};

struct MyStruct arr[] = {
  {
    "Hello world",
    []() { printf("hehehe\n"); }
  },
  {
    "Goodbye world",
    []() { printf("hohoho\n"); }
  }
};

int main() {
  int count;
  count = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < count; i++)  {
    printf("%s\n", arr[i].msg);
  }
  for (int i = 0; i < count; i++)  {
    arr[i].func();
  }
  return 0;
}
