#include "../my_decimal.h"

int my_from_int_to_decimal(int src, my_decimal *dst) {
  int flag = CONVERTOK;
  if (dst == NULL)
    flag = CONVERTERROR;
  else {
    my_set_zero(dst);
    if (src < 0) {
      src = -src;
      dst->sign = 1;
    }
    dst->bits[0] = src;
  }
  return flag;
}
