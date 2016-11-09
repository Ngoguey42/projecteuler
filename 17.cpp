// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   17.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/09 15:26:56 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/09 16:40:58 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <cassert>
#include <cctype>

static char const *const _small_units[] = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
  "ten",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eighteen",
  "nineteen",
};

static  char const *_tenth_units[] = {
  "ERROR",
  "ERROR",
  "twenty",
  "thirty",
  "forty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety",
};

static  char const *_3block_units[] = {
  "",
  " thousand",
  " million",
  " billion",
};

class NumberToEnglish {

  std::list<char const*> _create_block2(unsigned int i);
  std::list<char const*> _create_block3(unsigned int i);
  std::list<char const*> _create(unsigned int i);

public:
  std::string operator()(unsigned int i);

};

std::list<char const*> NumberToEnglish::_create_block2(unsigned int i) {
  assert(i < 100);
  if (i == 0)
    return {};
  else if (i < 20)
    return {{_small_units[i]}};
  else if (i % 10 == 0)
    return {{_tenth_units[i / 10]}};
  else
    return {{_tenth_units[i / 10], "-", _small_units[i % 10]}};
}

std::list<char const*> NumberToEnglish::_create_block3(unsigned int i) {
  std::list<char const*> elts;

  assert(i < 1000);
  elts = _create_block2(i % 100);
  if (i / 100 != 0) {
    if (elts.empty()) {
      elts.push_back(_small_units[i / 100]);
      elts.push_back(" hundred");
    }
    else {
      elts.push_front(" hundred and ");
      elts.push_front(_small_units[i / 100]);
    }
  }
  return elts;
}

std::list<char const*> NumberToEnglish::_create(unsigned int i) {
  std::list<char const*> elts, tmp;
  int block3_index;

  block3_index = 0;
  while (i != 0) {
    tmp = _create_block3(i % 1000);
    i /= 1000;
    if (!tmp.empty()) {
      tmp.push_back(_3block_units[block3_index]);
      elts.splice(elts.cbegin(), std::move(tmp));
      if (i != 0)
        elts.push_front(" ");
    }
    block3_index++;
  }
  return elts;
}

std::string NumberToEnglish::operator()(unsigned int i) {
  std::list<char const*> parts;
  std::ostringstream oss;

  parts = _create(i);
  if (parts.empty())
    return "zero";
  for (char const *str: parts)
    oss << str;
  return oss.str();
}

int alpha_char_count_of_string(std::string const &str) {
  int acc;

  acc = 0;
  for (char c: str) {
    if (std::isalpha(c))
      acc++;
  }
  return acc;
}

int main() {

  NumberToEnglish f;
  int acc;

  acc = 0;
  for (size_t i = 1; i <= 1000; i++) {
    acc += alpha_char_count_of_string(f(i));
  }
  std::cout << acc << std::endl;

  const auto test = [&](unsigned int i) {
    std::cout << i << " '" << f(i) << "'" << std::endl;
  };

  test(0);
  test(10);
  test(42);
  test(444);
  test(555000);
  test(555444);
  test(666000000);
  test(666000444);
  test(666555000);
  test(666555444);
  test(1000000000);
  test(1001001001);
}
