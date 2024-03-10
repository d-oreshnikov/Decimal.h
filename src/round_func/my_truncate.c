#include "../my_decimal.h"

int my_truncate(my_decimal value, my_decimal *result) {
  my_set_zero(result);
  int error_flag = CONVERTOK;
  if (value.exp > 28) {
    error_flag = CONVERTERROR;
  } else {
    my_bits_div_10(value, result, value.exp);
    result->sign = value.sign;
    result->exp = 0;
  }
  return error_flag;
}
