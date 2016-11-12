
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <deque>

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

class CuriousFractions {

  int _n, _d;

  int _next_number(int i) {
    i++;
    if (i % 10 == 0)
      return i + 1;
    else
      return i;
  }

  bool _double_same(double a, double b) {
    return std::fabs(a - b) < 0.0001;
  }

  double _divide(int n, int d) {
    return  static_cast<double>(n) / static_cast<double>(d);
  }

  bool _is_curious() {
    const double fract = _divide(_n, _d);

    if (_n % 10 == _d % 10 && _double_same(fract, _divide(_n / 10, _d / 10)))
      return true;
    else if (_n / 10 == _d / 10 && _double_same(fract, _divide(_n % 10, _d % 10)))
      return true;
    else if (_n % 10 == _d / 10 && _double_same(fract, _divide(_n / 10, _d % 10)))
      return true;
    else if (_n / 10 == _d % 10 && _double_same(fract, _divide(_n % 10, _d / 10)))
      return true;
    else
      return false;
  }

public:
  std::deque<std::pair<int, int>> operator()() {
    std::deque<std::pair<int, int>> curious_fractions;

    for (_n = 11; _n <= 98; _n = _next_number(_n))
      for (_d = _next_number(_n); _d <= 99; _d = _next_number(_d))
        if (_is_curious())
          curious_fractions.emplace_back(_n, _d);
    return curious_fractions;
  }

};

int main() {
  int curious_n, curious_d;

  curious_n = 1;
  curious_d = 1;
  for (auto pair: CuriousFractions{}()) {
    std::cout << pair.first << "/" << pair.second << std::endl;
    curious_n *= pair.first;
    curious_d *= pair.second;
  }

  std::cout << curious_n << "/" << curious_d << std::endl;
  std::tie(curious_n, curious_d) = simplify_fraction(curious_n, curious_d);
  std::cout << curious_n << "/" << curious_d << std::endl;
  return 0;
}
