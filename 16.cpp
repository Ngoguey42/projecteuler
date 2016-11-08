

#include <cmath>
#include <array>
#include <vector>
#include <iostream>

#define BASE 2
#define EXPONENT 1000

constexpr int MAX_DIGITS =
  static_cast<int>(
  ceil(log10(static_cast<double>(BASE)) *
       static_cast<double>(EXPONENT)));

// try valarray ?
using number_t = std::vector<int>;
// using number_t = std::array<int, MAX_DIGITS>;

int profiler_a = 0;

static void multiply(number_t &number, int factor) {
  int carry;
  int tmp;

  carry = 0;
  for (int &digit: number) {
    profiler_a++;
    tmp = digit * factor + carry;
    digit = tmp % 10;
    carry = tmp / 10;
  }
  while (carry != 0) {
    number.push_back(carry % 10);
    carry /= 10;
    profiler_a++;
  }
}

void dump_number(number_t const &number) {
  auto it = number.rbegin();
  while (it != number.rend()) {
    std::cout << *it;
    it++;
  }
  std::cout << std::endl;
}

int main() {
  number_t number;
  int acc;

  std::cout << MAX_DIGITS << std::endl;
  // number.fill(0);
  number.reserve(MAX_DIGITS);
  number.push_back(1);
  for (int i = 0; i < EXPONENT; i++) {
    multiply(number, BASE);
    // dump_number(number);
  }
  dump_number(number);

  acc = 0;
  for (int i: number)
    acc += i;
  std::cout << acc << std::endl;
  std::cout << "profiler_a: " << profiler_a << std::endl;

  return 0;
}
