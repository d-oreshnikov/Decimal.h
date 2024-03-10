#include "../my_decimal.h"

void my_mul_precise(my_decimal value_1, my_decimal value_2, uint32_t **mul,
                     uint32_t *sign, uint32_t *exp) {
  *sign = ((value_1.sign + value_2.sign) == 1) ? 1 : 0;
  *exp = value_1.exp + value_2.exp;
  for (int i = 0; i < 6; i++) {
    (*mul)[i] = (uint32_t)0;
  }
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      uint64_t tmp = 0;
      tmp =
          (uint64_t)(*mul)[i + j] + (uint64_t)value_1.bits[j] * value_2.bits[i];
      (*mul)[i + j] = (uint32_t)tmp;
      for (int k = i + j + 1; k < 6; k++) {
        tmp = (uint64_t)(*mul)[k] + (uint64_t)(tmp >> 32);
        (*mul)[k] = (uint32_t)tmp;
      }
    }
  }
}