
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <numeric>

std::unordered_set<int> divisors(int nbr) {
  std::unordered_set<int> pd;
  int i, j;

  i = static_cast<int>(ceil(sqrt(static_cast<double>(nbr))));
  while (i > 0) {
    j = nbr / i;
    if (j * i == nbr) {
      pd.insert(i);
      pd.insert(j);
    }
    i--;
  }
  return pd;
}

int d(int nbr) {
  auto const pd = divisors(nbr);

  return std::accumulate(pd.begin(), pd.end(), 0) - nbr;
}


int main() {
  using intint_mm_t = std::unordered_multimap<int, int>;

  const int max = 9999;
  intint_mm_t nbr_of_d;
  intint_mm_t::const_iterator it, end;
  int tmp;
  int acc;

  for (int i = 1; i <= max; i++) {
    tmp = d(i);
    nbr_of_d.emplace(tmp, i);
  }

  auto is_reciprocal = [&](int a, int b){
    intint_mm_t::const_iterator it, end;

    std::tie(it, end) = nbr_of_d.equal_range(b);
    while (it != end) {
      if (it->second == a)
        return true;
      ++it;
    }
    return false;
  };

  acc = 0;
  for (int i = 1; i <= max; i++) {
    std::tie(it, end) = nbr_of_d.equal_range(i);

    while (it != end) {
      if (it->second != i && is_reciprocal(i, it->second)) {
        std::cout << i << std::endl;
        acc += i;
      }
      ++it;
    }
  }
  std::cout << "" << std::endl;
  std::cout << acc << std::endl;
  return 0;
}
