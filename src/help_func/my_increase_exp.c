#include "../my_decimal.h"

void my_increase_exp(my_decimal value, my_decimal *result,
                      uint32_t delta_exp) {
  int loss_flag = 0;
  my_decimal increased, compare;
  while (delta_exp > 0 && loss_flag == 0) {
    my_copy(value, &compare);
    my_bits_mul_10(compare, &increased, 1);
    my_bits_div_10(increased, &compare, 1);
    if (my_is_equal(compare, value)) {
      my_copy(increased, &value);
      value.exp += 1;
      delta_exp -= 1;
    } else {
      loss_flag = 1;
    }
  }
  *result = value;
}