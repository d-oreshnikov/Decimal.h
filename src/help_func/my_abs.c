#include "../my_decimal.h"

void my_abs(my_decimal value, my_decimal *dst) {
  if (value.sign == 1) {
    my_negate(value, dst);
  } else {
    *dst = value;
  }
}