#include "../my_decimal.h"

void SHL(uint32_t *value, int shift) {
  uint32_t carry = 0;
  for (int i = 0; i < MAX_U32_SCALE; i++) {
    uint32_t v = (value[i] << shift) | carry;
    carry = value[i] >> (32 - shift);
    value[i] = v;
  }
}
