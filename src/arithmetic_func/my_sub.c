#include "../my_decimal.h"

int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int status = OP_OK;
  my_negate(value_2, &value_2);
  status = my_sum(value_1, value_2, result);
  return status;
}
