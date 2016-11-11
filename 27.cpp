
#include <iostream>
#include <tuple>
#include <vector>
#include <cassert>

#define A_MIN -9990
#define A_MAX 9990
// #define B_MIN -100000
#define B_MAX 100000

class PrimeContainer {

  std::vector<bool> _sieve;

  static std::vector<bool> _make_sieve(int max) {
    int p;
    std::vector<bool> sieve;

    sieve.resize(max + 1, true);
    p = 2;
    while (p <= max) {
      if (sieve[p] == true) {
        for (int i = p * 2; i <= max; i += p)
          sieve[i] = false;
      }
      p++;
    }
    return sieve;
  }

public:
  ~PrimeContainer() = default;
  PrimeContainer() = delete;
  PrimeContainer(int max)
    : _sieve(_make_sieve(max)) {
    _sieve.resize(max, false);
  }
  PrimeContainer(PrimeContainer const&) = delete;
  PrimeContainer &operator =(PrimeContainer const&) = delete;

  int next(int p) const {

    ++p;
    while (true) {
      assert(p < (int)_sieve.size());
      if (_sieve[p] == true)
        return p;
      ++p;
    }
  }

  bool is_prime(int n) const {
    assert(n < (int)_sieve.size());
    return _sieve[n];
  }

};

class Functor {

  PrimeContainer _pc;

  int _num_consecutive_prime(int a, int b) {
    int n, count, res;

    n = 0;
    count = 0;
    while ((res = n * n + n * a + b) > 0 && _pc.is_prime(res)) {
      count++;
      n++;
    }
    return count;
  }

public:
  Functor()
    : _pc(10000000) {
  }

  void operator()() {
    std::tuple<int, int, int> max;
    int tmp;

    max = std::make_tuple(0, 0, 0);
    for (int a = A_MIN; a <= A_MAX; a++) {
      for (int b = 2; b <= B_MAX; b = _pc.next(b)) {
        tmp = _num_consecutive_prime(a, b);
        if (tmp > std::get<0>(max)) {
          std::cout
            << "a(" << a << ") "
            << "b(" << b << ") "
            << tmp
            << std::endl;
          max = std::make_tuple(tmp, a, b);
        }
      }
    }
    return ;
  }

};

int main() {
  Functor{}();
  return 0;
}
