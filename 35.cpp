
#include <iostream>
#include <vector>
#include <cmath>

class Primes {

  std::vector<bool> _sieve;

public:
  Primes(int max)
    : _sieve(max + 1, true) {
    for (int i = 2; i <= max; i++) {
      if (_sieve[i] == true) {
        for (int j = i * 2; j <= max; j += i)
          _sieve[j] = false;
      }
    }
  }

  ~Primes() = default;
  Primes() = delete;
  Primes(Primes const &) = delete;
  Primes &operator =(Primes const &) = delete;

  bool is_prime(int nbr) {
    return _sieve[nbr];
  }

  int next(int p) {
    while (_sieve[++p] == false)
      ;
    return p;
  }

};

class IntRotationIterator {

  const int _num_rot;
  const int _upper_power_of_10;
  int _rot_id;
  int _nbr;

public:
  IntRotationIterator(int nbr)
    : _num_rot(static_cast<int>(ceil(log10(nbr))))
    , _upper_power_of_10(static_cast<int>(pow(10, _num_rot - 1)))
    , _rot_id(0)
    , _nbr(nbr) {
  }

  ~IntRotationIterator() = default;
  IntRotationIterator() = delete;
  IntRotationIterator(IntRotationIterator const &) = delete;
  IntRotationIterator operator =(IntRotationIterator const &) = delete;

  int operator *() const {
    return _nbr;
  }

  IntRotationIterator &operator ++() {
    int tmp;

    tmp = _nbr % 10;
    _nbr /= 10;
    _nbr += tmp * _upper_power_of_10;
    _rot_id++;
    return *this;
  }

  bool done() const {
    return _rot_id >= _num_rot;
  }

};

#define MAX (1000000 - 1)

int main() {

  Primes p(MAX);
  int count;

  auto is_circular_prime = [&](int i) {
    IntRotationIterator it(i);

    while (!it.done()) {
      if (!p.is_prime(*it))
        return false;
      ++it;
    }
    return true;
  };

  count = 0;
  for (int i = 2; i <= MAX; i = p.next(i)) {
    if (is_circular_prime(i)) {
      std::cout << i << std::endl;
      count++;
    }
  }
  std::cout << count << std::endl;
  return 0;
}
