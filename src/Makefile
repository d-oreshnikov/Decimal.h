CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g
LDFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage

all: my_decimal.a

my_decimal.a:
	$(CC) $(CFLAGS) -c convert_func/*.c arithmetic_func/*.c compar_func/*.c round_func/*.c help_func/*.c
	ar rc my_decimal.a *.o
	ranlib my_decimal.a

test:
	$(CC) $(CFLAGS) $(LDFLAGS) convert_func/*.c arithmetic_func/*.c compar_func/*.c round_func/*.c help_func/*.c tests/*.c -lm `pkg-config --cflags --libs check`
	./a.out
	rm a.out

gcov_report:
	$(CC) $(CFLAGS) $(LDFLAGS) $(GCOVFLAGS) convert_func/*.c arithmetic_func/*.c compar_func/*.c round_func/*.c help_func/*.c tests/*.c -o gcov_main -lm `pkg-config --cflags --libs check`
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt gcov*

style_check:
	clang-format -style=Google -n *.h
	clang-format -style=Google -n */*.c */*.h

cpk:
	cppcheck *.[h]
	cppcheck */*.[ch]

rebuild: clean all
