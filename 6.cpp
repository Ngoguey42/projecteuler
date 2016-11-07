
#include <iostream>

#define MAX 100

int main() {
  int sum, sum_sq;

  sum = (MAX + 1) * MAX / 2;
  sum_sq = MAX * (MAX + 1) * (MAX * 2 + 1) / 6;
  std::cout << sum * sum << std::endl;
  std::cout << sum_sq << std::endl;
  std::cout << sum * sum - sum_sq << std::endl;

  return 0;
}
