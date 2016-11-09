
#include <iostream>
#include <cmath>
#include <vector>

constexpr double fact_value(int fact, double prod) {
  return fact == 0 ? prod : fact_value(fact - 1, prod * fact);
}

#define FACT_OPERAND 100
#define FACT_VALUE fact_value(FACT_OPERAND, 1.0)
#define FACT_VALUE_DIGITS static_cast<int>(ceil(log10(FACT_VALUE)))

using number_t = std::vector<int>;

void multiply(number_t &nbr, int fact) {
  int tmp, carry;

  carry = 0;
  for (int &digit: nbr) {
    tmp = digit * fact + carry;
    // std::cout << "  d " << digit << " ->" << tmp << std::endl;
    digit = tmp % 10;
    carry = tmp / 10;
  }
  while (carry != 0) {
    std::cout << "c" << std::endl;
    nbr.push_back(carry % 10);
    carry /= 10;
  }
}

int main() {

  number_t nbr;
  int acc;

  nbr.reserve(FACT_VALUE_DIGITS);
  nbr.push_back(1);
  for (int i = 2; i <= FACT_OPERAND; i++)
    multiply(nbr, i);
  // for (auto it = nbr.crbegin(); it != nbr.crend(); ++it) {
  //   std::cout << *it;
  // }
  // std::cout << std::endl;
  acc = 0;
  for (int i: nbr)
    acc += i;
  std::cout << acc << std::endl;
  return 0;
}
