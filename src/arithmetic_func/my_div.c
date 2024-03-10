#include "../my_decimal.h"

int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  // зануляем все биты переданной структуры result
  my_set_zero(result);
  // создаём два пространства для хранения целой и дробной части при делении
  uint32_t div[MAX_U32_SCALE + 1], mod[MAX_U32_SCALE + 1];

  int status = OP_OK;

  uint32_t zero = 0;
  uint32_t val_1[MAX_U32_SCALE + 1], val_2[MAX_U32_SCALE + 1];
  for (int i = 0; i < MAX_U32_SCALE + 1; i++) {
    val_1[i] = i < 3 ? value_1.bits[i] : 0;
    val_2[i] = i < 3 ? value_2.bits[i] : 0;
    zero |= val_2[i];
    // переписывем числа в большие пространства
    // смотрим не равно ли второе число нулю
  }

  if (!zero) {
    status = OP_DIV_ZERO;
  } else {
    int32_t exp = value_1.exp - value_2.exp;
    uint32_t sign = value_1.sign ^ value_2.sign;

    if (exp < 0) {
      MUL_EXP10(val_1, -exp, MAX_U32_SCALE);
      exp = 0;
    }
    DIV(val_1, val_2, div, mod);
    // делим до тех пор пока число не даст в остатке 0 или exp не больше 28
    while (exp < 28 && !isZero(mod, MAX_U32_SCALE + 1)) {
      MUL_EXP10(val_1, 1, MAX_U32_SCALE);
      DIV(val_1, val_2, div, mod);
      exp++;
    }

    int idx = COUNT_OF(div, MAX_U32_SCALE);
    if (idx > 2) {
      status = SCALE_EXP(div, &exp, idx);
    }

    if (status == OP_OK) {
      for (int i = 0; i < 3; i++) {
        result->bits[i] = div[i];
      }
      result->exp = exp;
      result->sign = sign;
    }
  }
  return status;
}
