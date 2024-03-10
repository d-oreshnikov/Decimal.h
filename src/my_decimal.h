
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_U32_SCALE 6
#define TRUE 1
#define FALSE 0

typedef union {
  struct {
    uint32_t : 32;
    uint32_t : 32;
    uint32_t : 32;
    uint32_t : 16;
    uint32_t exp : 8;
    uint32_t : 7;
    uint32_t sign : 1;
  };
  uint32_t bits[4];
} my_decimal;

typedef enum {
  CONVERTOK = 0,
  CONVERTERROR = 1,
  OP_OK = 0,
  OP_LARGE = 1,
  OP_SMALL = 2,
  OP_DIV_ZERO = 3
} OP_STATUS;

// cupcakep convert func
int my_from_int_to_decimal(int src, my_decimal *dst);
int my_from_decimal_to_int(my_decimal src, int *dst);
int my_from_decimal_to_float(my_decimal src, float *dst);
int my_from_float_to_decimal(float src, my_decimal *dst);

// takakoka compare func
int my_is_less(my_decimal value_1, my_decimal value_2);
int my_is_less_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_greater(my_decimal value_1, my_decimal value_2);
int my_is_greater_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_equal(my_decimal value_1, my_decimal value_2);
int my_is_not_equal(my_decimal value_1, my_decimal value_2);

// mathildc round func
int my_truncate(my_decimal value, my_decimal *result);
int my_floor(my_decimal value, my_decimal *result);
// jesicahi round func
int my_round(my_decimal value, my_decimal *result);
int my_negate(my_decimal value, my_decimal *result);

// mathildc arithmetic func
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);
// jesicahi arithmetic func
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mod(my_decimal value_1, my_decimal value_2, my_decimal *result);

// help_func
void my_set_zero(my_decimal *value);
void write_digits(my_decimal *result, int digits);
void my_copy(my_decimal value, my_decimal *dst);
void my_swap(my_decimal *value_1, my_decimal *value_2);
void my_abs(my_decimal value, my_decimal *dst);
void my_uint32_array_div_10(uint32_t *array, uint32_t **res_array,
                             int array_len, int pow_10);
void my_uint32_array_mul_10(uint32_t *init_array, uint32_t **res_array,
                             int array_len, int pow_10);
void my_uint32_array_sub(uint32_t *init_array1, uint32_t *init_array2,
                          uint32_t **res_array, int array_len);
void my_bits_div_10(my_decimal value, my_decimal *dst, int pow_10);
void my_bits_mul_10(my_decimal value, my_decimal *dst, int pow_10);
void my_bits_sub(my_decimal value_1, my_decimal value_2,
                  my_decimal *result);
int my_bits_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_normalize(my_decimal value, my_decimal *result);
void my_decrease_exp(my_decimal value, my_decimal *rounded,
                      my_decimal *remainder, uint32_t delta_exp);
void my_increase_exp(my_decimal value, my_decimal *result,
                      uint32_t delta_exp);
void my_equate_exp(my_decimal value_1, my_decimal value_2,
                    my_decimal *new_value1, my_decimal *new_value2,
                    my_decimal *remainder, int *delta);
int my_overflow(my_decimal value, my_decimal *result, my_decimal *remainder,
                 int overflow_flag);
int my_round_sum(my_decimal value, my_decimal remainder,
                  my_decimal *result);
int my_sum(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_bits_equal(my_decimal value_1, my_decimal value_2);
int my_is_abs_less(my_decimal value_1, my_decimal value_2);
int my_is_zero(my_decimal value);
int my_mul_check(uint32_t *mul);
void my_mul_precise(my_decimal value_1, my_decimal value_2, uint32_t **mul,
                     uint32_t *sign, uint32_t *exp);
int my_mul_normalize(uint32_t *mul, uint32_t **mul_normalized, uint32_t *exp,
                      uint32_t sign);
int my_negate(my_decimal value, my_decimal *result);
int isZero(uint32_t *v, int sz);
int clz(uint32_t x);
int COUNT_OF(uint32_t *value, int sz);
void MUL_EXP10(uint32_t *value, int32_t exp, int sz);
void DIV_EXP10(uint32_t *value, uint32_t *mod, int32_t exp, int sz);
int SCALE_EXP(uint32_t *value, int32_t *exp, int idx);
void SHL(uint32_t *value, int shift);
void DIV(uint32_t *value_1, uint32_t *value_2, uint32_t *div, uint32_t *mod);
