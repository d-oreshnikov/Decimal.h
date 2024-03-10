#include "my_decimal_test.h"

START_TEST(arithmetic_check) {
  my_decimal src1, src2, true_result, result, dec_null, dec_max;
  int val;

  my_set_zero(&dec_null);
  my_set_zero(&true_result);
  dec_max.bits[0] = dec_max.bits[1] = dec_max.bits[2] = 0xffffffff;
  dec_max.bits[3] = 0;

  // 1+3=4
  src1 = dec_null;
  src1.bits[0] = 1;
  src2 = dec_null;
  src2.bits[0] = 3;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // -1+3=2
  src1.bits[0] = 1;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2 = dec_null;
  src2.bits[0] = 3;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // -1+(-3)=-4
  src1.bits[0] = 1;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 3;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 1+(-3)=-2
  src1 = dec_null;
  src1.bits[0] = 1;
  src2.bits[0] = 3;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 3+1=4
  src1 = dec_null;
  src1.bits[0] = 3;
  src2 = dec_null;
  src2.bits[0] = 1;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // -3+1=-2
  src1.bits[0] = 3;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2 = dec_null;
  src2.bits[0] = 1;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 3+(-1)=2
  src1 = dec_null;
  src1.bits[0] = 3;
  src2.bits[0] = 1;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // -3+(-1)=-4
  src1.bits[0] = 3;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 1;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 2-16=-14
  src1 = dec_null;
  src1.bits[0] = 2;
  src2.bits[0] = 16;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 14);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335+(-6)=79228162514264337593543950329
  src1 = dec_max;
  src2.bits[0] = 6;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xffffffff - 6);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335+0.4=79228162514264337593543950335
  src1 = dec_max;
  src2.bits[0] = 4;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 65536;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335+0.5=OP_LARGE
  src1 = dec_max;
  src2.bits[0] = 5;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 65536;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(val, OP_LARGE);

  // -79228162514264337593543950335+79228162514264337593543950335=-0
  src1 = dec_max;
  src1.bits[3] = 0x80000000;
  src2 = dec_max;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 99+1=100
  src1 = dec_null;
  src1.bits[0] = 99;
  src2 = dec_null;
  src2.bits[0] = 1;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335-79228162514264337593543950335=0
  src1 = dec_max;
  src2 = dec_max;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335+79228162514264337593543950335=OP_LARGE
  src1 = dec_max;
  src2 = dec_max;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(val, OP_LARGE);

  // 18446744073709551615-79228162514264337593543950335=-79228162495817593519834398720
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src2 = dec_max;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335*10^28-79228162514264337593543950335=-79228162514264337593543950327
  src1 = dec_max;
  src1.bits[3] = 0x001C0000;
  src2 = dec_max;
  src2.bits[3] = 0x80000000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xFFFFFFF7);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, 0);

  // -79228162514264337593543950335+79228162514264337593543950335*10^28=-79228162514264337593543950327
  src1 = dec_max;
  src1.bits[3] = 0x80000000;
  src2 = dec_max;
  src2.bits[3] = 0x001C0000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xFFFFFFF7);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, 0);

  // NEW 39614081257132168796771975168*10^-28
  //    +39614081257132168796771975168*10^-28
  //    =7922816251426433759354395033 *10^-27
  src1.bits[0] = (uint32_t)0;
  src1.bits[1] = (uint32_t)0;
  src1.bits[2] = 0b10000000000000000000000000000000;
  src1.bits[3] = 0x001C0000;
  src2.bits[0] = (uint32_t)0;
  src2.bits[1] = (uint32_t)0;
  src2.bits[2] = 0b10000000000000000000000000000000;
  src2.bits[3] = 0x001C0000;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0],
                   0b10011001100110011001100110011001);
  ck_assert_int_eq((unsigned)result.bits[1],
                   0b10011001100110011001100110011001);
  ck_assert_int_eq((unsigned)result.bits[2],
                   0b00011001100110011001100110011001);
  ck_assert_int_eq((unsigned)result.bits[3], 0x001B0000);
  ck_assert_int_eq(val, 0);

  // NEW ERR
  src1.bits[0] = (uint32_t)1;
  src1.bits[1] = (uint32_t)0;
  src1.bits[2] = (uint32_t)0;
  src1.bits[3] = (uint32_t)0;
  src2.bits[0] = (uint32_t)0;
  src2.bits[1] = (uint32_t)0;
  src2.bits[2] = (uint32_t)0;
  src2.bits[3] = 2293760;
  // src2.exp = 35;
  val = my_add(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0);
  ck_assert_int_eq((unsigned)result.bits[1], 0);
  ck_assert_int_eq((unsigned)result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0);
  ck_assert_int_eq(val, OP_SMALL);

  // 0-2=-2
  src1 = dec_null;
  src2 = dec_null;
  src2.bits[0] = 2;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 3-1=2
  src1 = dec_null;
  src2 = dec_null;
  src1.bits[0] = 3;
  src2.bits[0] = 1;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // -3-(-1)=-2
  src1.bits[0] = 3;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 1;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // -1-(-3)=2
  src1.bits[0] = 1;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 3;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 1-3=2
  src1 = dec_null;
  src2 = dec_null;
  src1.bits[0] = 1;
  src2.bits[0] = 3;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // 1-(-3)=4
  src1 = dec_null;
  src2 = dec_null;
  src1.bits[0] = 1;
  src2.bits[0] = 3;
  src2.bits[3] = 0x80000000;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // -1-3=-4
  src1 = dec_null;
  src2 = dec_null;
  src1.bits[0] = 1;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 3;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // -3-1=-4
  src1 = dec_null;
  src2 = dec_null;
  src1.bits[0] = 3;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 1;
  val = my_sub(src1, src2, &result);

  // 3-(-1)=4
  src1 = dec_null;
  src2 = dec_null;
  src1.bits[0] = 3;
  src2.bits[0] = 1;
  src2.bits[3] = 0x80000000;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335-6=79228162514264337593543950329
  src1 = dec_max;
  src2 = dec_null;
  src2.bits[0] = 6;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xffffffff - 6);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335-0.4=79228162514264337593543950335
  src1 = dec_max;
  src2 = dec_null;
  src2.bits[0] = 4;
  src2.bits[3] = 65536;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335-0.5=79228162514264337593543950334
  src1 = dec_max;
  src2 = dec_null;
  src2.bits[0] = 5;
  src2.bits[3] = 65536;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xffffffff - 1);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335-79228162514264337593543950335=0
  src1 = dec_max;
  src2 = dec_max;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 100-1=99'
  src1 = dec_null;
  src2 = dec_null;
  src1.bits[0] = 100;
  src2.bits[0] = 1;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 99);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // -79228162514264337593543950335*10^28-79228162514264337593543950335=-79228162514264337593543950342
  src1 = dec_max;
  src2 = dec_max;
  src1.bits[3] = 0b10000000000111000000000000000000;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(val, OP_SMALL);

  // 79228162514264337593543950335*10^28--79228162514264337593543950335=79228162514264337593543950342
  src1 = dec_max;
  src2 = dec_max;
  src1.bits[3] = 0b00000000000111000000000000000000;
  src2.bits[3] = 0x80000000;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(val, OP_LARGE);

  // 0-0=0
  src1 = dec_null;
  src2 = dec_null;
  src1.bits[3] = 0x80000000;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
  ck_assert_int_eq(val, OP_OK);

  // NEW 18446744073709551648 - 57 = 18446744073709551591
  src1.bits[0] = 32;
  src1.bits[1] = 0;
  src1.bits[2] = 1;
  src1.bits[3] = 0;
  src2.bits[0] = 57;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  val = my_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4294967271);
  ck_assert_int_eq(result.bits[1], 4294967295);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, OP_OK);

  // 57*32= 1824
  src1.bits[0] = 57;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src2.bits[0] = 32;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  val = my_mul(src1, src2, &result);

  true_result.bits[0] = 1824;
  true_result.bits[1] = 0;
  true_result.bits[2] = 0;
  true_result.bits[3] = 0;
  ck_assert_int_eq(result.bits[0], true_result.bits[0]);
  ck_assert_int_eq(result.bits[1], true_result.bits[1]);
  ck_assert_int_eq(result.bits[2], true_result.bits[2]);
  ck_assert_int_eq(result.bits[3], true_result.bits[3]);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335 * (-0.00321)= -254322401670788523675276080.58
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;
  src2.bits[0] = 0b00000000000000000000000101000001;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0b10000000000001010000000000000000;
  val = my_mul(src1, src2, &result);

  true_result.bits[0] = 0b10111100011010100111111011111010;
  true_result.bits[1] = 0b00000100000110001001001101110100;
  true_result.bits[2] = 0b01010010001011010000111001010110;
  true_result.bits[3] = 0b10000000000000100000000000000000;

  ck_assert_int_eq(result.bits[0], true_result.bits[0]);
  ck_assert_int_eq(result.bits[1], true_result.bits[1]);
  ck_assert_int_eq(result.bits[2], true_result.bits[2]);
  ck_assert_int_eq(result.bits[3], true_result.bits[3]);
  ck_assert_int_eq(val, OP_OK);

  // (-89.4730208302234) * (-1834857353874.7273873454897) =
  // 164170230243722.07187139009243
  src1.bits[0] = 0b10011100001111000101010010011010;
  src1.bits[1] = 0b00000000000000110010110111000000;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000011010000000000000000;
  src2.bits[0] = 0b00101001010000111111011100110001;
  src2.bits[1] = 0b00101010001001011001010110011000;
  src2.bits[2] = 0b00000000000011110010110101110110;
  src2.bits[3] = 0b10000000000011010000000000000000;
  true_result.bits[0] = 0b01100111000001001001101011011011;
  true_result.bits[1] = 0b01110000001111011110100011110111;
  true_result.bits[2] = 0b00110101000010111101011111011001;
  true_result.bits[3] = 0b00000000000011100000000000000000;
  val = my_mul(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], true_result.bits[0]);
  ck_assert_int_eq(result.bits[1], true_result.bits[1]);
  ck_assert_int_eq(result.bits[2], true_result.bits[2]);
  ck_assert_int_eq(result.bits[3], true_result.bits[3]);
  ck_assert_int_eq(val, OP_OK);

  // 79228162514264337593543950335*1.7=OP_LARGE
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;
  src2.bits[0] = 17;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x00010000;
  val = my_mul(src1, src2, &result);
  ck_assert_int_eq(val, OP_LARGE);

  // -79228162514264337593543950335 * 10 = -OP_LARGE
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 10;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  val = my_mul(src1, src2, &result);

  ck_assert_int_eq(val, OP_SMALL);

  // 7.9228162514264337593543950335 * 7.9228162514264337593543950335
  // = 62.771017353866807638357894230
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0b00000000000111000000000000000000;
  src2.bits[0] = 0xffffffff;
  src2.bits[1] = 0xffffffff;
  src2.bits[2] = 0xffffffff;
  src2.bits[3] = 0b00000000000111000000000000000000;
  true_result.bits[0] = 158262358;
  true_result.bits[1] = 899300158;
  true_result.bits[2] = 3402823669;
  true_result.bits[3] = 1769472;
  val = my_mul(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], true_result.bits[0]);
  ck_assert_int_eq(result.bits[1], true_result.bits[1]);
  ck_assert_int_eq(result.bits[2], true_result.bits[2]);
  ck_assert_int_eq(result.bits[3], true_result.bits[3]);
  ck_assert_int_eq(val, OP_OK);

  // 0.000002514264337593543950335 * 0.9228162514264337593543950335 =
  // 0.0000023202039911132397835426
  src1.bits[0] = 0b11011111111111111111111111111111;
  src1.bits[1] = 0b01001100011011010100110111100101;
  src1.bits[2] = 0b00000000000000000000000010001000;
  src1.bits[3] = 0b00000000000110110000000000000000;
  src2.bits[0] = 0b10001111111111111111111111111111;
  src2.bits[1] = 0b01001100111111001110111101011000;
  src2.bits[2] = 0b00011101110100010101101101101100;
  src2.bits[3] = 0b00000000000111000000000000000000;
  val = my_mul(src1, src2, &result);
  true_result.bits[0] = 0b10111010011100000001010010100010;
  true_result.bits[1] = 0b11001000111111001001000101111111;
  true_result.bits[2] = 0b00000000000000000000010011101001;
  true_result.bits[3] = 0b00000000000111000000000000000000;
  ck_assert_int_eq(result.bits[0], true_result.bits[0]);
  ck_assert_int_eq(result.bits[1], true_result.bits[1]);
  ck_assert_int_eq(result.bits[2], true_result.bits[2]);
  ck_assert_int_eq(result.bits[3], true_result.bits[3]);
  ck_assert_int_eq(val, OP_OK);

  // 7.9228162514264337593543950335 * 0 =0
  // степень нуля
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0b00000000000111000000000000000000;
  src2.bits[0] = 0;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;

  val = my_mul(src1, src2, &result);
  ck_assert_int_eq(0, result.bits[0]);
  ck_assert_int_eq(0, result.bits[1]);
  ck_assert_int_eq(0, result.bits[2]);
  ck_assert_int_eq(0, result.bits[3]);
  ck_assert_int_eq(val, OP_OK);

  // -79228162514264337593543950335 * 79228162514264337593543950335
  // = negativ_inf
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 0xffffffff;
  src2.bits[1] = 0xffffffff;
  src2.bits[2] = 0xffffffff;
  src2.bits[3] = 0;

  val = my_mul(src1, src2, &result);
  // ck_assert_int_eq(0, result.bits[0]);
  // ck_assert_int_eq(0, result.bits[1]);
  // ck_assert_int_eq(0, result.bits[2]);
  // ck_assert_int_eq(0, result.bits[3]);
  ck_assert_int_eq(val, OP_SMALL);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  my_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000001);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  my_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000001);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x80000000;

  my_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000001);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);

  src1.bits[0] = 0x0000000a;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  my_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x001c0000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x001c0000;

  my_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000001);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x001c0000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00020000;

  src2.bits[0] = 0x00000000;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x001c0000;

  val = my_mod(src1, src2, &result);
  ck_assert_int_eq(val, OP_DIV_ZERO);

  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x001c0000;

  val = my_mod(src1, src2, &result);
  ck_assert_int_eq(val, OP_LARGE);

  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x001c0000;

  val = my_mod(src1, src2, &result);
  ck_assert_int_eq(val, OP_LARGE);

  src1.bits[0] = 0x0000000f;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x001c0000;

  my_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x001b0000);

  src1.bits[0] = 0x00000002;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00030000;

  src2.bits[0] = 0x00000007;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x001c0000;

  my_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000006);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x001c0000);

  src1.bits[0] = 0x0000000a;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000005);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);

  src1.bits[0] = 0x0000000a;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000005);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80000000);

  src1.bits[0] = 0x0000000a;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x80000000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000005);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000023);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00010000);

  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x80000000);
  ck_assert_int_eq(result.bits[3], 0x00000000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00010000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00010000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000023);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00010000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x80000000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000023);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00010000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000023);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x80010000);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000000;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  val = my_div(src1, src2, &result);
  ck_assert_int_eq(val, OP_DIV_ZERO);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00010000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00010000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000023);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00010000);

  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00010000;

  val = my_div(src1, src2, &result);
  ck_assert_int_eq(val, OP_LARGE);

  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0x80000000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00010000;

  val = my_div(src1, src2, &result);
  ck_assert_int_eq(val, OP_LARGE);

  src1.bits[0] = 0x00000007;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00020000;

  src2.bits[0] = 0x00000002;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00010000;

  my_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0x00000023);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

Suite *my_arithmetic_suite() {
  Suite *s = suite_create("arithmetic_suit");
  TCase *tc = tcase_create("arithmetic_test");
  tcase_add_test(tc, arithmetic_check);
  suite_add_tcase(s, tc);
  return s;
}
