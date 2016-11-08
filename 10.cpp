

#include <iostream>
#include <vector>
// #include <cassert>
// #include <cmath>

class PrimeIterator {
  const int _max;
  std::vector<bool> _sieve;
  int _prime;

public:

  PrimeIterator() = delete;
  PrimeIterator(PrimeIterator const &) = default;
  PrimeIterator &operator=(PrimeIterator const &) = default;

  PrimeIterator(int max)
    : _max(max)
    , _sieve(max + 1, true)
    , _prime(2) {
    _set_prime(2);
  }

  int operator *() const {
    return _prime;
  }

  bool done() const {
    return _prime == 0;
  }

  PrimeIterator &operator++() {
    int p;

    p = _prime;
    do {
      ++p;
    } while (p <= _max && _sieve[p] == false);
    if (p > _max)
      _prime = 0;
    else
      _set_prime(p);
    return *this;
  }

private:
  void _set_prime(int p) {
    _prime = p;
    for (int i = p; i <= _max; i += p)
      _sieve[i] = false;
  }

};

int main() {

  auto it = PrimeIterator{2000000};
  size_t acc;

  acc = 0;
  while (!it.done()) {
    acc += static_cast<size_t>(*it);
    ++it;
  }
  std::cout << acc << std::endl;
  return 0;
}
