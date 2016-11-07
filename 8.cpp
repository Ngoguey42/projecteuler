
#include <cassert>
#include <iostream>
#include <limits>
#include <cmath>

char const series[] = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";

#define SEQ_LEN 13
#define SERIES_LEN (static_cast<int>(sizeof(series) / sizeof(*series)) - 1)
#define SEQ_MAX_PROD_FP pow(9.0, static_cast<double>(SEQ_LEN))
#define PROD_MAX_VALUE_FP static_cast<double>(std::numeric_limits<size_t>::max())

int profiler = 0;
int profiler_op = 0;

size_t prod_of_first_digit_index(int first) {
  size_t prod;

  prod = 1;
  for (int i = 0; i < SEQ_LEN; i++) {
    profiler_op++;
    prod *= series[i + first] - '0';
  }
  return prod;
}

size_t maxprod() {

  int head_index, tail_index;
  size_t prod, max_prod;
  size_t prev_head_digit, tail_digit;

  head_index = 1;
  tail_index = SEQ_LEN;

  prod = prod_of_first_digit_index(0);
  max_prod = prod;
  while (tail_index < SERIES_LEN) {
    profiler++;
    prev_head_digit = series[head_index - 1] - '0';
    tail_digit = series[tail_index] - '0';

    if (tail_digit == 0) {
      head_index += SEQ_LEN - 1;
      tail_index += SEQ_LEN - 1;
    }
    else {
      if (prev_head_digit == 0)
        prod = prod_of_first_digit_index(head_index);
      else {
        profiler_op++;
        profiler_op++;
        prod /= prev_head_digit;
        prod *= tail_digit;
      }
      if (prod > max_prod) {
        max_prod = prod;
        std::cout
          << "new max: " << prod
          << " at " << std::string{series + head_index, SEQ_LEN} << std::endl;
      }
      head_index++;
      tail_index++;
    }
  }
  return max_prod;
}

int main() {
  if (SEQ_LEN > SERIES_LEN) {
    std::cerr << "too long 0" << std::endl;
    return 1;
  }
  if (SEQ_MAX_PROD_FP > PROD_MAX_VALUE_FP) {
    std::cerr << "too long 1" << std::endl;
    return 1;
  }
  std::cout << maxprod() << std::endl;
  std::cout << "profiler:" << profiler << std::endl;
  std::cout << "profiler_op:" << profiler_op << std::endl;
  return 0;
}
