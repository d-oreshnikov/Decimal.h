#include "../my_decimal.h"

void my_uint32_array_div_10(uint32_t *init_array, uint32_t **res_array,
                             int array_len, int pow_10) {
  for (int i = 0; i < array_len; i++) {
    (*res_array)[i] = init_array[i];
  }
  while (pow_10 > 0) {
    uint32_t divider = 1;
    divider = (pow_10 < 10) ? pow_10 : 9;
    pow_10 -= divider;
    divider = pow(10, divider);
    uint64_t tmp = 0;
    for (int i = array_len - 1; i >= 0; i--) {
      tmp = (tmp << 32) + (*res_array)[i];
      (*res_array)[i] = tmp / divider;
      tmp %= divider;
    }
  }
}