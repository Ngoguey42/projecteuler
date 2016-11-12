
#include <array>
#include <iostream>

constexpr unsigned int factorial(unsigned int d, unsigned int fact = 1) {
  return d == 0 ? fact : factorial(d - 1, fact * d);
}

unsigned int power(unsigned int b, unsigned int p) {
  unsigned int fact;

  fact = 1;
  for (unsigned int i = 0; i < p; i++)
    fact *= b;
  return fact;
}



constexpr unsigned int digits_fact[10] = {
  factorial(0),
  factorial(1),
  factorial(2),
  factorial(3),
  factorial(4),
  factorial(5),
  factorial(6),
  factorial(7),
  factorial(8),
  factorial(9),
};

int main() {
  int j;
  int acc;
  int digit_count, min_value, max_value;


  digit_count = 2;
  while (true) {
    min_value = power(10, digit_count - 1);
    max_value = std::min(power(10, digit_count) - 1,
                         digit_count * digits_fact[9]);
    std::cout << digit_count << " digits ["
              << min_value << ", "
              << max_value << "]" << std::endl;

    if (max_value < min_value)
      break ;

    for (int i = min_value; i <= max_value; i++) {
      j = i;
      acc = 0;
      while (j != 0) {
        acc += digits_fact[j % 10];
        j /= 10;
      }
      if (acc == i) {
        std::cout << i << std::endl;
      }
    }
    digit_count++;
  }
  return 0;
}
