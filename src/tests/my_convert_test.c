#include <check.h>
#include <limits.h>

#include "my_decimal_test.h"

START_TEST(convert_check_from_decimal_to_int_01) {
  int result = 0;
  int number = 0;
  my_decimal src = {{0}};

  src.bits[0] = -1;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = my_from_decimal_to_int(src, &number);
  ck_assert_float_eq(number, -1);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(convert_check_from_decimal_to_int_02) {
  int result = 0;
  int number = 0;
  my_decimal src = {{0}};
  src.bits[0] = 133141;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = my_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(convert_check_from_decimal_to_int_03) {
  int result = 0;
  int number = 0;
  my_decimal src = {{0}};
  src.bits[0] = 2147483647;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  src.sign = 1;
  result = my_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(convert_check_from_decimal_to_int_04) {
  int result = 0;
  int number = 0;
  my_decimal src = {{0}};
  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.sign = 1;
  result = my_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(convert_check_from_decimal_to_int_05) {
  int result = 0;
  int number = 0;
  my_decimal src = {{0}};
  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.sign = 1;
  result = my_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(convert_check_from_decimal_to_int_06) {
  int result = 0;
  int number = 0;
  my_decimal src = {{0}};
  src.bits[0] = -1;
  src.bits[1] = -1;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = my_from_decimal_to_int(src, &number);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(convert_check_from_int_to_decimal_01) {
  my_decimal src = {{0}};
  my_from_int_to_decimal(0, &src);
  ck_assert_int_eq(src.bits[0], 0);
  ck_assert_int_eq(src.bits[1], 0);
  ck_assert_int_eq(src.bits[2], 0);
  ck_assert_int_eq(src.bits[3], 0);
}
END_TEST

START_TEST(convert_check_from_int_to_decimal_02) {
  my_decimal src = {{0}};
  my_from_int_to_decimal(-128, &src);
  ck_assert_int_eq(src.bits[0], 128);
  ck_assert_int_eq(src.bits[1], 0);
  ck_assert_int_eq(src.bits[2], 0);
  ck_assert_int_eq(src.sign, 1);
}
END_TEST

START_TEST(convert_check_from_int_to_decimal_03) {
  my_decimal src = {{0}};
  my_from_int_to_decimal(127, &src);
  ck_assert_int_eq(src.bits[0], 127);
  ck_assert_int_eq(src.bits[1], 0);
  ck_assert_int_eq(src.bits[2], 0);
  ck_assert_int_eq(src.bits[3], 0);
}
END_TEST

START_TEST(convert_check_from_int_to_decimal_04) {
  my_decimal src = {{0}};
  my_from_int_to_decimal(-2147483648, &src);
  ck_assert_int_eq(src.bits[0], 2147483648);
  ck_assert_int_eq(src.bits[1], 0);
  ck_assert_int_eq(src.bits[2], 0);
  ck_assert_int_eq(src.sign, 1);
}
END_TEST

START_TEST(convert_check_from_int_to_decimal_05) {
  my_decimal src = {{0}};
  my_from_int_to_decimal(2147483647, &src);
  ck_assert_int_eq(src.bits[0], 2147483647);
  ck_assert_int_eq(src.bits[1], 0);
  ck_assert_int_eq(src.bits[2], 0);
  ck_assert_int_eq(src.bits[3], 0);
}
END_TEST

START_TEST(convert_check_from_int_to_decimal_06) {
  ck_assert_int_eq(my_from_int_to_decimal(2147483647, NULL), 1);
}
END_TEST

START_TEST(convert_check_int_01) {
  my_decimal decimal;
  my_set_zero(&decimal);
  int i = INT32_MAX, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(convert_check_int_02) {
  my_decimal decimal;
  my_set_zero(&decimal);
  int i = INT32_MIN, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(convert_check_int_03) {
  my_decimal decimal;
  my_set_zero(&decimal);
  int i = 0, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(convert_check_int_04) {
  my_decimal decimal;
  my_set_zero(&decimal);
  int i = -123456, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(convert_check_int_05) {
  my_decimal decimal;
  my_set_zero(&decimal);
  int i = 987654, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(convert_check_int_06) {
  my_decimal decimal;
  my_set_zero(&decimal);
  int i = -1, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(convert_check_int_07) {
  my_decimal decimal;
  my_set_zero(&decimal);
  int i = 2, res = 0;
  my_from_int_to_decimal(i, &decimal);
  my_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(convert_check_from_decimal_to_float_01) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  src.bits[0] = 123456;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  src.sign = 1;
  src.exp = 3;
  my_from_decimal_to_float(src, &fl1);
  fl2 = -123.456;
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_from_decimal_to_float_02) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  src.bits[0] = 0;
  src.bits[1] = 1;
  src.bits[2] = 0;
  src.bits[3] = 0;
  src.sign = 0;
  src.exp = 0;
  my_from_decimal_to_float(src, &fl1);
  fl2 = 4294967296;
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_from_decimal_to_float_03) {
  my_decimal src = {{0}};
  float fl1 = 0.0;
  src.bits[0] = 1;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  src.sign = 0;
  src.exp = 30;
  ck_assert_int_eq(my_from_decimal_to_float(src, &fl1), 1);
}
END_TEST

START_TEST(convert_check_from_decimal_to_float_04) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  src.bits[0] = 900000;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  src.sign = 0;
  src.exp = 3;
  my_from_decimal_to_float(src, &fl1);
  fl2 = 900;
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_from_decimal_to_float_05) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  src.bits[0] = 123456789;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  src.sign = 0;
  src.exp = 0;
  my_from_decimal_to_float(src, &fl1);
  fl2 = 123456789;
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_from_decimal_to_float_06) {
  my_decimal src = {{0}};
  src.bits[0] = 123456789;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  src.sign = 0;
  src.exp = 0;
  ck_assert_float_eq(my_from_decimal_to_float(src, NULL), 1);
}
END_TEST

START_TEST(convert_check_float_01) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = -1234.1234;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_02) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = 1234.1234;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_03) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = 0;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_04) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = 1;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_05) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = 12345678;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_06) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = 123456789;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_07) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = 10000000;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_08) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = -0;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_09) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = 0.9099;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_10) {
  my_decimal src = {{0}};
  float fl2 = 0.0;
  float fl1 = 0.0;
  fl1 = 1234.12345678;
  my_from_float_to_decimal(fl1, &src);
  my_from_decimal_to_float(src, &fl2);
  ck_assert_float_eq(fl1, fl2);
}
END_TEST

