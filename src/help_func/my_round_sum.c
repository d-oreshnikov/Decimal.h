#include "../my_decimal.h"

int my_round_sum(my_decimal value, my_decimal remainder,
                  my_decimal *result) {
  int sign = 0;
  OP_STATUS status = OP_OK;
  my_decimal half, tmp_result;
  my_set_zero(&half);
  half.bits[0] = (uint32_t)5;
  half.exp = value.exp + 1;
  sign = remainder.sign;
  remainder.sign = 0;
  if (my_is_less(half, remainder) ||
      (my_is_equal(half, remainder) && ((int)value.bits[0] % 2 != 0))) {
    int overflow = 0;
    my_decimal one;
    my_set_zero(&one);
    one.bits[0] = (uint32_t)1;
    if (sign == 0) {
      overflow = my_bits_add(value, one, &tmp_result);
      status = my_overflow(
          tmp_result, &tmp_result, &one,
          overflow);  // запись остатка в one не несёт смысловой нагрузки
    } else {
      my_bits_sub(value, one, &tmp_result);
    }
  } else {
    tmp_result = value;
  }
  if (status == OP_OK) {
    *result = tmp_result;
  }
  return status;
}