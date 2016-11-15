// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   54.cpp                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/11/14 20:48:23 by ngoguey           #+#    #+#             //
//   Updated: 2016/11/15 15:30:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "54.hpp"

#include <forward_list>
#include <algorithm>
#include <set>
#include <functional>

int main() {
  using std::cin;

  std::array<char, 10> arr;
  std::pair<int, int> score{0, 0};
  std::pair<Hand, Hand> hands;

  auto next_hand = [&]{
    for (int i = 0; i < 10; i++) {
      cin >> arr[i];
      if (i % 2 == 1)
        cin.ignore();
    }
    return Hand{arr};
  };

  while (true) {
    hands.first = next_hand();
    hands.second = next_hand();
    if (cin.eof())
      break ;
    if (hands.first < hands.second) {
      score.second++;
      std::cout << "B wins" << std::endl;
    }
    else {
      score.first++;
      std::cout << "A wins" << std::endl;
    }
  }
  std::cout << score.first << std::endl;
  std::cout << score.second << std::endl;
  return 0;
}

Hand::Rank::Rank(Hand const &that) {
  _sorted_raw = that._cards;
  std::sort(_sorted_raw.begin(), _sorted_raw.end(), std::greater<int>{});
  _compute_distribution();
}

std::pair<int, std::array<Card, 5>> Hand::Rank::operator()() {
  const bool is_flush = _is_flush();
  const bool all_consecutive = _all_consecutive();
  const bool smallest_ten = _is_smallest_ten();

  if (is_flush && all_consecutive && smallest_ten)
    return {9, _sorted_raw};
  else if (is_flush && all_consecutive)
    return {8, _sorted_raw};
  else if (_distribution[4 - 1] == 1)
    return {7, _sorted_distribution};
  else if (_distribution[3 - 1] == 1 && _distribution[2 - 1] == 1)
    return {6, _sorted_distribution};
  else if (is_flush)
    return {5, _sorted_raw};
  else if (all_consecutive)
    return {4, _sorted_distribution};
  else if (_distribution[3 - 1] == 1)
    return {3, _sorted_distribution};
  else if (_distribution[2 - 1] == 2)
    return {2, _sorted_distribution};
  else if (_distribution[2 - 1] == 1)
    return {1, _sorted_distribution};
  else
    return {0, _sorted_raw};
}

template <typename T>
using rev_set_t = std::set<T, std::greater<T>>;

void Hand::Rank::_compute_distribution() {
  int begin, j;
  rev_set_t<std::forward_list<Card>> groups[4];

  auto tag_group = [&](int last){
    const int size = last - begin + 1;

    _distribution[size - 1]++;
    groups[size - 1].emplace(
      _sorted_raw.begin() + begin,
      _sorted_raw.begin() + begin + size);
    begin = last + 1;
  };

  _distribution = {0};
  begin = 0;
  for (int i = 1; i < 5; i++) {
    if (_sorted_raw[i - 1] == _sorted_raw[i])
      continue ;
    else
      tag_group(i - 1);
  }
  tag_group(4);

  j = 0;
  for (int i = 3; i >= 0; i--) {
    for (auto &card_list: groups[i]) {
      for (auto &card: card_list)
        _sorted_distribution[j++] = card;
    }
  }
}

bool Hand::Rank::_is_flush() {
  auto second = _sorted_raw.begin();

  ++second;
  return std::equal(
    second, _sorted_raw.end(), _sorted_raw.begin(),
    [](Card const &l, Card const &r) {
      return l.get_color() == r.get_color();
    }
  );
}

bool Hand::Rank::_all_consecutive() {
  return std::adjacent_find(
    _sorted_raw.begin(), _sorted_raw.end(),
    [](Card const &l, Card const &r) {
      return (l.get_value() - r.get_value()) != 1;
    }) == _sorted_raw.end();
}

bool Hand::Rank::_is_smallest_ten() {
  return _sorted_raw.rbegin()->get_value() == Value('T');
}
