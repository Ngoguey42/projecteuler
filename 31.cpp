
#include <iostream>
#include <vector>
#include <array>
#include <cassert>

// using values_t = std::array<int, 4>;
// const values_t decreasing_coins{10, 5, 2, 1};
// #define NDEBUG

using values_t = std::array<int, 8>;
const values_t decreasing_coins{200, 100, 50, 20, 10, 5, 2, 1};
const values_t increasing_coins{1, 2, 5, 10, 20, 50, 100, 200};

// V1 *********************************************************************** **
size_t profilerv1 = 0;

static size_t integer_partitions_v1(int i, int coin_index = 0) {
  profilerv1++;
  assert(i > 0);
  if (coin_index == decreasing_coins.size() - 1)
    return 1;
  else if (i < decreasing_coins[coin_index])
    return integer_partitions_v1(i, coin_index + 1);
  else if (i == decreasing_coins[coin_index])
    return 1 + integer_partitions_v1(i, coin_index + 1);
  else
    return integer_partitions_v1(i - decreasing_coins[coin_index], coin_index) +
      integer_partitions_v1(i, coin_index + 1);
}

// V2 *********************************************************************** **
static size_t integer_partitions_v2(int const price_aim) {
  std::vector<size_t> combinations_of_price;

  combinations_of_price.resize(price_aim + 1, 0);
  combinations_of_price[0] = 1;
  for (int coin_weigth: increasing_coins) {
    for (int price = coin_weigth; price <= price_aim; price++) {
      combinations_of_price[price] +=
        combinations_of_price[price - coin_weigth];
    }
  }
  return combinations_of_price[price_aim];
}

// MAIN ********************************************************************* **
int main() {

  // std::cout << integer_partitions_v1(10) << std::endl;
  // std::cout << integer_partitions_v1(1000) << std::endl;
  std::cout << integer_partitions_v2(200) << std::endl;
  std::cout << profilerv1 << std::endl;

  return 0;
}
