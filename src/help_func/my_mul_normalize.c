#include "../my_decimal.h"

int my_mul_normalize(uint32_t *mul, uint32_t **mul_normalized, uint32_t *exp,
                      uint32_t sign) {
  OP_STATUS status = OP_OK;
  for (int i = 0; i < 6; i++) {
    (*mul_normalized)[i] = mul[i];
  }
  while (*exp > 28) {
    my_uint32_array_div_10(*mul_normalized, mul_normalized, 6, *exp - 28);
    *exp = 28;
  }
  while (my_mul_check(*mul_normalized) == 1 && *exp > 0) {
    my_uint32_array_div_10(*mul_normalized, mul_normalized, 6, 1);
    *exp = *exp - 1;
  }
  if (my_mul_check(*mul_normalized) == 1) {
    if (sign == 1) {
      status = OP_SMALL;
    } else {
      status = OP_LARGE;
    }
  }
  return status;
}