#include "../my_decimal.h"

void my_uint32_array_mul_10(uint32_t *init_array, uint32_t **res_array,
                             int array_len, int pow_10) {
  for (int i = 0; i < array_len; i++) {
    (*res_array)[i] = init_array[i];
  }
  while (pow_10 > 0) {
    uint32_t multiplier = 1;
    multiplier = (pow_10 < 10) ? pow_10 : 9;
    pow_10 -= multiplier;
    multiplier = pow(10, multiplier);
    uint64_t tmp = 0;
    for (int i = 0; i < array_len; i++) {
      tmp = tmp + (uint64_t)(*res_array)[i] * multiplier;
      (*res_array)[i] = (uint32_t)tmp;
      tmp = (uint32_t)(tmp >> 32);
    }
  }
}