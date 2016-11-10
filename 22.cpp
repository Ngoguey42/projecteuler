
#include <iostream>
#include <cstring>
#include <algorithm>

char const *names[] {
#include "p022_names.txt"
};


bool cstringcmp(char const *a, char const *b) {
  return std::strcmp(a, b) < 0;
}

int main() {
  size_t acc;
  size_t wscore;
  size_t ordinal;

  std::sort(std::begin(names), std::end(names), cstringcmp);
  acc = 0;
  ordinal = 1;
  for (char const *name: names) {
    wscore = 0;
    while (*name != '\0') {
      wscore += *name - 'A' + 1;
      name++;
    }
    acc += wscore * ordinal;
    ordinal++;
  }
  std::cout << acc << std::endl;
  return 0;
}
