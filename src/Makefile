CC=g++
CC_FLAGS=-Wall -Wextra -Werror -std=c++17
test_flags=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
# VALGRIND_FLAGS=--leak-check=full

ifeq ($(OS), Linux)
	test_libs=-lgtest -lgmock -pthread
	open=xdg-open
else
	test_libs=-lcheck
	open=open
endif

all: s21_matrix_oop.a gcov_report

s21_matrix_oop.a:
		rm -f *.a
		$(CC) $(CC_FLAGS) -c s21_matrix_oop.cpp
		ar rc s21_matrix_oop.a *.o
		ranlib s21_matrix_oop.a
		rm -f *.o

test:
	rm -f *.txt
	$(CC) $(CC_FLAGS) $(test_flags) *.cpp -o test $(test_libs)
	./test

gcov_report: test
		lcov -t "test" -o $(tests_info)test.info -c -d .
		genhtml -o report $(tests_info)test.info
		$(open) report/index.html

clean:
	rm -f test
	rm -f *.o
	rm -f */*.gcda
	rm -f */*.gcno
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
	rm -f *.a
	rm -fr ./report/*
	rmdir ./report

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cpp *.h
	rm -f .clang-format

valgrind:
	$(CC) $(CC_FLAGS) $(test_flags) *.cpp -o test $(test_libs)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./test