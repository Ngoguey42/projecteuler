// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   51.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/14 17:50:56 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/14 20:25:01 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _51_HPP
# define _51_HPP

#include <iostream>
#include <limits>
#include <vector>
#include <set>
#include <cassert>
#include <deque>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>

// BCD ********************************************************************** **
// BCD = Binary coded decimal
template <typename T>
class BCDNumber {

  T _number;

  static T _bcd_of_bcb(T n) {
    T bcd;
    int i;

    bcd = 0;
    i = 0;
    while (n != 0) {
      bcd |= (n % 10) << (4 * i++);
      n /= 10;
    }
    return bcd;
  }

  static T _mask_of_indices(std::deque<int> const &digit_indices) {
    T mask;

    mask = 0;
    for (int digit_index: digit_indices) {
      mask |= 0xf << (digit_index * 4);
    }
    return mask;
  }

public:

  BCDNumber(T n)
    : _number(_bcd_of_bcb(n)) {
  }
  BCDNumber(std::deque<int> const &digit_indices)
    : _number(_mask_of_indices(digit_indices)) {
  }
  BCDNumber(T n, bool)
    : _number(n) {
  }
  ~BCDNumber() = default;
  BCDNumber() = default;
  BCDNumber(BCDNumber const &) = default;
  BCDNumber &operator =(BCDNumber const &) = default;

  T number() const {
    return _number;
  }

  T decode() const {
    T n;
    T bcd;
    T fact;

    bcd = _number;
    n = 0;
    fact = 1;
    while (bcd != 0) {
      if ((bcd & 0xf) == 0xf)
        n += 1 * fact;
      else
        n += (bcd & 0xf) * fact;
      bcd >>= 4;
      fact *= 10;
    }
    return n;
  }

  bool all_digit_equal(BCDNumber const &m) const {
    T nbr;
    T mask;
    T digit;

    digit = 10;
    nbr = _number;
    mask = m._number;
    for (unsigned int i = 0; i < (sizeof(T) * 8) / 4; i++) {
      if (mask & 0xf) {
        if (digit == 10)
          digit = (nbr & 0xf);
        else if (digit != (nbr & 0xf))
          return false;
      }
      nbr >>= 4;
      mask >>= 4;
    }
    return true;
  }

  void operator &=(BCDNumber<T> const &m) {
    _number &= m._number;
  }

  void operator +=(BCDNumber<T> const &rhs) {
    _number = _bcd_of_bcb(this->decode() + rhs.decode());
  }

  void operator ~() {
    T tmp = 0xf;

    for (unsigned int i = 0; i < (sizeof(T) * 8) / 4; i++) {
      if (_number & tmp)
        _number &= ~tmp;
      else
        _number |= tmp;
      tmp <<= 4;
    }
  }

  bool operator ==(BCDNumber const &rhs) const {
    return _number == rhs._number;
  }

  struct Hash {

    size_t operator()(BCDNumber const &n) const {
      return std::hash<uint32_t>{}(n._number);
    }

  };

};

template <class T>
std::ostream &operator <<(std::ostream &o, BCDNumber<T> const &n) {
  o << n.decode();
  return o;
}

// PRIMES ******************************************************************* **
class Primes {

  const std::vector<bool> _sieve;

  static std::vector<bool> _sieve_of_max(unsigned int max) {
    std::vector<bool> sieve(max + 1, true);

    sieve[0] = false;
    sieve[1] = false;
    for (unsigned int i = 2; i <= max; i++) {
      if (sieve[i] == true) {
        for (unsigned int j = i * 2; j <= max; j += i)
          sieve[j] = false;
      }
    }
    return sieve;
  }

public:
  Primes(unsigned int max)
    : _sieve(_sieve_of_max(max)) {
  }
  ~Primes() = default;
  Primes() = delete;
  Primes(Primes const &) = delete;
  Primes &operator =(Primes const &) = delete;

  unsigned int next(unsigned int p) const {
    do {
      p++;
    } while (p < _sieve.size() && _sieve[p] == false);
    return p;
  }

  unsigned int is_prime(unsigned int p) const {
    return _sieve[p];
  }

};

// ************************************************************************** **
class IntComboIterator {
  const int _n;
  const int _k;
  std::vector<bool> _bitmask;
  bool _done;

public:
  IntComboIterator(int n, int k)
    : _n(n)
    , _k(k)
    , _done(false) {
    _bitmask.resize(k, true); // (K, 1); // K leading 1's
    _bitmask.resize(n, false); // N-K trailing 0's
  }
  ~IntComboIterator() = default;
  IntComboIterator() = delete;
  IntComboIterator(IntComboIterator const &) = delete;
  IntComboIterator &operator =(IntComboIterator const &) = delete;

  std::deque<int> operator *() const {
    std::deque<int> dq;

    for (int i = 0; i < _n; i++)
      if (_bitmask[i] == true)
        dq.push_back(i);
    return dq;
  }

  void operator ++() {
    _done = !std::prev_permutation(_bitmask.begin(), _bitmask.end());
  }

  bool done() const {
    return _done;
  }

};

class Functor {

  using bcd_t = BCDNumber<uint32_t>;

  const Primes _pr;

  unsigned int _num_digit;
  unsigned int _min_value;
  unsigned int _max_value;
  bcd_t _all_digit_mask;

  bool _handle_number_width();
  unsigned int _fam_mask_width;
  std::unordered_set<bcd_t, bcd_t::Hash> _matching_families;

  void _handle_mask_width();
  bcd_t _fam_mask;
  bcd_t _rev_fam_mask;

  void _handle_mask();
  unsigned int _p;
  std::unordered_map<bcd_t, uint32_t, bcd_t::Hash> _family_map;
  unsigned int _max_family_size;

  void _handle_prime();

public:
  Functor();
  void operator()();

};

#endif
