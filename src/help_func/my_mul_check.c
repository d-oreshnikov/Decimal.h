#include "../my_decimal.h"

int my_mul_check(uint32_t *mul) {
  int res = 0;
  for (int i = 3; i < 6; i++) {
    if (mul[i] != (uint32_t)0) {
      res = 1;
    }
  }
  return res;
}