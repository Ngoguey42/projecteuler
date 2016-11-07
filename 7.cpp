
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>

int upper_bound_of_nth_prine(int n) {
  const double d = static_cast<double>(n);
  const double ld = log(d);
  const double lld = log(ld);

  assert(n >= 6);
  return static_cast<int>(ceil(d * ld + d * lld));
}

int nth_prime(int n) {

  const int upper_bound = upper_bound_of_nth_prine(n);
  std::vector<bool> sieve(upper_bound + 1, true);
  int p;
  int s;

  std::cout << upper_bound << std::endl;
  p = 2;
  for (int i = 1; i < n; i++) {
    s = p;
    while (s <= upper_bound) {
      sieve[s] = false;
      s += p;
    }
    do {
      p++;
    } while (sieve[p] == false);
    std::cout << i + 1 << " " << p << std::endl;
  }
  return p;
}

int main() {
  std::cout << nth_prime(10001) << std::endl;
  return 0;
}
