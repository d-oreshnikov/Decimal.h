#include "../my_decimal.h"

void my_swap(my_decimal *value_1, my_decimal *value_2) {
  my_decimal tmp;
  tmp = *value_1;
  *value_1 = *value_2;
  *value_2 = tmp;
}