START_TEST(convert_check_float_12) {
  my_decimal decimal;
  my_set_zero(&decimal);
  float A = 100.5;
  float B = 0.0;
  my_from_float_to_decimal(A, &decimal);
  my_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(convert_check_float_13) {
  my_decimal decimal;
  my_set_zero(&decimal);
  float A = -100.5;
  float B = 0.0;
  my_from_float_to_decimal(A, &decimal);
  my_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(convert_check_float_14) {
  my_decimal decimal;
  my_set_zero(&decimal);
  float A = -1000.201;
  float B = 0.0;
  my_from_float_to_decimal(A, &decimal);
  my_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(convert_check_float_15) {
  my_decimal decimal;
  my_set_zero(&decimal);
  float f = 0.0000000001;
  float res = 0.0;
  my_from_float_to_decimal(f, &decimal);
  my_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(convert_check_float_16) {
  my_decimal decimal;
  my_set_zero(&decimal);
  float f = -3.0;
  float res = 0.0;
  my_from_float_to_decimal(f, &decimal);
  my_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(convert_check_float_17) {
  my_decimal decimal;
  my_set_zero(&decimal);
  float f = 0.0;
  float res = 0.0;
  my_from_float_to_decimal(f, &decimal);
  my_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(convert_check_from_float_to_decimal_01) {
  my_decimal decimal;
  my_set_zero(&decimal);
  float number = 100.5;
  ck_assert_int_eq(1, my_from_float_to_decimal(number, NULL));
}
END_TEST

START_TEST(convert_check_from_float_to_decimal_02) {
  my_decimal decimal;
  my_set_zero(&decimal);
  float number = 7.9342816251e+29;
  ck_assert_int_eq(1, my_from_float_to_decimal(number, &decimal));
}
END_TEST

Suite *my_convert_suite() {
  Suite *s = suite_create("convert_suit");
  TCase *tc = tcase_create("convert_test");

  // decimal to int
  tcase_add_test(tc, convert_check_from_decimal_to_int_01);
  tcase_add_test(tc, convert_check_from_decimal_to_int_02);
  tcase_add_test(tc, convert_check_from_decimal_to_int_03);
  tcase_add_test(tc, convert_check_from_decimal_to_int_04);
  tcase_add_test(tc, convert_check_from_decimal_to_int_05);
  tcase_add_test(tc, convert_check_from_decimal_to_int_06);

  // int to decimal
  tcase_add_test(tc, convert_check_from_int_to_decimal_01);
  tcase_add_test(tc, convert_check_from_int_to_decimal_02);
  tcase_add_test(tc, convert_check_from_int_to_decimal_03);
  tcase_add_test(tc, convert_check_from_int_to_decimal_04);
  tcase_add_test(tc, convert_check_from_int_to_decimal_05);
  tcase_add_test(tc, convert_check_from_int_to_decimal_06);

  // int to decimal and back from decimal to int
  tcase_add_test(tc, convert_check_int_01);
  tcase_add_test(tc, convert_check_int_02);
  tcase_add_test(tc, convert_check_int_03);
  tcase_add_test(tc, convert_check_int_04);
  tcase_add_test(tc, convert_check_int_05);
  tcase_add_test(tc, convert_check_int_06);
  tcase_add_test(tc, convert_check_int_07);

  // decimal to float
  tcase_add_test(tc, convert_check_from_decimal_to_float_01);
  tcase_add_test(tc, convert_check_from_decimal_to_float_02);
  tcase_add_test(tc, convert_check_from_decimal_to_float_03);
  tcase_add_test(tc, convert_check_from_decimal_to_float_04);
  tcase_add_test(tc, convert_check_from_decimal_to_float_05);
  tcase_add_test(tc, convert_check_from_decimal_to_float_06);

  // float to decimal
  tcase_add_test(tc, convert_check_from_float_to_decimal_01);
  tcase_add_test(tc, convert_check_from_float_to_decimal_02);

  // float to decimal and back from decimal to float
  tcase_add_test(tc, convert_check_float_01);
  tcase_add_test(tc, convert_check_float_02);
  tcase_add_test(tc, convert_check_float_03);
  tcase_add_test(tc, convert_check_float_04);
  tcase_add_test(tc, convert_check_float_05);
  tcase_add_test(tc, convert_check_float_06);
  tcase_add_test(tc, convert_check_float_07);
  tcase_add_test(tc, convert_check_float_08);
  tcase_add_test(tc, convert_check_float_09);
  tcase_add_test(tc, convert_check_float_10);
  tcase_add_test(tc, convert_check_float_12);
  tcase_add_test(tc, convert_check_float_13);
  tcase_add_test(tc, convert_check_float_14);
  tcase_add_test(tc, convert_check_float_15);
  tcase_add_test(tc, convert_check_float_16);
  tcase_add_test(tc, convert_check_float_17);

  suite_add_tcase(s, tc);
  return s;
}
