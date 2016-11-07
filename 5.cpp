
#include <iostream>
#include <vector>

class PrimeIterator {

  const int _max;
  std::vector<bool> _sieve;
  int _cur;

public:
  PrimeIterator() = delete;
  PrimeIterator(int max)
    : _max(max)
    , _sieve(max + 1, true)
    , _cur(1) {
  }

  int operator *() const {
    return _cur;
  }

  void operator ++() {
    int tmp;

    do {
      ++_cur;
    } while (_cur <= _max && _sieve[_cur] == false);
    if (_cur <= _max) {
      tmp = _cur;
      while (tmp <= _max) {
        _sieve[tmp] = false;
        tmp += _cur;
      }
    }
  }

  bool done() const {
    return _cur > _max;
  }

};

#define BOUND 20

int main() {
  int res, prime_power;
  auto it = PrimeIterator(BOUND);

  res = 1;
  ++it;
  while (!it.done()) {
    std::cout << *it << std::endl;
    prime_power = *it;
    while (prime_power <= BOUND) {
      res *= *it;
      prime_power *= *it;
    }
    std::cout << "  " << res << std::endl;
    ++it;
  }
  std::cout << res << std::endl;
}
