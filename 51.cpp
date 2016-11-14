// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   51.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/14 17:54:24 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/14 20:24:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "51.hpp"

int main() {
  Functor{}();
  return 0;
}

Functor::Functor()
  : _pr(99999999) {
}

static BCDNumber<uint32_t> create_all_digit_mask(int num_digit) {
  std::deque<int> tmp;

  tmp.resize(num_digit);
  std::iota(tmp.begin(), tmp.end(), 0);
  return BCDNumber<uint32_t>{tmp};
}

void Functor::operator()() {
  for (_num_digit = 2; _num_digit <= 8; _num_digit++) {
    _min_value = pow(10, _num_digit - 1);
    _max_value = pow(10, _num_digit) - 1;
    _all_digit_mask = create_all_digit_mask(_num_digit);
    std::cout
      << "_num_digit(" << _num_digit << ") "
      << "_min_value(" << _min_value << ") "
      << "_max_value(" << _max_value << ") "
      << "_all_digit_mask(" << _all_digit_mask << ") "
      << std::endl;
    if (_handle_number_width())
      break ;
  }
}

bool Functor::_handle_number_width() {

  _matching_families.clear();
  for (_fam_mask_width = 1; _fam_mask_width < _num_digit; _fam_mask_width++) {
    std::cout
      << " "
      << "_fam_mask_width(" << _fam_mask_width << ") "
      << std::endl;
    _handle_mask_width();
  }
  if (_matching_families.size() != 0) {
    std::cout << "FOUND !" << std::endl;
    for (bcd_t n: _matching_families)
      std::cout << n.decode() << std::endl;
    return true;
  }
  else
    return false;
}

void Functor::_handle_mask_width() {
  IntComboIterator it(_num_digit, _fam_mask_width);

  while (!it.done()) {
    _fam_mask = bcd_t(*it);
    _rev_fam_mask = _fam_mask;
    ~_rev_fam_mask;
    _rev_fam_mask &= _all_digit_mask;
    std::cout
      << "  "
      << "_fam_mask(" << _fam_mask << ") "
      << "_rev_fam_mask(" << _rev_fam_mask << ") "
      << std::endl;
    _handle_mask();
    ++it;
  }
}

void Functor::_handle_mask() {
  _family_map.clear();
  _max_family_size = 0;
  for (_p = _pr.next(_min_value - 1); _p <= _max_value; _p = _pr.next(_p)) {
    _handle_prime();
  }
  if (_max_family_size >= 8) {
    for (auto const &pair: _family_map) {
      if (pair.second == 8) {
        _matching_families.insert(pair.first);
      }
    }
  }
}

void Functor::_handle_prime() {
  bcd_t tmp;
  std::unordered_map<bcd_t, uint32_t, bcd_t::Hash>::iterator it;
  tmp = {_p};

  if (tmp.all_digit_equal(_rev_fam_mask)) {
    tmp &= _fam_mask;
    it = _family_map.find(tmp);
    if (it == _family_map.end()) {
      _family_map.emplace(tmp, 1);
    }
    else {
      it->second++;
      _max_family_size = std::max(_max_family_size, it->second);
    }
  }
}
