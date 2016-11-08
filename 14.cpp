
#include <vector>
#include <stack>
#include <iostream>

class LongestChain {

  size_t _max;
  size_t _longest;
  size_t _longest_start;
  std::vector<size_t> _lengths;
  std::stack<size_t> pile;
  // std::stack<size_t, std::vector<size_t>> pile;

  size_t _next(size_t n) {
    if (n % 2 == 0)
      return n / 2;
    else
      return 3 * n + 1;
  }

  void _compute_chain_from(size_t target) {
    size_t i;
    size_t len;

    // std::cout << "_compute_chain_from " << target << std::endl;
    i = target;
    while (i != 1 && (i > _max || _lengths[i] == 0)) {
      pile.push(i);
      i = _next(i);
    }
    len = _lengths[i];
    while (!pile.empty()) {
      ++len;
      if (pile.top() <= _max)
        _lengths[pile.top()] = len;
      pile.pop();
    }
    if (len > _longest) {
      _longest = len;
      _longest_start = target;
    }
  }

  size_t _chain_length(size_t n) {
    size_t len;

    if (n == 1)
      return 0;
    else if (n > _max)
      return _chain_length(_next(n)) + 1;
    else if (_lengths[n] != 0)
      return _lengths[n];
    else {
      len = _chain_length(_next(n)) + 1;
      _lengths[n] = len;
      return len;
    }
  }

public:

  size_t operator()(size_t max) {
    size_t len;

    _max = max - 1;
    _longest = 0;
    _lengths.clear();
    _lengths.resize(max, 0);


    for (size_t i = 1; i < max; i++) {

      // V1 ***************************************************************** **
      // _compute_chain_from(i);

      // V2 ***************************************************************** **
      len = _chain_length(i);
      if (len > _longest) {
        _longest = len;
        _longest_start = i;
      }
    }
    // for (auto i : _lengths)
    // std::cout << "'" << i << std::endl;
    std::cout << _longest << std::endl;
    std::cout << _longest_start << std::endl;
    return _longest_start;
  }

};

int main() {
  LongestChain functor;

  functor(5000000);
}
