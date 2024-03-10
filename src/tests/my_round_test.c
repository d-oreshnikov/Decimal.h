#include "my_decimal_test.h"

START_TEST(round_check) {
  my_decimal src1, result;
  int val;
  src1.bits[0] = 123456;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x00030000;
  val = my_truncate(src1, &result);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 87654;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80040000;
  val = my_truncate(src1, &result);
  ck_assert_int_eq(result.bits[0], 8);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 87654;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80050000;
  val = my_truncate(src1, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 5912;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 3;
  val = my_truncate(src1, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 23;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x001F0000;
  val = my_truncate(src1, &result);
  ck_assert_int_eq(val, CONVERTERROR);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  src1.bits[0] = 23;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x001F0000;
  val = my_floor(src1, &result);
  ck_assert_int_eq(val, CONVERTERROR);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  src1.bits[0] = 0;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;

  val = my_floor(src1, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 125;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 2;

  val = my_floor(src1, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 15;
  src1.bits[1] = 1;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 2;

  val = my_floor(src1, &result);
  ck_assert_int_eq(result.bits[0], 42949673);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 256;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 2;
  src1.sign = 1;
  uint32_t expb = 1;
  expb = expb << 31;
  val = my_floor(src1, &result);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], expb);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 5;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.sign = 1;
  val = my_floor(src1, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], expb);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 5151;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 2;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 52);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 5500;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 3;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 6);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 591;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 59);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 5;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 54;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 1;
  src1.sign = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], expb);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 54558;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 3;
  src1.sign = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 55);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], expb);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 145;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 1;
  src1.sign = 0;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 14);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.exp, 0);
  ck_assert_int_eq(result.sign, 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 155;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 1;
  src1.sign = 0;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 16);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.exp, 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 1450;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 2;
  src1.sign = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 14);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.exp, 0);
  ck_assert_int_eq(result.sign, 1);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 1350;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 2;
  src1.sign = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 14);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.exp, 0);
  ck_assert_int_eq(result.sign, 1);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 1350;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 2;
  src1.sign = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 14);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.exp, 0);
  ck_assert_int_eq(result.sign, 1);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 155;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 1;
  src1.sign = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 16);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.exp, 0);
  ck_assert_int_eq(result.sign, 1);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 155000;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.exp = 4;
  src1.sign = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 16);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.exp, 0);
  ck_assert_int_eq(result.sign, 1);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 0;
  src1.bits[1] = 0;
  src1.bits[2] = 1;
  src1.bits[3] = 0;
  src1.sign = 1;
  val = my_round(src1, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 1);
  ck_assert_int_eq(result.bits[3], expb);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 100;
  src1.bits[1] = 1;
  src1.bits[2] = 23;
  src1.bits[3] = 0;
  src1.sign = 1;
  val = my_negate(src1, &result);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(result.bits[1], 1);
  ck_assert_int_eq(result.bits[2], 23);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 100;
  src1.bits[1] = 1;
  src1.bits[2] = 23;
  src1.bits[3] = 0;
  src1.sign = 0;
  val = my_negate(src1, &result);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(result.bits[1], 1);
  ck_assert_int_eq(result.bits[2], 23);
  ck_assert_int_eq(result.bits[3], expb);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 0;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src1.sign = 0;
  val = my_negate(src1, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], expb);
  ck_assert_int_eq(val, CONVERTOK);

  src1.bits[0] = 4294967295;
  src1.bits[1] = 4294967295;
  src1.bits[2] = 4294967295;
  src1.bits[3] = 0;
  src1.exp = 10;
  src1.sign = 0;
  val = my_negate(src1, &result);
  ck_assert_int_eq(result.bits[0], 4294967295);
  ck_assert_int_eq(result.bits[1], 4294967295);
  ck_assert_int_eq(result.bits[2], 4294967295);
  ck_assert_int_eq(result.bits[3], expb + (10 << 16));
  ck_assert_int_eq(val, CONVERTOK);
}
END_TEST

Suite *my_round_suite() {
  Suite *s = suite_create("round_suit");
  TCase *tc = tcase_create("round_test");
  tcase_add_test(tc, round_check);
  suite_add_tcase(s, tc);
  return s;
}
