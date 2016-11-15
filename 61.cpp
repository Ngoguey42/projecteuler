// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   61.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/15 20:20:30 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/15 21:45:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "61.hpp"

#include <iostream>

int main() {
  Functor{}();
  return 0;
}

void Functor::operator ()() {
  _generate_group([](int n){ return n * (n + 1) / 2; });
  _generate_group([](int n){ return n * n; });
  _generate_group([](int n){ return n * (3 * n - 1) / 2; });
  _generate_group([](int n){ return n * (2 * n - 1); });
  _generate_group([](int n){ return n * (5 * n - 3) / 2; });
  _generate_group([](int n){ return n * (3 * n - 2); });
  _pick_any_group();
}

void Functor::_generate_group(std::function<int(int)> const &f) {
  group_t g;
  int i, tmp;

  i = 0;
  while (true) {
    tmp = f(i);
    if (tmp >= 10000)
      break ;
    else if (tmp >= 1000)
      g.insert(tmp);
    i++;
  }
  _available_groups.push_back(g);
}

void Functor::_pick_any_group(uint8_t prev_tail /*= -1*/) {
  std::list<group_t>::iterator it, next;
  std::list<group_t> g;

  it = _available_groups.begin();
  while (it != _available_groups.end()) {
    next = it;
    ++next;
    g.splice(g.begin(), _available_groups, it);
    _pick_any_number(prev_tail, *g.begin());
    _available_groups.splice(next, g, g.begin());
    it = next;
  }
}


void Functor::_pick_any_number(uint8_t prev_tail, group_t const &g) {
  group_t::const_iterator it, end;

  if (_taken_numbers.empty()) {
    for (Number const &n: g) {
      _taken_numbers.insert(n.get_number());
      _first_head = n.get_head();
      _pick_any_group(n.get_tail());
      _taken_numbers.erase(n.get_number());
    }
  }
  else if (_available_groups.empty()) {
    std::tie(it, end) = g.equal_range(Number(prev_tail));
    while (it != end) {
      if (it->get_tail() == _first_head &&
          _taken_numbers.count(it->get_number()) == 0) {
        _taken_numbers.insert(it->get_number());
        _report_success();
        _taken_numbers.erase(it->get_number());
      }
      ++it;
    }
  }
  else {
    std::tie(it, end) = g.equal_range(Number(prev_tail));
    while (it != end) {
      if (_taken_numbers.count(it->get_number()) == 0) {
        _taken_numbers.insert(it->get_number());
        _pick_any_group(it->get_tail());
        _taken_numbers.erase(it->get_number());
      }
      ++it;
    }
  }
}

void Functor::_report_success() {
  int acc;

  acc = 0;
  for (int i: _taken_numbers) {
    std::cout << i << " ";
    acc += i;
  }
  std::cout << " = " << acc << std::endl;
}
