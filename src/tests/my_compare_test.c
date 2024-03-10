#include "my_decimal_test.h"

START_TEST(compare_check) {
  my_decimal src1, src2;
  int val;
  // 7 < 15 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 15 < 7 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 15;
  my_set_zero(&src2);
  src2.bits[0] = 7;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // -7 < 15 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.sign = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // -15 < -7 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 15;
  src1.sign = 1;
  my_set_zero(&src2);
  src2.bits[0] = 7;
  src2.sign = 1;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 0.7 < -0.15 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.exp = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  src2.exp = 2;
  src2.sign = 1;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // -0.7 < 0.15 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.exp = 0;
  src1.sign = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  src2.exp = 2;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 0 < 6 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 0;
  my_set_zero(&src2);
  src2.bits[0] = 6;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 79228162514264337593543950335 < 79228162514264337593543950335 = FALSE
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;
  src2.bits[0] = 0xffffffff;
  src2.bits[1] = 0xffffffff;
  src2.bits[2] = 0xffffffff;
  src2.bits[3] = 0;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 7 > 15 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  val = my_is_greater(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 15 > 7 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 15;
  my_set_zero(&src2);
  src2.bits[0] = 7;
  val = my_is_greater(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // -15 > 7 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.sign = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  val = my_is_greater(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // -15 > -7 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 15;
  src1.sign = 1;
  my_set_zero(&src2);
  src2.bits[0] = 7;
  src2.sign = 1;
  val = my_is_greater(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 0.7 > 0.15 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.exp = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  src2.exp = 2;
  val = my_is_greater(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // -0.7 > 0.15 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.sign = 1;
  src1.exp = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  src2.exp = 2;
  src2.sign = 1;
  val = my_is_greater(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 0 > 6 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 0;
  my_set_zero(&src2);
  src2.bits[0] = 6;
  val = my_is_greater(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 79228162514264337593543950335 > 79228162514264337593543950335 = FALSE
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;
  src2.bits[0] = 0xffffffff;
  src2.bits[1] = 0xffffffff;
  src2.bits[2] = 0xffffffff;
  src2.bits[3] = 0;
  val = my_is_greater(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 0.7 == 0.15 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.exp = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  src2.exp = 2;
  val = my_is_equal(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 0 == 6 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 0;
  my_set_zero(&src2);
  src2.bits[0] = 6;
  val = my_is_equal(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 79228162514264337593543950335 == 79228162514264337593543950335 = TRUE
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;
  src2.bits[0] = 0xffffffff;
  src2.bits[1] = 0xffffffff;
  src2.bits[2] = 0xffffffff;
  src2.bits[3] = 0;
  val = my_is_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // -8 == 8 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 8;
  src1.sign = 1;
  my_set_zero(&src2);
  src2.bits[0] = 8;
  val = my_is_equal(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // -0 == 0 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 0;
  src1.sign = 1;
  my_set_zero(&src2);
  src2.bits[0] = 0;
  val = my_is_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // -1 == 0 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 1;
  src1.sign = 1;
  my_set_zero(&src2);
  src2.bits[0] = 0;
  val = my_is_equal(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 0.7 != 0.15 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.exp = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  src2.exp = 2;
  val = my_is_not_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 0 != 6 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 0;
  my_set_zero(&src2);
  src2.bits[0] = 6;
  val = my_is_not_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 79228162514264337593543950335 != 79228162514264337593543950335 = FALSE
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;
  src2.bits[0] = 0xffffffff;
  src2.bits[1] = 0xffffffff;
  src2.bits[2] = 0xffffffff;
  src2.bits[3] = 0;
  val = my_is_not_equal(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 0.7 <= 0.15 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 7;
  src1.exp = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  src2.exp = 2;
  val = my_is_less_or_equal(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 0 <= 6 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 0;
  my_set_zero(&src2);
  src2.bits[0] = 6;
  val = my_is_less_or_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 79228162514264337593543950335 <= 79228162514264337593543950335 = TRUE
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;
  src2.bits[0] = 0xffffffff;
  src2.bits[1] = 0xffffffff;
  src2.bits[2] = 0xffffffff;
  src2.bits[3] = 0;
  val = my_is_less_or_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 0.15 >= 0.15 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 15;
  src1.exp = 1;
  my_set_zero(&src2);
  src2.bits[0] = 15;
  src2.exp = 1;
  val = my_is_greater_or_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 0 >= 6 = FALSE
  my_set_zero(&src1);
  src1.bits[0] = 0;
  my_set_zero(&src2);
  src2.bits[0] = 6;
  val = my_is_greater_or_equal(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // 79228162514264337593543950335 >= 79228162514264337593543950335 = TRUE
  src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0xffffffff;
  src1.bits[3] = 0;
  src2.bits[0] = 0xffffffff;
  src2.bits[1] = 0xffffffff;
  src2.bits[2] = 0xffffffff;
  src2.bits[3] = 0;
  val = my_is_greater_or_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 1.37 < 1.395 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 137;
  src1.exp = 2;
  my_set_zero(&src2);
  src2.bits[0] = 1395;
  src2.exp = 3;
  val = my_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 15 == 15 = TRUE
  my_set_zero(&src1);
  src1.bits[0] = 15;
  my_set_zero(&src2);
  src2.bits[0] = 15000;
  src2.exp = 3;
  val = my_is_equal(src1, src2);
  ck_assert_int_eq(val, TRUE);
}
END_TEST

Suite *my_compare_suite() {
  Suite *s = suite_create("compare_suit");
  TCase *tc = tcase_create("compare_test");
  tcase_add_test(tc, compare_check);
  suite_add_tcase(s, tc);
  return s;
}
