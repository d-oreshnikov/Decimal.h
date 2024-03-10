#include "../my_decimal.h"

void my_set_zero(my_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
}