

#include <iostream>
#include <deque>

// V1 *********************************************************************** **
bool is_palindrome1(int nbr, int base) {
  std::deque<int> dq;

  while (nbr != 0) {
    dq.push_back(nbr % base);
    nbr /= base;
  }
  while (dq.size() > 1) {
    if (dq.front() != dq.back())
      return false;
    dq.pop_front();
    dq.pop_back();
  }
  return true;
}

// V2 *********************************************************************** **
// same complexity, 13 times faster both with Ofast
bool is_palindrome2(unsigned int nbr, int base, int encoding_width, int encoding_mask) {
  size_t rev_nbr;
  unsigned int tmp;

  tmp = nbr;
  rev_nbr = tmp % base;
  tmp /= base;
  while (tmp != 0) {
    rev_nbr <<= encoding_width;
    rev_nbr += tmp % base;
    tmp /= base;
  }
  while (nbr != 0) {
    if ((rev_nbr & encoding_mask) != nbr % base)
      return false;
    nbr /= base;
    rev_nbr >>= encoding_width;
  }
  return true;
}

// MAIN ********************************************************************* **
#define MAX (100000000 - 1)

int main() {
  int acc;

  acc = 0;
  for (unsigned int i = 0; i <= MAX; i++) {
    // if (is_palindrome1(i, 10) && is_palindrome1(i, 2)) {
    if (is_palindrome2(i, 10, 4, 0b1111) && is_palindrome2(i, 2, 1, 0b1)) {
      std::cout << i << std::endl;
      acc += i;
    }
  }
  std::cout << acc << std::endl;
  return 0;
}
