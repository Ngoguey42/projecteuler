// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   51.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/14 17:54:24 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/14 19:04:46 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "51.hpp"

void Functor::_register_prime(unsigned int nbr) {
  BCDNumber<uint32_t> bcd{nbr};
  std::unordered_map<bcd_t, uint32_t, bcd_t::Hash>::iterator it;

  if (bcd.all_digit_equal(_rev_fam_mask)) {
    bcd &= _fam_mask;
    it = _family_map.find(bcd);
    if (it == _family_map.end()) {
      _family_map.emplace(bcd, 1);
    }
    else {
      it->second++;
      _max_family_size = std::max(_max_family_size, it->second);
    }
  }
}

int Functor::_foreach_primes() {
  _family_map.clear();
  _max_family_size = 0;

  for (unsigned int p = _pr.next(_min_value - 1);
       p <= _max_value;
       p = _pr.next(p)) {
    _register_prime(p);
  }

  std::cout << "  family count(" << _family_map.size() << ") ";
  std::cout << "  _max_family_size(" << _max_family_size << ")" << std::endl;
  std::cout << std::endl;
  if (_max_family_size >= 8) {
    for (auto const &pair: _family_map) {
      if (pair.second == 8)
        std::cout << "----------" << pair.first.decode() << std::endl;
    }
  }
  return 0;
}

int Functor::_foreach_mask(unsigned int k) {
  IntComboIterator it(_num_digit, k);
  int best;

  best = std::numeric_limits<int>::max();
  while (!it.done()) {
    _fam_mask = bcd_t{*it};
    _rev_fam_mask = _fam_mask;
    ~_rev_fam_mask;
    _rev_fam_mask &= _all_digit_mask;
    std::cout << "  mask " << _fam_mask
              << " rev " << _rev_fam_mask << std::endl;
    best = std::min(best, _foreach_primes());
    ++it;
  }
  return best == std::numeric_limits<int>::max() ? 0 : best;
}

Functor::Functor()
  : _pr(999999) {
}

int Functor::operator()() {
  int i;
  std::deque<int> tmp;

  for (_num_digit = 2; _num_digit <= 8; _num_digit++) {
    tmp.resize(_num_digit);
    std::iota(tmp.begin(), tmp.end(), 0);
    _all_digit_mask = bcd_t{tmp};
    _min_value = pow(10, _num_digit - 1);
    _max_value = pow(10, _num_digit) - 1;
    std::cout
      << "_num_digit(" << _num_digit << ") "
      << "_min_value(" << _min_value << ") "
      << "_max_value(" << _max_value << ") "
      << "_all_digit_mask(" << _all_digit_mask << ") "
      << std::endl;
    for (unsigned int k = 1; k < _num_digit; k++) {
      std::cout << " mask size " << k << std::endl;
      i = _foreach_mask(k);
      if (i != 0)
        break ;
    }
    if (_num_digit == 7)
    break ;
  }
  return 0;
}

int main() {
  Functor{}();
  return 0;
}
