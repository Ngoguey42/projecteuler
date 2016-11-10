
#include <set>
#include <vector>
#include <cassert>
#include <iostream>
#include <cmath>

#define MAX 28123

int proper_divisors_sum(int nbr) {
  int i, j, acc;

  if (nbr <= 1)
    return 0;
  i = static_cast<int>(floor(sqrt(static_cast<double>(nbr))));
  acc = 0;
  while (i > 1) {
    if (nbr % i == 0) {
      j = nbr / i;
      acc += i;
      if (i != j)
        acc += j;
    }
    i--;
  }
  return acc + 1;
}

int main() {
  std::set<int> ordered_abudant;
  std::vector<bool> sieve;
  std::set<int>::const_iterator it, it2, end;
  int acc;

  for (int i = 1; i <= MAX; i++) {
    if (i < proper_divisors_sum(i)) {
      ordered_abudant.insert(i);
    }
  }


  sieve.resize(MAX + 1, false);
  it = ordered_abudant.cbegin();
  end = ordered_abudant.cend();
  while (it != end) {
    it2 = it;
    while (it2 != end && *it2 + *it <= MAX) {
      sieve[*it2 + *it] = true;
      ++it2;
    }
    ++it;
  }


  acc = 0;
  for (int i = 0; i <= MAX; i++)
    if (sieve[i] == false)
      acc += i;
  std::cout << acc << std::endl;
  return 0;
}
