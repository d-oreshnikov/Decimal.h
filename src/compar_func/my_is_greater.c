#include "../my_decimal.h"
int my_is_greater(my_decimal value_1, my_decimal value_2) {
  int result = TRUE;

  if (my_is_less(value_1, value_2) == TRUE ||
      my_is_equal(value_1, value_2) == TRUE) {
    result = FALSE;
  }
  return result;
}
