#include "../my_decimal.h"

int my_negate(my_decimal value, my_decimal *result) {
  bool sign = value.sign;
  value.sign = sign ? 0 : 1;
  *result = value;
  return 0;
}
