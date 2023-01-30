#include <iostream>

auto main() -> int {
  int intValue1 = 15;
  int intValue2 = 24;
  auto intIntSum = intValue1 + intValue2;

  long longValue1 = 11l;
  auto longIntSum = longValue1 + intValue1;

  double doubleValue = 128.0;
  auto doubleIntSum = doubleValue + intValue1;

  unsigned unsignedValue = 99u;
  auto unsignedIntSum = unsignedValue + intValue1;

  int negativeInt = -50;

  std::cout << "intValue1 " << intValue1 << '\n';
  std::cout << "unsignedIntSum " << unsignedIntSum << '\n';
  if (intValue1 < -unsignedIntSum) {
    std::cout << "intValue1 < -unsignedIntSum\n";
    //		std::cout << "-unsignedIntSum " << -unsignedIntSum << '\n';
  }

  std::cout << "--- loop ---\n";
  int zeroIndex = 0;
  for (unsigned size = 5; size <= 10; size--) {
    if (zeroIndex <= size - 1) {
      std::cout << "access with 0 is ok for size " << size << '\n';
    } else {
      std::cout << "access with 0 is not ok for size " << size << '\n';
    }
  }
}
