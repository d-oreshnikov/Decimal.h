#include "../my_decimal.h"

int my_normalize(my_decimal value, my_decimal *result) {
  // убирает незначащие конечные нули (за счёт понижения exp)
  // отсекает разряды младше 10^(-28)
  int is_normalized = 0;
  int err_flag = CONVERTOK;
  if (value.exp == 0) {
    is_normalized = 1;
    *result = value;
  } else if (value.exp > 28) {
    err_flag = CONVERTERROR;
    // } else if (value.exp > 28) {
    //   my_decimal zero;
    //   my_set_zero(&zero);
    //   my_bits_div_10(value, &value, value.exp - 28);
    //   value.exp = 28;
    //   if (my_is_equal(value, zero)) {
    //     err_flag = CONVERTERROR;
    //   }
  }
  if (err_flag == CONVERTOK && is_normalized == 0) {
    uint32_t new_exp = 0;
    new_exp = value.exp;
    while (new_exp > 0 && is_normalized == 0) {
      my_decimal value_round;
      my_set_zero(&value_round);
      my_bits_div_10(value, &value_round, 1);
      my_bits_mul_10(value_round, &value_round, 1);
      if (my_bits_equal(value_round, value)) {
        new_exp -= 1;
      } else {
        my_bits_div_10(value, result, value.exp - new_exp);
        result->sign = value.sign;
        result->exp = new_exp;
        is_normalized = 1;
      }
    }
  }
  return err_flag;
}