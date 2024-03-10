#include "my_decimal_test.h"

int main() {
  int fc = 1;
  runTest(my_convert_suite(), &fc);
  runTest(my_arithmetic_suite(), &fc);
  runTest(my_compare_suite(), &fc);
  runTest(my_round_suite(), &fc);

  return fc;
}

void runTest(Suite *suit, int *fc) {
  SRunner *sr = srunner_create(suit);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  int f = srunner_ntests_failed(sr);
  if (*fc != 0) {
    *fc = f;
  }
  srunner_free(sr);
}
