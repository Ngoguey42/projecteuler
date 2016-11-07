
#include <iostream>

int main() {

  int acc, lo, gr, tmp;

  lo = 1;
  gr = 2;
  acc = 0;
  while (gr < 4000000) {
    if (gr % 2 == 0)
      acc += gr;
    tmp = gr;
    gr += lo;
    lo = tmp;
  }
  std::cout << acc << std::endl;

}
