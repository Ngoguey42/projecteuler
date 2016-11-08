
#include <iostream>
#include <cmath>

#define K 1000

static int int_sqrt_floor(int i) {
  return static_cast<int>(floor(sqrt(static_cast<double>(i))));
}

int b_of_a(int a) {
  return (a * K - K * K / 2) / (a - K);
}

int main() {

  int a, b, c_sq, c, sum_abc;

  a = 1;
  while (true) {
    b = b_of_a(a);
    c_sq = a * a + b * b;
    c = int_sqrt_floor(c_sq);
    sum_abc = a + b + c;
    if (c * c == c_sq && sum_abc == 1000) {
      std::cout << a << std::endl;
      std::cout << b << std::endl;
      std::cout << c << std::endl;
      std::cout << a + b + c << std::endl;
      std::cout << a * b * c << std::endl;
      std::cout << "" << std::endl;
    }
    if (a >= b)
      break ;
    a++;
  }
  return 0;
}

int main_old() {

  int a, b;
  int c_sq, c, sum_abc;

  a = 0;
  b = 500;
  while (true) {
    c_sq = a * a + b * b;
    c = int_sqrt_floor(c_sq);
    sum_abc = a + b + c;
    if (c * c == c_sq && sum_abc == 1000) {
      std::cout << a << std::endl;
      std::cout << b << std::endl;
      std::cout << c << std::endl;
      std::cout << a + b + c << std::endl;
      std::cout << a * b * c << std::endl;
      std::cout << "" << std::endl;
    }
    if (sum_abc < 1000)
      a++;
    else
      b--;
    if (a >= b)
      break ;
  }
  std::cout << "stop at:" << std::endl;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  return 0;
}
