
#include <iostream>
#include <cmath>

template <class T>
class TriangularNumberIterator {
  T _n;
  T _add;

public:

  TriangularNumberIterator()
    : _n(1)
    , _add(1) {
  }

  T operator *() const {
    return _n;
  }

  TriangularNumberIterator &operator ++() {
    ++_add;
    _n += _add;
    return *this;
  }

};

int num_factors(const size_t n) {
  const size_t ceil_sqrt = static_cast<size_t>(ceil(sqrt(static_cast<double>(n))));
  const size_t half_min_epsilon = (n + 1) / 2 - 1;
  size_t i = std::min(ceil_sqrt, half_min_epsilon);
  int count;

  count = 0;
  for (; i > 0; i--) {
    if (n % i == 0) {
      // std::cout << "  " << i << std::endl;
      if (i * i == n)
        count++;
      else
        count += 2;
    }
  }
  return count;
}

int main() {
  TriangularNumberIterator<size_t> it;
  int n;

  while (true) {
    n = num_factors(*it);
    std::cout << *it << ": " << n << std::endl;
    if (n >= 500)
      break ;
    ++it;
  }
  std::cout << *it << std::endl;
  return 0;
}
