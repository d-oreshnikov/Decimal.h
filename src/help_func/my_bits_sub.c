#include "../my_decimal.h"

void my_bits_sub(my_decimal value_1, my_decimal value_2,
                  my_decimal *result) {
  // целочисленные части вычитаются, знак и показатель берутся из первого
  // аргумента
  my_set_zero(result);
  uint32_t *res_bits = NULL;
  res_bits = (uint32_t *)malloc(3 * sizeof(uint32_t));
  my_uint32_array_sub(value_1.bits, value_2.bits, &res_bits, 3);
  for (int i = 0; i < 3; i++) {
    result->bits[i] = res_bits[i];
  }
  result->exp = value_1.exp;
  result->sign = value_1.sign;
  free(res_bits);
}