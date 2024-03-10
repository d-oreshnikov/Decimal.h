#include "../my_decimal.h"
int my_is_greater_or_equal(my_decimal value_1, my_decimal value_2) {
  int result = FALSE;

  if (my_is_equal(value_1, value_2) == TRUE ||
      my_is_greater(value_1, value_2) == TRUE) {
    result = TRUE;
  }
  return result;
}