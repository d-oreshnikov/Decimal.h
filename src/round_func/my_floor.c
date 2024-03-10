#include "../my_decimal.h"

int my_floor(my_decimal value, my_decimal *result) {
  my_decimal tmp_result;
  int error_flag = CONVERTOK, op_status = OP_OK;
  error_flag = my_truncate(value, &tmp_result);
  my_set_zero(result);
  if (error_flag == CONVERTOK) {
    if (value.sign == 1 && my_is_not_equal(value, tmp_result)) {
      my_decimal one;
      my_from_int_to_decimal(1, &one);
      op_status = my_sub(tmp_result, one, &tmp_result);
    }
    if (op_status == OP_OK) {
      my_copy(tmp_result, result);
    }
  }
  return error_flag;
}
