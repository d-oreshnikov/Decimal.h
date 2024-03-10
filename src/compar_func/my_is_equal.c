#include "../my_decimal.h"

int my_is_equal(my_decimal value_1, my_decimal value_2) {
  int result = TRUE;

  int zeroV1 = 0, zeroV2 = 0;
  for (int i = 0; i < 3; i++) {
    zeroV1 |= value_1.bits[i];
    zeroV2 |= value_2.bits[i];
  }

  // additional check for numbers of different signs

  if (value_1.sign != value_2.sign && (zeroV1 || zeroV2)) {
    result = FALSE;
  } else {
    uint32_t val_1[MAX_U32_SCALE];
    uint32_t val_2[MAX_U32_SCALE];

    // make a number "wider" to make
    // it possible to multiply

    for (int i = 0; i < MAX_U32_SCALE; i++) {
      val_1[i] = i < 3 ? value_1.bits[i] : 0;
      val_2[i] = i < 3 ? value_2.bits[i] : 0;
    }
    // define scale to normalize numbers
    int32_t scale = value_2.exp - value_1.exp;
    if (scale < 0) {
      scale = -scale;
      MUL_EXP10(val_2, scale, MAX_U32_SCALE);
    } else {
      MUL_EXP10(val_1, scale, MAX_U32_SCALE);
    }
    for (int i = MAX_U32_SCALE - 1; i >= 0; i--) {
      if (val_1[i] != val_2[i]) {
        result = FALSE;
        break;
      }
    }
  }
  return result;
}
