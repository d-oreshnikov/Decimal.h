#include "../my_decimal.h"

int isZero(uint32_t *v, int sz) {
  int status = 1;
  for (int i = 0; i < sz; i++) {
    if (v[i]) {
      status = 0;
      break;
    }
  }
  return status;
}