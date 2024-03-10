#include "../my_decimal.h"

int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  OP_STATUS status = OP_OK;
  uint32_t sign = 0, init_exp = 0, exp = 0;
  my_decimal remainder;
  my_set_zero(&remainder);
  uint32_t *mul = NULL, *mul_normalized = NULL, *mul_compare = NULL,
           *mul_remainder = NULL;
  mul = (uint32_t *)malloc(6 * sizeof(uint32_t));
  mul_normalized = (uint32_t *)malloc(6 * sizeof(uint32_t));
  mul_compare = (uint32_t *)malloc(6 * sizeof(uint32_t));
  mul_remainder = (uint32_t *)malloc(6 * sizeof(uint32_t));
  my_mul_precise(value_1, value_2, &mul, &sign, &init_exp);
  exp = init_exp;
  status = my_mul_normalize(mul, &mul_normalized, &exp, sign);
  if (status == OP_OK) {
    my_uint32_array_mul_10(mul_normalized, &mul_compare, 6, init_exp - exp);
    my_uint32_array_sub(mul, mul_compare, &mul_remainder, 6);
    for (int i = 0; i < 3; i++) {
      result->bits[i] = mul_normalized[i];
      remainder.bits[i] = mul_remainder[i];
    }
    result->exp = exp;
    result->sign = sign;
    remainder.exp = init_exp;
    my_round_sum(*result, remainder, result);
    if (my_is_zero(*result)) {
      result->bits[3] = 0;
    }
  } else {
    my_set_zero(result);
  }
  free(mul);
  free(mul_normalized);
  free(mul_compare);
  free(mul_remainder);
  return status;
}
