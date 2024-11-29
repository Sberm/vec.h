#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "vec.h"

#define SMALL_NUM 10

void inline passed(int test_num)
{
	printf("\033[0;32m  Test %d passed\033[0;0m\n", test_num);
}

void inline failed(int test_num)
{
	printf("\033[0;31m  Test %d passed\033[0;0m\n", test_num);
}

#define ASSERT(expr1, expr2, i) if (strcmp((expr1), (expr2)) == 0) passed(i); else failed(i);

void test1(char *buf, size_t len)
{
	int *int_v = vec__new(sizeof(int));
	size_t printed = 0;

	for (int i = 0; i < SMALL_NUM; i++)
		vec__push(int_v, i);

	for (int i = 0; i < SMALL_NUM / 2; i++)
		vec__pop(int_v);

	for (int i = 0; i < vec__len(int_v); i++) {
		printed += snprintf(buf + printed, len - printed, "%d", vec__at(int_v, i));
		printed += snprintf(buf + printed, len - printed, " ");
	}

	if (printed > 0)
		buf[printed - 1] = 0;

	vec__free(int_v);
}

void test2(char *buf, size_t len)
{
	int *int_v = vec__new(sizeof(int));
	size_t printed = 0;

	for (int i = 0; i < 1000; i++)
		vec__push(int_v, i);

	for (int i = 0; i < 1000 + 10; i++)
		vec__pop(int_v);

	for (int i = 0; i < 100; i++)
		vec__push(int_v, i);

	for (int i = 0; i < 50; i++)
		vec__push(int_v, i);

	for (int i = 0; i < vec__len(int_v); i++) {
		printed += snprintf(buf + printed, len - printed, "%d", vec__at(int_v, i));
		printed += snprintf(buf + printed, len - printed, " ");
	}

	if (printed > 0)
		buf[printed - 1] = 0;

	vec__free(int_v);
}

struct inner_struct {
	int a;
	int b;
	float f;
};

struct custom_struct {
	double d1;
	double d2;
	short s1;
	char c[5];
	unsigned long long *p;
	struct inner_struct inner;
};

void test3(char *buf, size_t len)
{
	struct custom_struct *custom_struct_v = vec__new(sizeof(struct custom_struct)), res;
	size_t printed = 0;

	struct custom_struct cstruct = {
		.d1 = 114.514,
		.s1 = 1919,
		.c = { [0] = 'c', [1] = 'u', [2] = 'n', [3] = 't', [4] = 0 },
		.p = NULL,
		.inner = { .a = 1, .b = 2, .f = 114.0f },
	};
	
	for (int i = 0; i < 1000; i++)
		vec__push(custom_struct_v, cstruct);

	for (int i = 0; i < 99; i++)
		vec__pop(custom_struct_v);

	res = vec__at(custom_struct_v, 14);

	printed += snprintf(buf + printed, len - printed, "%.3f %hd %p %s", res.d1, res.s1, res.p, res.c);

	vec__free(custom_struct_v);
}

void test4(char *buf, size_t len, char *str1, char *str2)
{
	char **str_v = vec__new(sizeof(char *));
	size_t printed = 0;

	vec__push(str_v, str1);
	vec__push(str_v, str2);

	printed += snprintf(buf + printed, len - printed, "%s ", vec__at(str_v, 0));
	printed += snprintf(buf + printed, len - printed, "%s", vec__at(str_v, 1));

	vec__free(str_v);
}

void test5(char *buf, size_t len, char *str)
{
	char **str_v = vec__new(sizeof(char *));
	size_t printed = 0;

	vec__push(str_v, str);

	printed += snprintf(buf + printed, len - printed, "%s ", vec__at(str_v, 0));

	vec__free(str_v);
}

