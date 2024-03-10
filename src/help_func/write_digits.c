#include "../my_decimal.h"

void write_digits(my_decimal *result, int digits) {
  int znak = result->sign;
  result->bits[3] = digits * 65536;
  result->sign = znak;
}