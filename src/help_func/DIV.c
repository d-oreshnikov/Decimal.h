#include "../my_decimal.h"

void DIV(uint32_t *value_1, uint32_t *value_2, uint32_t *div, uint32_t *mod) {
  uint32_t a[MAX_U32_SCALE + 1];

  for (int i = 0; i < MAX_U32_SCALE + 1; i++) {
    div[i] = mod[i] = 0;
  }

  for (int i = MAX_U32_SCALE * 32; i >= 0; i--) {
    int idx = i >> 5;
    int shift = i & ((1 << 5) - 1);
    SHL(mod, 1);
    mod[0] |= (value_1[idx] >> shift) & 1;
    uint32_t carry = 0;
    for (int i = 0; i < MAX_U32_SCALE + 1; i++) {
      uint64_t v = (uint64_t)mod[i] - (uint64_t)value_2[i] - (uint64_t)carry;
      a[i] = (uint32_t)v;
      carry = (v >> 63);
    }
    if (carry == 0) {
      for (int i = 0; i < MAX_U32_SCALE + 1; i++) {
        mod[i] = a[i];
      }
      div[idx] |= (1 << shift);
    }
  }
}