#include "../my_decimal.h"

int my_bits_equal(my_decimal value_1, my_decimal value_2) {
  int result = 1;
  for (int i = 2; i >= 0; i--) {
    if (value_1.bits[i] != value_2.bits[i]) {
      result = 0;
    }
  }
  return result;
}