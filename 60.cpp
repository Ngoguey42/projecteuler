// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   60.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/15 16:23:20 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/15 19:47:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "60.hpp"

#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>

#define PRIME_MAX 99999999
#define NUMDIGIT_MAX 8

int main() {
  Functor{}();
  return 0;
}

// FUNCTOR ****************************************************************** **

const primeint Functor::_min_value_of_digit_count[10] ={
  0, 0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000
};

Functor::Functor()
  : _pr(PRIME_MAX) {
}

void Functor::operator ()() {
  primeint min, max;

  for (_num_digit = 2; _num_digit <= NUMDIGIT_MAX; _num_digit++) {
    min = _min_value_of_digit_count[_num_digit];
    max = pow(10, _num_digit) - 1;
    std::cout
      << "_num_digit(" << _num_digit << ") "
      << "min(" << min << ") "
      << "max(" << max << ") "
      << std::endl;
    for (primeint p = _pr.next(min); p <= max; p = _pr.next(p)) {
      _decompose_prime(p);
    }
  }
}

std::pair<primeint, primeint> Functor::_cut_prime(primeint p) {
  primeint rhs;
  primeint fact;

  fact = 1;
  rhs = 0;
  for (size_t i = 0; i < _suffix_size; i++, fact *= 10) {
    rhs += (p % 10) * fact;
    p /= 10;
  }
  return {p, rhs};
}

void Functor::_decompose_prime(primeint p) {
  const size_t max_prefix_size = _num_digit / 2;
  primeint lhs, rhs;

  _prefix_size = 1;
  _suffix_size = _num_digit - 1;
  for (; _prefix_size <= max_prefix_size; _prefix_size++, _suffix_size--) {
    // std::cout
    // << "_prefix_size(" << _prefix_size << ") "
    // << "_suffix_size(" << _suffix_size << ") "
    // << std::endl;
    std::tie(lhs, rhs) = _cut_prime(p);
    _handle_prime_decomposition(lhs, rhs);
  }
}

bool Functor::_rhs_has_leading_zero(primeint rhs) {
  return rhs < _min_value_of_digit_count[_suffix_size];
}

void Functor::_handle_prime_decomposition(primeint lhs, primeint rhs) {
  if (_rhs_has_leading_zero(rhs))
    return ;

  if (lhs < rhs && _pr.is_prime(lhs) && _pr.is_prime(rhs) &&
      _pr.is_prime(lhs + rhs * _min_value_of_digit_count[_prefix_size + 1])) {
    _register_a_with_b(lhs, rhs);
    _register_a_with_b(rhs, lhs);
    (void)_family_size(lhs, rhs);
  }
}

void Functor::_register_a_with_b(primeint a, primeint b) {
  auto it = _prime_presuf.find(a);

  if (it == _prime_presuf.end())
    _prime_presuf.emplace(a, std::vector<primeint>{b});
  else {
    it->second.push_back(b);
  }
}

size_t Functor::_family_size(primeint a, primeint b) {
  std::deque<primeint> pretendings;
  auto const &va = _prime_presuf[a];
  auto const &vb = _prime_presuf[b];
  primeint sum;

  std::set_intersection(va.begin(), va.end(), vb.begin(), vb.end(),
                        std::back_inserter(pretendings));

  _narrow_family(pretendings);
  if (pretendings.size() + 2 >= 5) {
    std::cout << "size = " << pretendings.size() + 2 << ": ";
    sum = a + b;
    for (primeint p: pretendings) {
      std::cout << p << " + ";
      sum += p;
    }
    std::cout << a << " + " << b;
    std::cout << " = " << sum << std::endl;
  }
  return 2 + pretendings.size();
}

void Functor::_narrow_family(std::deque<primeint> &pretendings) {
  std::vector<primeint> tmp;
  std::deque<int> pretendings_sizes;
  std::deque<int>::iterator minsize;
  std::vector<primeint> const *tmp_ptr;

  tmp.reserve(pretendings.size());
  while (pretendings.size() > 1) {
    pretendings_sizes.resize(pretendings.size(), 0);
    for (size_t i = 0; i < pretendings.size(); i++) {
      tmp_ptr = &_prime_presuf[pretendings[i]];
      tmp.clear();
      std::set_intersection(pretendings.begin(), pretendings.end(),
                            tmp_ptr->begin(), tmp_ptr->end(),
                            std::back_inserter(tmp));
      pretendings_sizes[i] = tmp.size();
    }
    minsize = std::min_element(pretendings_sizes.begin(), pretendings_sizes.end());

    if (*minsize == (int)pretendings.size() - 1)
      break ;
    pretendings.erase(pretendings.begin() + (std::distance(pretendings_sizes.begin(), minsize)));
  }
}

// PRIMES ******************************************************************* **
std::vector<bool> Primes::_sieve_of_max(primeint max) { // static
  std::vector<bool> v(max + 1, true);

  v[0] = false;
  v[1] = false;
  for (primeint p = 2; p <= max; p++) {
    if (v[p] == true) {
      for (primeint i = p * 2; i <= max; i += p)
        v[i] = false;
    }
  }
  return v;
}

Primes::Primes(primeint max)
  : _sieve(_sieve_of_max(max)) {
}

bool Primes::is_prime(primeint p) const {
  return _sieve[p];
}

primeint Primes::next(primeint p) const {
  ++p;
  while (p < static_cast<primeint>(_sieve.size()) && _sieve[p] == false)
    ++p;
  if (p >= static_cast<primeint>(_sieve.size()))
    return static_cast<primeint>(_sieve.size());
  else
    return p;
}
