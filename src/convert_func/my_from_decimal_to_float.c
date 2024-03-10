#include "../my_decimal.h"

int my_from_decimal_to_float(my_decimal src, float *dst) {
  int flag = CONVERTOK;
  if (dst == NULL)
    flag = CONVERTERROR;
  else {
    int sign = src.sign;
    int exp = src.exp;
    double res = 0;
    if (0 > exp || 28 < exp)
      flag = CONVERTERROR;
    else {
      int j = 0;
      for (int i = 0; i <= 2; i++) {
        for (int h = 0; h < 32; h++, j++) {
          res += pow(2, j) * ((src.bits[i] & (1 << h)) >> h);
        }
      }
      if (sign) res *= -1;
      while (exp--) res /= 10;
      *dst = (float)res;
    }
  }
  return flag;
}
