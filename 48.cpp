
#include <iostream>
#include <array>

#define PRECISION 10
using nbr_t = std::array<int, PRECISION>;

void multiply(nbr_t &nbr, int factor) {
  int carry;

  carry = 0;
  for (int &digit: nbr) {
    carry += digit * factor;
    digit = carry % 10;
    carry /= 10;
  }
  // ignoring carry
  return ;
}

void add(nbr_t &dst, nbr_t const &rhs) {
  int carry;

  carry = 0;
  for (int i = 0; i < PRECISION; i++) {
    carry += dst[i] + rhs[i];
    dst[i] = carry % 10;
    carry /= 10;
  }
  // ignoring carry
  return ;
}

int main() {
  nbr_t nbr{0};
  nbr_t acc{0};

  for (int i = 1; i <= 1000; i++) {
    nbr.fill(0);
    nbr[0] = 1;
    for (int j = 0; j < i; j++)
      multiply(nbr, i);
    add(acc, nbr);
  }
  for (auto it = acc.crbegin(); it != acc.crend(); ++it) {
    std::cout << *it;
  }
  std::cout << std::endl;
  return 0;

}
