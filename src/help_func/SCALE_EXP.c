#include "../my_decimal.h"

uint32_t POW10_1[] = {1,      10,      100,      1000,      10000,
                      100000, 1000000, 10000000, 100000000, 1000000000};

int SCALE_EXP(uint32_t *value, int32_t *exp, int idx) {
  int status = OP_OK;
  int nExp = 0;
  if (idx > 2) {
    nExp = (int)(idx << 5) - 64 - 1;
    nExp -= clz(value[idx]);
    nExp = ((nExp * 77) >> 8) + 1;
  }

  if (nExp > *exp) {
    status = OP_LARGE;
  } else {
    if (nExp != 0) {
      uint32_t mod = 0;
      uint32_t sticky = 0;
      *exp = *exp - nExp;
      while (1) {
        sticky |= mod;
        uint32_t scale = nExp > 4 ? 4 : nExp;
        uint32_t halfpow10 = POW10_1[scale] >> 1;
        DIV_EXP10(value, &mod, scale, idx);
        if (value[idx] == 0 && idx != 0) {
          idx--;
        }
        nExp -= 4;
        if (nExp > 0) {
          continue;
        }
        if (halfpow10 <= mod &&
            (halfpow10 < mod || ((value[0] & 1) | sticky) != 0) &&
            ++value[0] == 0) {
          uint32_t cur = 0;
          while (++value[++cur] == 0)
            ;
        }
        break;
      }
    }
  }
  return status;
}