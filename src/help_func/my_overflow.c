#include "../my_decimal.h"

int my_overflow(my_decimal value, my_decimal *result, my_decimal *remainder,
                 int overflow_flag) {
  OP_STATUS status = OP_OK;
  if (overflow_flag) {
    if (value.exp > 0) {
      my_decimal overflow, overflow_remainder, remainder_sum;
      overflow.bits[0] = 2576980376;  // 2^96 / 10
      overflow.bits[1] = 2576980377;
      overflow.bits[2] = 429496729;
      my_set_zero(&overflow_remainder);
      overflow_remainder.bits[0] = 6;  // 2^96 % 10
      // value сдвигается на один десятичный разряд вправо, остаток - в
      // remainder_sum value суммируется с overflow, остатки (value_2 и от
      // переполнения) - между собой
      my_decrease_exp(value, &value, &remainder_sum, 1);
      my_bits_add(remainder_sum, overflow_remainder, &remainder_sum);
      my_bits_add(value, overflow, &value);
      // из остатка выделяется значимая часть и суммируется с value
      my_decrease_exp(remainder_sum, &overflow, &overflow_remainder, 1);
      my_bits_add(value, overflow, &value);
      overflow_remainder.sign = value.sign;
      overflow_remainder.exp = value.exp;
      *result = value;
      *remainder = overflow_remainder;
    } else {
      my_set_zero(result);
      my_set_zero(remainder);
      status = (value.sign == 0) ? OP_LARGE : OP_SMALL;
    }
  } else {
    *result = value;
    my_set_zero(remainder);
  }
  return status;
}