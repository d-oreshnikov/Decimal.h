#include <check.h>
#include <limits.h>

#include "../my_decimal.h"

Suite *my_convert_suite();
Suite *my_arithmetic_suite();
Suite *my_compare_suite();
Suite *my_round_suite();

void runTest(Suite *suit, int *fc);
