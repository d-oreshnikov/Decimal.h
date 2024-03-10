#include "../my_decimal.h"

int my_sum(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  OP_STATUS status = OP_OK;
  int overflow = 0, delta_exp = 0;
  my_decimal remainder, overflow_remainder;
  my_decimal tmp_result;
  my_set_zero(&remainder);
  my_set_zero(&overflow_remainder);
  my_set_zero(&tmp_result);
  if (my_normalize(value_1, &value_1) || my_normalize(value_2, &value_2)) {
    status = OP_SMALL;
  } else {
    if (my_is_abs_less(value_1, value_2)) {
      my_swap(&value_1, &value_2);
    }
    my_equate_exp(value_1, value_2, &value_1, &value_2, &remainder,
                   &delta_exp);
    if (value_1.sign == value_2.sign) {
      overflow = my_bits_add(value_1, value_2, &tmp_result);
      status =
          my_overflow(tmp_result, &tmp_result, &overflow_remainder, overflow);
      if (overflow == 1 && status == OP_OK) {
        my_bits_mul_10(overflow_remainder, &overflow_remainder, delta_exp);
        my_bits_add(remainder, overflow_remainder, &remainder);
        my_decrease_exp(remainder, &overflow_remainder, &remainder,
                         delta_exp + overflow);
        my_bits_add(tmp_result, overflow_remainder, &tmp_result);
        remainder.sign = 0;
      }
    } else {
      my_bits_sub(value_1, value_2, &tmp_result);
      remainder.sign =
          1;  // если sign == 1, при округлении вверх модуль числа уменьшается
    }
    if (status == OP_OK) {
      status = my_round_sum(tmp_result, remainder, &tmp_result);
    }
  }
  if (status == OP_OK) {
    *result = tmp_result;
    result->sign = value_1.sign;
  } else {
    my_set_zero(result);
  }
  return status;
}
