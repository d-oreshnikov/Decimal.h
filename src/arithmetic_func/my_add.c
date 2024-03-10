#include "../my_decimal.h"

int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int status = OP_OK;
  status = my_sum(value_1, value_2, result);
  return status;
}
