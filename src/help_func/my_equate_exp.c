#include "../my_decimal.h"

void my_equate_exp(my_decimal value_1, my_decimal value_2,
                    my_decimal *new_value1, my_decimal *new_value2,
                    my_decimal *remainder, int *delta) {
  int delta_exp = 0;
  delta_exp = value_1.exp - value_2.exp;
  if (delta_exp >= 0) {
    my_increase_exp(value_2, &value_2, delta_exp);
  } else {
    my_increase_exp(value_1, &value_1, -delta_exp);
  }
  delta_exp = value_1.exp - value_2.exp;
  *delta = delta_exp;
  if (delta_exp >= 0) {
    my_decrease_exp(value_1, &value_1, remainder, delta_exp);
  } else {
    my_decrease_exp(value_2, &value_2, remainder, -delta_exp);
  }
  *new_value1 = value_1;
  *new_value2 = value_2;
}