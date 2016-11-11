

#include <iostream>

int main() {
  int acc;
  int side;
  int left;

  left = 1;
  acc = 1;
  for (int side = 1; side <= 1001; side += 2) {
    std::cout
      << "side(" << side << ") "
      << "left(" << left << ") "
      << "acc(" << acc << ") "
      << std::endl;
    // left += (side / 2) + side - 1 + (side + 2) - 1 + (side + 2) - 1 + (side + 2) / 2;
    // left += (side / 2) * 2 + 1 + side - 1 + (side + 2) - 1 + (side + 2) - 1;
    // left += (side / 2) * 2 + 1 + side * 3 - 1 + 2 - 1 + 2 - 1;
    // left += (side / 2) * 2 + side * 3 + 2;
    // left += 4 * side - side % 2 + 2;
    left += 4 * side + 1;
    acc += left * 4;
  }
  return 0;
}
