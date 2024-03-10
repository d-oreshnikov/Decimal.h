#include "../my_decimal.h"

void my_uint32_array_sub(uint32_t *init_array1, uint32_t *init_array2,
                          uint32_t **res_array, int array_len) {
  uint32_t tmp = 0;
  // for (int i = 0; i < array_len; i++) {
  //   (*res_array)[i] = (uint32_t)0;
  // }
  for (int i = 0; i < array_len; i++) {
    uint64_t minuend = 0;
    // minuend = init_array1[i] - tmp;
    if (((uint64_t)init_array1[i]) < ((uint64_t)init_array2[i] + tmp)) {
      minuend = ((uint64_t)1 << 32) + (uint64_t)init_array1[i] - tmp;
      ;
      tmp = 1;
    } else {
      minuend = init_array1[i] - tmp;
      tmp = 0;
    }
    (*res_array)[i] = (uint32_t)(minuend - init_array2[i]);
  }
}