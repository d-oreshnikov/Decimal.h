#include "../my_decimal.h"

int my_is_abs_less(my_decimal value_1, my_decimal value_2) {
  int result = 0;
  my_abs(value_1, &value_1);
  my_abs(value_2, &value_2);
  result = my_is_less(value_1, value_2);
  return result;
}