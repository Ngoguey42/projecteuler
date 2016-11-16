// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   37.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/16 17:01:39 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/16 17:35:07 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "37.hpp"

#include <iostream>

#define MAX_DIGIT 8
#define MAX_VALUE 99999999

int main() {
  Functor{}();
  return 0;
}

Functor::Functor()
  : _pr(MAX_VALUE) {
}

void Functor::operator()() {
  int acc;

  _digit_count = 2;
  _min_value = 10;
  _max_value = 99;

  while (_digit_count <= MAX_DIGIT) {
    std::cout
      << "_digit_count(" << _digit_count << ") "
      << "_min_value(" << _min_value << ") "
      << "_max_value(" << _max_value << ") "
      << std::endl;
    for (size_t p = _pr.next(_min_value - 1); p <= _max_value; p = _pr.next(p)) {
      _handle_prime(p);
    }
    _digit_count++;
    _min_value *= 10;
    _max_value *= 10;
    _max_value += 9;
  }

  acc = 0;
  for (size_t p: _truncable_primes)
    acc += p;
  std::cout << acc << std::endl;

}

void Functor::_handle_prime(size_t const p) {
  size_t tmp;

  tmp = p / 10;
  while (tmp != 0) {
    if (!_pr.is_prime(tmp))
      return ;
    tmp /= 10;
  }

  tmp = _min_value;
  while (tmp > 1) {
    if (!_pr.is_prime(p % tmp))
      return ;
    tmp /= 10;
  }
  std::cout << "FOUND" << p << std::endl;
  _truncable_primes.insert(p);
}

// PRIMES ******************************************************************* **
Primes::Primes(size_t max)
  : _sieve(_sieve_of_max(max)) {
}

std::vector<bool> Primes::_sieve_of_max(size_t max) { // static
  std::vector<bool> v(max + 1, true);

  v[0] = false;
  v[1] = false;
  for (size_t i = 2; i <= max; i++) {
    if (v[i] == true) {
      for (size_t j = i * 2; j <= max; j += i)
        v[j] = false;
    }
  }
  return v;
}

bool Primes::is_prime(size_t p) const {
  return _sieve[p];
}

size_t Primes::next(size_t i) const {
  i++;
  while (i < _sieve.size() && _sieve[i] == false)
    i++;
  return i;
}
