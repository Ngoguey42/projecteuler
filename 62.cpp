// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   62.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/15 21:47:26 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/15 23:08:47 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "62.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
  Functor{}();
  return 0;
}

void Functor::operator()() {
  int n;
  size_t cube;
  size_t max_value;
  const size_t max_digit = floor(log10(size_t(-1)));

  n = 0;
  _digit_count = 1;
  _found = false;
  max_value = 9;
  while (!_found && _digit_count <= max_digit) {
    std::cout
      << "_digit_count(" << _digit_count << ") "
      << std::endl;
    _cubes_grouped.clear();
    while (true) {
      cube = _cube(n);
      if (cube > max_value)
        break ;
      _handle_cube(cube);
      n++;
    }
    max_value *= 10;
    max_value += 9;
    _digit_count++;
  }

}

size_t Functor::_cube(int i) {
  size_t n;

  n = static_cast<size_t>(i);
  return n * n * n;
}

void Functor::_handle_cube(size_t cube) {
  size_t tmp;
  std::unordered_map<size_t, std::deque<size_t>>::iterator it;

  _make_ordered_digit_vector_of_cube(cube);
  tmp = _number_of_digit_vector();
  it = _cubes_grouped.find(tmp);
  if (it == _cubes_grouped.end()) {
    _cubes_grouped.emplace(tmp, std::deque<size_t>{cube});
  }
  else {
    it->second.push_back(cube);
    if (it->second.size() == 5) {
      std::cout << cube << " has " << it->second.size() << " permutations" << std::endl;
      std::cout << "    ";
      for (size_t c: it->second)
        std::cout << c << " ";
      std::cout << "" << std::endl;
      _found = true;
    }
  }
}

void Functor::_make_ordered_digit_vector_of_cube(size_t cube) {
  _digits.clear();
  while (cube != 0) {
    _digits.push_back(cube % 10);
    cube /= 10;
  }
  std::sort(_digits.begin(), _digits.end());
}

size_t Functor::_number_of_digit_vector() {
  size_t i, fact;

  i = 0;
  fact = 1;
  for (auto digit: _digits) {
    i += digit * fact;
    fact *= 10;
  }
  return i;
}
