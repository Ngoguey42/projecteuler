

#include <iostream>

int main() {
  int acc = 0;

  for (int i = 0; i < 1000; i++)
    if (i % 3 == 0 || i % 5 == 0)
      acc += i;
  std::cout << acc << std::endl;
  return 0;
}
