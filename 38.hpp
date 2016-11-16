// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   38.hpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/16 18:11:02 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/16 18:41:34 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <array>

class DigitIterator {

  size_t _nbr;

public:
  ~DigitIterator() = default;
  DigitIterator();
  DigitIterator(size_t nbr);
  DigitIterator(DigitIterator const &) = default;
  DigitIterator &operator =(DigitIterator const &) = default;

  size_t operator*() const;
  void operator++();
  bool done() const;

};

class Functor {

  std::array<bool, 10> _digit_sieve;
  size_t _digit_count;

  void _reset_digit_sieve();
  bool _handle_number(size_t const nbr);
  size_t _rebuild_concatenation(size_t nbr);

public:
  void operator()();

};
