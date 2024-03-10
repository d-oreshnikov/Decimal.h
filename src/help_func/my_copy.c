#include "../my_decimal.h"

void my_copy(my_decimal value, my_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = value.bits[i];
  }
}