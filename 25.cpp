
#include <vector>
#include <cassert>
#include <iostream>

using nbr_t = std::vector<int>;

void add(nbr_t &a, nbr_t const &b) {

  int carry;
  size_t index;

  carry = 0;
  index = 0;
  for (int rhs_digit: b) {
    carry += rhs_digit;
    if (index < a.size()) {
      carry += a[index];
      a[index] = carry % 10;
      carry /= 10;
    }
    index++;
  }
  assert(carry < 10);
  if (carry != 0) {
    a.push_back(carry);
  }
  return ;
}

#define AIM 80000 // O(N^1.93)

int main() {

  nbr_t nbrs[2];
  int lower, other;
  int others_index;

  for (auto &n: nbrs) {
    n.reserve(AIM);
    n.push_back(1);
  }
  lower = 0;
  other = 1;
  others_index = 2;
  while (nbrs[other].size() != AIM) {
    add(nbrs[lower], nbrs[other]);
    lower = other;
    other = (lower + 1) % 2;
    others_index++;
  }
  std::cout << others_index << std::endl;

  std::cout << "Bye World" << std::endl;
  return 0;
}
