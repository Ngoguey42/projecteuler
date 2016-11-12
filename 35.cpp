
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

  const int _num_digit;
  const int _lower_power_of_10;
  int _rot_id;
  int _nbr;

public:
  IntRotationIterator(int nbr, int num_digit, int lower_power_of_10)
    : _num_digit(num_digit)
    , _lower_power_of_10(lower_power_of_10)
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
    _nbr += tmp * _lower_power_of_10;
    _rot_id++;
    return *this;
  }

  bool done() const {
    return _rot_id >= _num_digit;
  }

};

#define MAX_DIGIT 6

int main() {

  Primes p(pow(10, MAX_DIGIT) - 1.0);
  int count;
  int num_digits, min_value, max_value;

  auto is_circular_prime = [&](int i) {
    IntRotationIterator it(i, num_digits, min_value);

    while (!it.done()) {
      if (!p.is_prime(*it))
        return false;
      ++it;
    }
    return true;
  };

  count = 0;
  num_digits = 1;
  while (num_digits <= MAX_DIGIT) {
    min_value = pow(10, num_digits - 1);
    max_value = pow(10, num_digits) - 1;
    std::cout
      << "num_digits(" << num_digits << ") "
      << "min_value(" << min_value << ") "
      << "max_value(" << max_value << ") "
      << std::endl;
    for (int i = p.next(std::max(min_value - 1, 1)); i <= max_value; i = p.next(i)) {
      if (is_circular_prime(i)) {
        std::cout << i << std::endl;
        count++;
      }
    }
    num_digits++;
  }
  std::cout << count << std::endl;
  return 0;
}
