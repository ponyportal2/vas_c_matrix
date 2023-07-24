UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
	SYSFLAG=-D LINUX
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
	LEAK=CK_FORK=no leaks -quiet -atExit --
	SYSFLAG=-D APPLE
endif

CFLAGS=-Wall -Werror -Wextra
GFLAGS=-fprofile-arcs -ftest-coverage

all: vas_matrix.a

vas_matrix.a: clean
	gcc $(SYSFLAG) $(CFLAGS) -c vas_matrix.c
	ar rc vas_matrix.a *.o
	ranlib vas_matrix.a
	rm -f *.o

test: vas_matrix.a
	checkmk clean_mode=1 tests_vas_matrix.check > test_check.c
	gcc $(SYSFLAG) vas_matrix.a test_check.c $(LFLAGS) -g -o test_check
	./test_check

gcov_report: vas_matrix.a
	checkmk clean_mode=1 tests_vas_matrix.check > test_check.c
	gcc $(SYSFLAG) vas_matrix.c test_check.c $(LFLAGS) $(GFLAGS) -g -o test_check
	./test_check > test.log
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -f *.gc* test.info log.xml *.log *.out test_check.c
	rm -f -rf report *.out.dSYM test.dSYM *.input *.output
	rm -rf *.a *.o *.test .test.c *.gcda *.gcno *.info
	rm -rf test test_check test_check.dSYM

cpplinth:
	python3 ../linters/cpplint.py *.h

checkers: vas_matrix.a
	-cppcheck *.c *.h
	clang-format --style=Google -i *.c *.h
	-python3 cpplint.py --extensions=c *.c *.h

style:
	clang-format --style=Google -n *.c *.h

stylef:
	clang-format --style=Google -i *.c *.h

# LOCALTEST:
# ----------

teztleak: vas_matrix.a
	gcc $(SYSFLAG) $(CFLAGS) *.c $(LFLAGS) -g
	-cppcheck *.c *.h
	clang-format --style=Google -i *.c *.h
	-python3 cpplint.py --extensions=c *.c *.h
	-leaks -quiet -atExit -- ./a.out > test.log
	grep -e "0 total leaked bytes" -e "nodes malloced" -e "leaks Report Version" -v test.log

teztleakval: vas_matrix.a
	gcc $(SYSFLAG) $(CFLAGS) *.c $(LFLAGS) -g
	-cppcheck *.c *.h
	clang-format --style=Google -i *.c *.h
	-python3 cpplint.py --extensions=c *.c *.h
	LEAK=CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log" ./a.out

tezt: vas_matrix.a
	gcc $(SYSFLAG) $(CFLAGS) *.c $(LFLAGS) -g
	-cppcheck *.c *.h
	clang-format --style=Google -i *.c *.h
	-python3 cpplint.py --extensions=c *.c *.h
	./a.out

tezd: vas_matrix.a
	gcc $(SYSFLAG) $(CFLAGS) vas_matrix.c vas_matrix_test.c $(LFLAGS) -g
	-cppcheck *.c *.h
	clang-format --style=Google -i *.c *.h
	-python3 cpplint.py --extensions=c *.c *.h
	./a.out

# TESTLEAK:
# ----------
testleak: vas_matrix.a
	checkmk clean_mode=1 tests_vas_matrix.check > test_check.c
	gcc $(SYSFLAG) vas_matrix.a test_check.c $(LFLAGS) -g -o test_check
	-CK_FORK=no leaks -quiet -atExit -- ./test_check > test.log
	grep -e "0 total leaked bytes" -e "nodes malloced" -e "leaks Report Version" -v test.log

testleakval: vas_matrix.a
	checkmk clean_mode=1 tests_vas_matrix.check > test_check.c
	gcc $(SYSFLAG) vas_matrix.a test_check.c $(LFLAGS) -g -o test_check
	-${LEAK} ./test_check