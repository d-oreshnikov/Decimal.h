#include "../my_decimal.h"

int COUNT_OF(uint32_t *value, int sz) {
  int idx;
  for (idx = sz; idx >= 0; idx--) {
    if (value[idx]) {
      break;
    }
  }
  return idx;
}