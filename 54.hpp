// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   54.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/14 20:48:25 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/15 15:41:33 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _54_HPP
# define _54_HPP

# include <cassert>
# include <array>
# include <unordered_map>
# include <tuple>
# include <iostream>

// VALUE ******************************************************************** **
class Value {

  enum class _v_t {
    _2, _3, _4, _5, _6, _7, _8, _9, _10, jack, queen, king, ace,
  };

  _v_t _v;

public:
  Value()
    : _v(_v_t::_2) {
  }

  Value(char c) {
    switch (c) {
    case ('2'): _v = _v_t::_2; break ;
    case ('3'): _v = _v_t::_3; break ;
    case ('4'): _v = _v_t::_4; break ;
    case ('5'): _v = _v_t::_5; break ;
    case ('6'): _v = _v_t::_6; break ;
    case ('7'): _v = _v_t::_7; break ;
    case ('8'): _v = _v_t::_8; break ;
    case ('9'): _v = _v_t::_9; break ;
    case ('T'): _v = _v_t::_10; break ;
    case ('J'): _v = _v_t::jack; break ;
    case ('Q'): _v = _v_t::queen; break ;
    case ('K'): _v = _v_t::king; break ;
    case ('A'): _v = _v_t::ace; break ;
    default: assert(false);
    }
  }

  ~Value() = default;
  Value(Value const &) = default;
  Value &operator =(Value const &) = default;
  bool operator ==(Value const &rhs) const {
    return _v == rhs._v;
  }

  bool operator <(Value const &rhs) const {
    return _v < rhs._v;
  }

  operator int() const {
    return static_cast<int>(_v);
  }

  int operator -(Value const &rhs) const {
    return static_cast<int>(_v) - static_cast<int>(rhs._v);
  }

  friend std::ostream &operator <<(std::ostream &o, Value const &that);

};

std::ostream &operator <<(std::ostream &o, Value const &that) {
  switch (that._v) {
  case (Value::_v_t::_2): o << '2'; break;
  case (Value::_v_t::_3): o << '3'; break;
  case (Value::_v_t::_4): o << '4'; break;
  case (Value::_v_t::_5): o << '5'; break;
  case (Value::_v_t::_6): o << '6'; break;
  case (Value::_v_t::_7): o << '7'; break;
  case (Value::_v_t::_8): o << '8'; break;
  case (Value::_v_t::_9): o << '9'; break;
  case (Value::_v_t::_10): o << 'T'; break;
  case (Value::_v_t::jack): o << 'J'; break;
  case (Value::_v_t::queen): o << 'Q'; break;
  case (Value::_v_t::king): o << 'K'; break;
  case (Value::_v_t::ace): o << 'A'; break;
  }
  return o;
}

// COLOR ******************************************************************** **
class Color {

  enum class _c_t {
    _club, _heart, _spades, _diamond,
  };

  _c_t _c;

public:
  Color()
    : _c(_c_t::_club) {
  }

  Color(char c) {
    switch (c) {
    case ('C'): _c = _c_t::_club; break ;
    case ('H'): _c = _c_t::_heart; break ;
    case ('S'): _c = _c_t::_spades; break ;
    case ('D'): _c = _c_t::_diamond; break ;
    default: assert(false);
    }
  }

  ~Color() = default;
  Color(Color const &) = default;
  Color &operator =(Color const &) = default;

  bool operator ==(Color const &rhs) const {
    return _c == rhs._c;
  }

  friend std::ostream &operator <<(std::ostream &o, Color const &that);

};

std::ostream &operator <<(std::ostream &o, Color const &that) {
  switch (that._c) {
  case (Color::_c_t::_club): o << 'C'; break;
  case (Color::_c_t::_heart): o << 'H'; break;
  case (Color::_c_t::_spades): o << 'S'; break;
  case (Color::_c_t::_diamond): o << 'D'; break;
  }
  return o;
}

// CARD ********************************************************************* **
class Card {

  Value _v;
  Color _c;

public:
  Card()
    : _v()
    , _c() {
  }

  Card(char v, char c)
    : _v(v)
    , _c(c) {
  }

  ~Card() = default;
  Card(Card const &) = default;
  Card &operator =(Card const &) = default;
  bool operator ==(Card const &rhs) const {
    return _v == rhs._v;
  }

  bool operator <(Card const &rhs) const {
    return _v < rhs._v;
  }

  operator int() const {
    return static_cast<int>(_v);
  }

  Color const &get_color() const {
    return _c;
  }

  Value const &get_value() const {
    return _v;
  }

  friend std::ostream &operator <<(std::ostream &o, Card const &that);

};

std::ostream &operator <<(std::ostream &o, Card const &that) {
  o << that._v;
  o << that._c;
  return o;
}

std::ostream &operator <<(std::ostream &o, std::array<Card, 5> const &that) {
  o << that[0];
  for (int i = 1; i < 5; i++) {
    o << " " << that[i];
  }
  return o;
}

// HAND AND RANKING ********************************************************* **
class Hand {

  std::array<Card, 5> _cards;

  class Rank {

    std::array<Card, 5> _sorted_raw;
    std::array<int, 4> _distribution;
    std::array<Card, 5> _sorted_distribution;

    bool _is_flush();
    bool _all_consecutive();
    bool _is_smallest_ten();

    void _compute_distribution();

  public:
    Rank(Hand const &that);
    std::pair<int, std::array<Card, 5>> operator()();

  };

public:
  Hand(std::array<char, 10> const &arr) {
    for (int i = 0; i < 5; i++) {
      _cards[i] = Card(arr[i * 2], arr[i * 2 + 1]);
    }
  }

  Hand() = default;
  ~Hand() = default;
  Hand(Hand const &) = default;
  Hand &operator =(Hand const &) = default;

  bool operator <(Hand const &rhs) const {
    auto r1 = Rank{*this}();
    std::cout << r1.first << " " << r1.second << std::endl;
    auto r2 = Rank{rhs}();
    std::cout << r2.first << " " << r2.second << std::endl;

    return r1 < r2;
  }

  friend std::ostream &operator <<(std::ostream &o, Hand const &that);

};

std::ostream &operator <<(std::ostream &o, Hand const &that) {
  o << that._cards;
  return o;
}

#endif
