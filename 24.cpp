

// #include <unordered_set>
#include <iostream>
#include <cassert>

// V1 *********************************************************************** **

// (nbr) should have 9 or 10 digits
static bool has_all_digits(size_t nbr) {
  bool has[10]{false};
  int count;
  size_t i, tmp;

  count = 0;
  i = nbr;
  while (i > 0) {
    tmp = i % 10;
    if (has[tmp])
      return false;
    has[tmp] = true;
    i /= 10;
    count++;
  }
  if (count == 10 || has[0] == false)
    return true;
  else
    return false;
}

static size_t v1() { //  25.590s total (-Ofast)
  int count;

  count = 0;
  for (size_t i = 123456789; i < 9876543210; i++) {
    if (has_all_digits(i)) {
      count++;
      if (count >  362850 * 2)
        std::cout << count << ": " << i << std::endl;
      if (count == 362900 * 2)
        return i;
    }
  }
  assert(false);
  return 0;
}

// V2 *********************************************************************** **
static size_t factorial(int nbr) {
  int prod;

  prod = 1;
  for (int i = 2; i <= nbr; i++)
    prod *= i;
  return prod;
}

void dump(int (&dig)[10]){
  std::cout << "index:" << "0123456789" << std::endl;
  std::cout << "mine: ";
  for (int d: dig)
    std::cout << d;
  std::cout << std::endl;
  std::cout << "ref:  " << 2783915460 << std::endl;
};


static void shift_rotate_right(int (&digits)[10], int left, int right) {
  const int rdigit = digits[right];

  for (int i = right; i > left; i--) {
    digits[i] = digits[i - 1];
  }
  digits[left] = rdigit;
}

static void perform_swap(int (&digits)[10], int const count, int const index) {
  const int fact_index = factorial(9 - index);
  const int i = (count - 1) / fact_index;
  const int num_swaps = i * fact_index;

  std::cout
    << "at index " << index
    << ": " << num_swaps << " swaps(" << i << ")" << std::endl;
  shift_rotate_right(digits, index, index + i);
  if (count - num_swaps > 1)
    perform_swap(digits, count - num_swaps, index + 1);
  return ;
}

static size_t v2() {
  int digits[10] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
  };

  perform_swap(digits, 10, 0);
  // perform_swap(digits, 3628800 - 1, 0);
  dump(digits);
  return 0;
}

// MAIN ********************************************************************* **
int main() {
  // std::cout << v1() << std::endl;
  v2();
  return 0;
}
