
#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>

static int next_number(int i) {
  i++;
  if (i % 10 == 0)
    return i + 1;
  else
    return i;
}

static bool double_same(double a, double b) {
  return std::fabs(a - b) < 0.0001;
}

static double divide(int n, int d) {
  return  static_cast<double>(n) / static_cast<double>(d);
}

static bool is_curious(int n, int d) {
  const double fract = divide(n, d);

  if (n % 10 == d % 10 && double_same(fract, divide(n / 10, d / 10)))
    return true;
  else if (n / 10 == d / 10 && double_same(fract, divide(n % 10, d % 10)))
    return true;
  else if (n % 10 == d / 10 && double_same(fract, divide(n / 10, d % 10)))
    return true;
  else if (n / 10 == d % 10 && double_same(fract, divide(n % 10, d / 10)))
    return true;
  else
    return false;
}

static std::set<int> factors(int nbr) {
  std::set<int> factors;
  int i;

  i = static_cast<int>(floor(sqrt(static_cast<double>(nbr))));
  while (i > 0) {
    if (nbr % i == 0) {
      factors.insert(i);
      factors.insert(nbr / i);
    }
    i--;
  }
  return factors;
}

static std::pair<int, int> simplify_fraction(int n, int d) {
  const std::set<int> n_factors = factors(n);
  const std::set<int> d_factors = factors(d);
  std::vector<int> sorted_common_factors;

  std::set_intersection(n_factors.begin(), n_factors.end(),
                        d_factors.begin(), d_factors.end(),
                        std::back_inserter(sorted_common_factors));

  for (auto it = sorted_common_factors.rbegin();
       it != sorted_common_factors.rend();
       ++it) {
    if (n % *it == 0 && d % *it == 0) {
      n /= *it;
      d /= *it;
    }
  }
  return {n, d};
}

int main() {
  int curious_n, curious_d;

  curious_n = 1;
  curious_d = 1;
  for (int n = 11; n <= 98; n = next_number(n)) {
    for (int d = next_number(n); d <= 99; d = next_number(d)) {
      if (is_curious(n, d)) {
        std::cout
          << "n(" << n << ") / "
          << "d(" << d << ") "
          << std::endl;
        curious_n *= n;
        curious_d *= d;
      }
    }
  }
  std::cout
    << "curious_n(" << curious_n << ") / "
    << "curious_d(" << curious_d << ")"
    << std::endl;
  std::tie(curious_n, curious_d) = simplify_fraction(curious_n, curious_d);
  std::cout
    << "curious_n(" << curious_n << ") / "
    << "curious_d(" << curious_d << ")"
    << std::endl;
  return 0;
}
