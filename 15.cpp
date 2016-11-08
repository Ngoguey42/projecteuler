

#include <iostream>

static size_t catalan_number(const size_t n) {
  double prod;
  double fact;

  // std::cout << "catalan_number " << n << std::endl;
  prod = 1.0;
  for (double i = 2.0; i <= n; i += 1.0) {
    fact = (n + i) / i;
    // std::cout << "for i=" << i << ": " << prod;
    prod *= fact;
    // std::cout << " * " << fact << " = " << prod << std::endl;
  }
  // std::cout << "res:" << prod << std::endl;
  return prod;
}

static size_t binomial_coef(double n, double k) {
  double prod;

  prod = 1.0;
  for (double i = 1.0; i <= k; i += 1.0) {
    prod *= (n + 1 - i) / i;
  }
  return prod;
}


int main() {
  size_t count;
  size_t count_below_diag;

  for (int i = 1; i < 21; i++) {
    count = binomial_coef(i * 2.0, i * 1.0);
    count_below_diag = catalan_number(i);
    std::cout
      << i << "x" << i << " "
      << count << " " << count_below_diag << " "
      << count / count_below_diag << std::endl;

  }
    // catalan_number(i);
  return 0;
}
