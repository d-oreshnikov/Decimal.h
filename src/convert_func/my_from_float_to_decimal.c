#include "../my_decimal.h"

int my_from_float_to_decimal(float src, my_decimal *dst) {
  int flag = CONVERTOK;
  double buf = (double)src;
  if (dst == NULL) {
    flag = CONVERTERROR;
  } else if (src >= 7.922816251e+29 || src <= -7.922816251e+29) {
    flag = CONVERTERROR;
  } else {
    my_set_zero(dst);
    if (src < 0) {
      dst->sign = 1;
      src *= -1;
      buf *= -1;
    }

    unsigned scale = 0;
    while (scale < 28 && (int)buf / (int)powl(2, 21) == 0) {
      buf *= 10;
      scale++;
    }
    buf = round(buf);

    dst->bits[0] = (int)buf;
    write_digits(dst, scale);
  }
  return flag;
}