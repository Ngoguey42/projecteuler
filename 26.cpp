
#include <iostream>
#include <unordered_map>

// A unit fraction contains 1 in the numerator.
int unit_fraction_cycle_length(int denominator) {
  std::unordered_map<int, int> index_of_remainder;
  std::unordered_map<int, int>::const_iterator it;
  int remainder;
  int index;

  remainder = 1;
  index = 0;
  while (remainder > 0) {
    remainder %= denominator;
    it = index_of_remainder.find(remainder);
    if (it != index_of_remainder.end())
      return index - it->second;
    index_of_remainder.emplace(remainder, index);
    index++;
    remainder *= 10;
  }
  return 0;
}

int main() {
  int max, i_max, tmp;

  max = 0;
  i_max = 0;
  for (int i = 1; i < 1000; i++) {
    tmp = unit_fraction_cycle_length(i);
    if (tmp > max) {
      std::cout << i << ": " << tmp << std::endl;
      max = tmp;
      i_max = i;
    }
  }
  std::cout << max << std::endl;
  std::cout << i_max << std::endl;
  return 0;
}
