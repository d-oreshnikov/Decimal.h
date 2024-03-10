#include "../my_decimal.h"

uint32_t POW10[] = {1,      10,      100,      1000,      10000,
                    100000, 1000000, 10000000, 100000000, 1000000000};

void DIV_EXP10(uint32_t *value, uint32_t *mod, int32_t exp, int sz) {
  uint32_t carry = 0;

  while (exp > 0) {
    uint32_t scale = exp > 9 ? 9 : exp;
    uint32_t pow10 = POW10[scale];
    carry = 0;
    for (int i = sz; i >= 0; i--) {
      uint64_t div = ((uint64_t)carry << 32) | value[i];
      value[i] = (uint32_t)(div / pow10);
      carry = (uint32_t)(div % pow10);
    }
    exp -= scale;
  }
  *mod = carry;
}