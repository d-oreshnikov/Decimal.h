#include "../my_decimal.h"

int my_round(my_decimal value, my_decimal *result) {
  // create decimal number which equal to 1.
  my_decimal one;
  one.bits[0] = 1;
  one.bits[1] = 0;
  one.bits[2] = 0;
  one.bits[3] = 0;
  // get sign bit;
  int sign = value.sign;
  my_decimal integer_part;
  int status = my_truncate(value, &integer_part);  // есть ли целая часть
  if (status == CONVERTOK) {
    my_decimal decimal_part;
    status = my_sub(value, integer_part, &decimal_part);
    decimal_part.sign = 0;
    int zero = 1;
    for (int i = 0; i < 3; i++)
      if (decimal_part.bits[i] != 0)
        zero = 0;  // if all bit is 0 then no decimal part
    if (!status) {
      if (zero)
        *result = integer_part;
      else {
        my_decimal half;
        half.bits[0] = 5;
        half.bits[1] = 0;
        half.bits[2] = 0;
        half.bits[3] = 0;
        half.exp = 1;
        if (my_is_greater(decimal_part, half))
          status = sign ? my_sub(integer_part, one, result)
                        : my_add(integer_part, one, result);
        else if (my_is_equal(decimal_part, half)) {
          if ((integer_part.bits[0] & 1) == 0)
            *result = integer_part;
          else
            status = sign ? my_sub(integer_part, one, result)
                          : my_add(integer_part, one, result);
        } else
          *result = integer_part;
      }
    }
  }
  return !status ? status : 1;
}
