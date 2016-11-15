// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   61.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/15 20:20:29 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/15 21:44:41 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _61_HPP
# define _61_HPP

# include <cstdint>
# include <cassert>
# include <unordered_set>
# include <list>
# include <functional>

class Number {

  uint16_t _n;
  uint8_t _head;
  uint8_t _tail;

public:
  Number()
    : _n(0)
    , _head(0)
    , _tail(0) {
  }

  Number(int n)
    : _n(static_cast<uint16_t>(n))
    , _head(static_cast<uint16_t>(n / 100))
    , _tail(static_cast<uint16_t>(n % 100)) {
    assert(n > 999 && n < 10000);
  }
  Number(uint8_t head)
    : _n(static_cast<uint16_t>(head))
    , _head(head)
    , _tail(0) {
    assert(head < 100);
  }

  ~Number() = default;
  Number(Number const &) = default;
  Number &operator =(Number const &) = default;

  inline uint16_t get_number() const {
    return _n;
  }

  inline uint8_t get_head() const {
    return _head;
  }

  inline uint8_t get_tail() const {
    return _tail;
  }

  struct Hash {

    size_t operator()(Number const &n) const {
      return static_cast<size_t>(n._head);
    }

  };

  bool operator ==(Number const &rhs) const {
    return _head == rhs._head;
  }

};

class Functor {

  uint8_t _first_head;

  using group_t = std::unordered_multiset<Number, Number::Hash>;

  std::unordered_set<uint16_t> _taken_numbers;
  std::list<group_t> _available_groups;

  void _generate_group(std::function<int(int)> const &f);
  void _pick_any_group(uint8_t prev_tail = -1);
  void _pick_any_number(uint8_t prev_tail, group_t const &g);
  void _report_success();

public:

  void operator()();

};

#endif