void test6(char *buf, size_t len)
{
	double *double_v = vec__new(sizeof(double)), tmp = 114.514;
	size_t printed = 0;

	vec__push(double_v, tmp);
	printed += snprintf(buf + printed, len - printed, "%d ", vec__len(double_v));

	vec__pop(double_v);
	printed += snprintf(buf + printed, len - printed, "%d ", vec__len(double_v));

	vec__pop(double_v);
	printed += snprintf(buf + printed, len - printed, "%d ", vec__len(double_v));

	for (int i = 0; i < 99; ++i)
		vec__push(double_v, tmp);

	printed += snprintf(buf + printed, len - printed, "%d ", vec__len(double_v));

	for (int i = 0; i < 1; ++i)
		vec__pop(double_v);

	for (int i = 0; i < 20; ++i)
		vec__push(double_v, tmp);

	printed += snprintf(buf + printed, len - printed, "%d", vec__len(double_v));

	vec__free(double_v);
}

void test7(char *buf, size_t len)
{
	int *int_v = vec__new(sizeof(int)), to_insert = 10;
	size_t printed = 0;

	vec__push(int_v, to_insert);
	vec__push(int_v, to_insert);
	printed += snprintf(buf + printed, len - printed,"%d ", vec__is_empty(int_v));

	vec__pop(int_v);
	vec__pop(int_v);
	printed += snprintf(buf + printed, len - printed, "%d", vec__is_empty(int_v));

	vec__free(int_v);
}

void test8(char *buf, size_t len)
{
	int *int_v = vec__new(sizeof(int)), to_insert = 10, low = 40000000, high = 50000000, iter;
	size_t printed = 0;

	srand(time(NULL));

	iter = rand() % (low - high) + low;
	for (int i = 0; i < iter; i++) {
		int tmp = rand();
		vec__push(int_v, tmp);
	}

	iter = rand() % (low - high) + low;
	for (int i = 0; i < iter; i++)
		vec__pop(int_v);

	iter = rand() % (low - high) + low;
	for (int i = 0; i < iter; i++)
		vec__len(int_v);

	iter = rand() % (low - high) + low;
	for (int i = 0; i < iter; i++)
		vec__is_empty(int_v);

	iter = abs(rand()) % vec__len(int_v);
	for (int i = 0; i < iter; i++)
		vec__at(int_v, i);

	vec__free(int_v);
}

int main(int argc, char *argv[])
{
	char buf[2048], verbose = 0;
	char str1[] = "cutiepie";
	char str2[] = "Denzel";
	char str3[] = "this test is designed to fail";

	buf[0] = 0;

	if (argc > 1 && 
	    (!strcmp(argv[1], "-V") ||
	     !strcmp(argv[1], "-v") ||
	     !strcmp(argv[1], "--verbose")))
		verbose = 1;

	if (verbose)
		printf("\n");

	test1(buf, sizeof(buf));
	ASSERT(buf, "0 1 2 3 4", 1);
	if (verbose && printf("\n    buf: %s\n\n", buf)) {}

	test2(buf, sizeof(buf));
	ASSERT(buf, "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49", 2);
	if (verbose && printf("\n    buf: %s\n\n", buf)) {}

	test3(buf, sizeof(buf));
	ASSERT(buf, "114.514 1919 0x0 cunt", 3);
	if (verbose && printf("\n    buf: %s\n\n", buf)) {}

	test4(buf, sizeof(buf), str1, str2);
	ASSERT(buf, "cutiepie Denzel", 4);
	if (verbose && printf("\n    buf: %s\n\n", buf)) {}

	test5(buf, sizeof(buf), str3);
	ASSERT(buf, "wrong answer", 5);
	if (verbose && printf("\n    buf: %s\n\n", buf)) {}

	test6(buf, sizeof(buf));
	ASSERT(buf, "1 0 0 99 118", 6);
	if (verbose && printf("\n    buf: %s\n\n", buf)) {}

	test7(buf, sizeof(buf));
	ASSERT(buf, "0 1", 7);
	if (verbose && printf("\n    buf: %s\n\n", buf)) {}

	strcpy(buf, "Randomized test");
	test8(buf, sizeof(buf));
	ASSERT(buf, "Randomized test", 8);
	if (verbose && printf("\n    buf: %s\n\n", buf)) {}

	return 0;
}
