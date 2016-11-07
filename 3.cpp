
#include <cmath>
#include <cassert>
#include <iostream>
#include <set>

int profile_a = 0;
int profile_b = 0;

bool is_integer_square(size_t i) {
  size_t sr;

  sr = static_cast<size_t>(sqrt(static_cast<double>(i)));
  return sr * sr == i;
}

size_t fermatfactor(size_t n) {
  size_t a, b_squared;

  profile_a++;
  assert(n % 2 == 1);
  a = ceil(sqrt(n));
  b_squared = a * a - n;
  while (!is_integer_square(b_squared)) {
    profile_b++;
    a++;
    b_squared = a * a - n;
  }
  return a - static_cast<size_t>(sqrt(static_cast<double>(b_squared)));
}


void add_factors(size_t n, std::set<size_t> &set) {

  const size_t fact = fermatfactor(n);

  if (fact == 1) {
    assert(set.count(n) == 0);
    set.insert(n);
  }
  else {
    add_factors(fact, set);
    add_factors(n / fact, set);
  }
}


std::set<size_t> factors_of_integer(size_t n) {
  std::set<size_t> set;

  add_factors(n, set);
  return set;
}


int main() {

  auto factors = factors_of_integer(600851475143);

  for (size_t i: factors) {
    std::cout << i << std::endl;
  }
  std::cout << "profile_a: " << profile_a << std::endl;
  std::cout << "profile_b: " << profile_b << std::endl;
}
