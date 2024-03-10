#include "../my_decimal.h"

void my_bits_mul_10(my_decimal value, my_decimal *dst, int pow_10) {
  // умножает целочисленное поле value (с 0 по 3 bit) на 10^(pow) и
  // записывает результат в dst
  *dst = value;
  uint32_t *dst_bits = NULL;
  dst_bits = (uint32_t *)malloc(3 * sizeof(uint32_t));
  my_uint32_array_mul_10(value.bits, &dst_bits, 3, pow_10);
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = dst_bits[i];
  }
  free(dst_bits);
}