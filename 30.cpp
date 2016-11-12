
#include <iostream>

static int power(int b, int e) {
  int prod;

  prod = 1;
  for (int i = 0; i < e; i++)
    prod *= b;
  return prod;
}

static int weigth(int i, int num_digit) {
  int w;

  w = 0;
  for (int j = 0; j < num_digit; j++) {
    w += power(i % 10, 5);
    i /= 10;
  }
  return w;
}

int main() {
  const int max_digit_weigth = power(9, 5);
  int num_digit, max_weigth, min_weigth, tmp;

  num_digit = 2;
  while (true) {
    max_weigth = max_digit_weigth * num_digit;
    min_weigth = power(10, num_digit - 1);
    if (max_weigth < min_weigth)
      break ;
    max_weigth = std::min(max_weigth, power(10, num_digit) - 1);
    std::cout
      << "num_digit(" << num_digit << ") "
      << "max_weigth(" << max_weigth << ") "
      << std::endl;
    for (int i = min_weigth; i <= max_weigth; i++) {
      tmp = weigth(i, num_digit);
      if (tmp == i)
        std::cout << i << std::endl;
    }
    num_digit++;
  }
  return 0;
}
