#include "../my_decimal.h"

int my_is_zero(my_decimal value) {
  int result = 1;
  for (int i = 0; i < 3; i++) {
    if (value.bits[i] != (uint32_t)0) {
      result = 0;
    }
  }
  return result;
}