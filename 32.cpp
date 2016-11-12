
#include <iostream>
#include <array>
#include <unordered_set>
#include <numeric>

bool is_pandigital_product(int a, int b) {
  std::array<bool, 10> digits{{false}};

  auto is_still_pandigital = [&](int i) {
    while (i != 0) {
      if (digits[i % 10] == true || i % 10 == 0)
        return false;
      digits[i % 10] = true;
      i /= 10;
    }
    return true;
  };

  return is_still_pandigital(a) &&
    is_still_pandigital(b) &&
    is_still_pandigital(a * b);
}

int main() {
  std::unordered_set<int> match_set;

  auto compute_pandigitals =
    [&](std::pair<int, int> a_bounds, int b_min, int prod_max) {
    for (int a = a_bounds.first; a <= a_bounds.second; a++) {
      for (int b = b_min; b <= prod_max / a; b++) {
        if (is_pandigital_product(a, b)) {
          std::cout
          << "a(" << a << ") "
          << "b(" << b << ") "
          << "a * b(" << a * b << ") "
          << std::endl;
          match_set.insert(a * b);
        }
      }
    }
  };

  compute_pandigitals({1, 9}, 1000, 9999);
  compute_pandigitals({10, 99}, 100, 9999);
  std::cout << match_set.size() << std::endl;
  std::cout << std::accumulate(match_set.begin(), match_set.end(), 0)
            << std::endl;
  return 0;
}
