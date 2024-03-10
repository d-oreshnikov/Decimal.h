#include "../my_decimal.h"

int my_from_decimal_to_int(my_decimal src, int *dst) {
  my_decimal trunc;
  int flag = my_truncate(src, &trunc);
  if (flag || trunc.bits[1] != 0 || trunc.bits[2] != 0)
    flag = CONVERTERROR;
  else {
    int res = trunc.bits[0];
    if (trunc.sign) res = -res;
    *dst = res;
    flag = CONVERTOK;
  }
  return flag;
}