#include "../my_decimal.h"

int my_bits_add(my_decimal value_1, my_decimal value_2,
                 my_decimal *result) {
  // целочисленные части складываются, знак и показатель берутся из первого
  // аргумента
  int overflow_flag = 0;
  uint64_t sum = 0;
  my_decimal tmp_result;
  my_set_zero(&tmp_result);
  for (int i = 0; i < 3; i++) {
    sum = ((uint64_t)sum >> 32) + value_1.bits[i] + value_2.bits[i];
    tmp_result.bits[i] = (uint32_t)(sum);
  }
  sum = (sum >> 32);
  if (sum != (uint64_t)0) {
    overflow_flag = 1;
  }
  *result = tmp_result;
  result->exp = value_1.exp;
  result->sign = value_1.sign;
  return overflow_flag;
}