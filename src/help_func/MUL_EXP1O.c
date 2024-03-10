#include "../my_decimal.h"

uint32_t POW10_0[] = {1,      10,      100,      1000,      10000,
                      100000, 1000000, 10000000, 100000000, 1000000000};

void MUL_EXP10(uint32_t *value, int32_t exp, int sz) {
  while (exp > 0) {
    // устранавливаем ШКАЛУ от 0 до 9. Если степень больше 9, то устанавливаем
    // степень равной 9
    uint32_t scale = exp > 9 ? 9 : exp;

    uint32_t carry = 0;
    // с помощью cz проходимся по битам value
    for (int i = 0; i < sz; i++) {
      // получаем умножение битов value на числа из массива + добавляем остаток
      uint64_t mul = (uint64_t)value[i] * POW10_0[scale] + carry;
      // присваиваем то, что останется при переводе инт64 в инт32
      value[i] = (uint32_t)mul;
      //  зачем-то сдвигаем mul на 32 бита в право
      carry = (uint32_t)(mul >> 32);
    }
    exp -= scale;
  }
}