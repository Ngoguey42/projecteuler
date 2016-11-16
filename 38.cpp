// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   38.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/16 18:11:07 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/16 18:53:15 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "38.hpp"

#include <iostream>
#include <cmath>

int main() {
  Functor{}();
  return 0;
}

void Functor::operator()() {
  for (size_t n = 1; n <= 98765; n++) {
    if (_handle_number(n)) {
      std::cout << "Success with " << n
                << " (" << _rebuild_concatenation(n) << ")"
                << std::endl;
    }
  }
}

bool Functor::_handle_number(size_t const nbr) {
  DigitIterator it;
  size_t fact;

  _reset_digit_sieve();
  _digit_count = 0;
  fact = 1;
  while (_digit_count != 9) {
    it = DigitIterator(nbr * fact);
    while (!it.done() && _digit_sieve[*it] == false) {
      _digit_sieve[*it] = true;
      _digit_count++;
      ++it;
    }
    if (!it.done())
      return false;
    fact++;
  }
  return true;
}

void Functor::_reset_digit_sieve() {
  _digit_sieve.fill(false);
  _digit_sieve[0] = true;
}

size_t Functor::_rebuild_concatenation(size_t nbr) {
  size_t res, tmp, fact;

  fact = 1;
  res = 0;
  while (log10(res) < 8) {
    tmp = fact * nbr;
    res *= pow(10, floor(log10(tmp)) + 1);
    res += tmp;
    fact++;
  }
  return res;
}

// DIGIT ITERATOR *********************************************************** **
DigitIterator::DigitIterator()
  : _nbr(0) {
}

DigitIterator::DigitIterator(size_t nbr)
  : _nbr(nbr) {
}

size_t DigitIterator::operator *() const {
  return _nbr % 10;
}

void DigitIterator::operator ++() {
  _nbr /= 10;
}

bool DigitIterator::done() const {
  return _nbr == 0;
}
