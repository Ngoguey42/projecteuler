
#include <iostream>
#include <tuple>
#include <cmath>
#include <cassert>

int profiler_e = 0;

int integer_ceil_sqrt(int i) {
  return static_cast<int>(ceil(sqrt(static_cast<double>(i))));
}

int palindrome_of_lhs(int lhs) {
  int pal;

  pal = lhs;
  while (lhs > 0) {
    pal *= 10;
    pal += lhs % 10;
    lhs /= 10;
  }
  return pal;
}

std::pair<bool, int> divider(int pal) {
  int d;

  d = integer_ceil_sqrt(pal);
  while (d < 1000 && pal / d > 99) {
    profiler_e++;
    if (pal % d == 0)
      return {true, d};
    d++;
  }
  return {false, 0};
}

int soon() {
  int pal;
  bool success;
  int d;

  for (int lhs = 999; lhs > 99; lhs--) {
    pal = palindrome_of_lhs(lhs);
    std::tie(success, d) = divider(pal);
    if (success) {
      std::cout << d
                << " "
                << pal / d << std::endl;
      return pal;
    }
  }
  assert(false);
  return 0;
}

int main() {

  std::cout << soon() << std::endl;
  std::cout << "profiler_e: " << profiler_e << std::endl;

  return 0;
}
