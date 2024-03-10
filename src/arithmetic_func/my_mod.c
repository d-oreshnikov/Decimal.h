#include "../my_decimal.h"

int my_mod(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int status;

  status = my_div(value_1, value_2, result);
  if (status == OP_OK) {
    my_truncate(*result, result);
    my_mul(*result, value_2, result);
    status = my_sub(value_1, *result, result);
  }

  return status;
}
