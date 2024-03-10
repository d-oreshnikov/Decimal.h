#include "../my_decimal.h"

void my_decrease_exp(my_decimal value, my_decimal *rounded,
                      my_decimal *remainder, uint32_t delta_exp) {
  my_decimal tmp;
  my_set_zero(rounded);
  my_set_zero(remainder);
  my_set_zero(&tmp);

  my_bits_div_10(value, rounded, delta_exp);
  rounded->exp = value.exp - delta_exp;
  rounded->sign = value.sign;

  my_bits_mul_10(*rounded, &tmp, delta_exp);
  my_bits_sub(value, tmp, remainder);
  remainder->exp = value.exp;
}
