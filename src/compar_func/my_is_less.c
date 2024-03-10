#include "../my_decimal.h"

int my_is_less(my_decimal value_1, my_decimal value_2) {
  int result = 0;
  int sign_1 = value_1.sign;
  int sign_2 = value_2.sign;

  // get a sign of a decimal
  // if numbers have one sign, define the scale (power of 10)

  if (my_is_equal(value_1, value_2)) {
    result = FALSE;
  } else if (sign_1 < sign_2) {
    result = FALSE;
  } else if (sign_1 > sign_2) {
    result = TRUE;
  } else {
    uint32_t val_1[MAX_U32_SCALE];
    uint32_t val_2[MAX_U32_SCALE];

    // "increase" the number to have an ability
    // to define it after multiplication

    for (int i = 0; i < MAX_U32_SCALE; i++) {
      val_1[i] = i < 3 ? value_1.bits[i] : 0;
      val_2[i] = i < 3 ? value_2.bits[i] : 0;
    }

    // if the power is different we need to normalize numbers
    int32_t scale = value_2.exp - value_1.exp;
    if (scale < 0) {
      scale = -scale;
      MUL_EXP10(val_2, scale, MAX_U32_SCALE);
    } else {
      MUL_EXP10(val_1, scale, MAX_U32_SCALE);
    }

    // compare numbers
    for (int i = MAX_U32_SCALE - 1; i >= 0; i--) {
      if (val_1[i] < val_2[i]) {
        result = TRUE;
        break;
      } else if (val_1[i] > val_2[i]) {
        result = FALSE;
        break;
      }
    }

    // if numbers are negative,
    // the comparion is inverted
    if (sign_1 && sign_2) {
      result ^= TRUE;
    }
  }

  return result;
}