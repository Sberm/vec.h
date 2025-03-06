#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "vec.h"

#define SMALL_NUM 10

void passed(int test_num)
{
	printf("\033[0;32m  Test %d passed\033[0;0m\n", test_num);
}

void failed(int test_num)
{
	printf("\033[0;31m  Test %d failed\033[0;0m\n", test_num);
}

#define ASSERT(expr1, expr2, i) if (strcmp((expr1), (expr2)) == 0) passed(i); else failed(i);
#define ASSERT_EITHER(expr1, expr2, expr3, i) if ((strcmp((expr1), (expr2)) & (strcmp((expr1), (expr3)))) == 0) passed(i); else failed(i);

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

void test8(void)
{
	int *int_v = vec__new(sizeof(int)), low = 40000000, high = 50000000, iter = 0;

	srand(time(NULL));
	iter = rand() % (high - low) + low;
	// volatile: avoid overflow warnings
	for (volatile int i = 0; i < iter; i++) {
		int tmp = rand();
		vec__push(int_v, tmp);
	}

	iter = rand() % (high - low) + low;
	for (volatile int i = 0; i < iter; i++)
		vec__pop(int_v);

	iter = rand() % (high - low) + low;
	for (volatile int i = 0; i < iter; i++)
		vec__len(int_v);

	iter = rand() % (high - low) + low;
	for (volatile int i = 0; i < iter; i++)
		vec__is_empty(int_v);

	int foo;
	if (vec__len(int_v) > 0) {
		iter = rand() % vec__len(int_v);
		for (volatile int i = 0; i < iter; i++) {
			foo = vec__at(int_v, i);
			foo = foo + 1; // to avoid warnings
		}
	}

	vec__free(int_v);
}

void test9(char *buf, size_t len)
{
	double *double_v = vec__new(sizeof(double));
	size_t printed = 0;

	vec__push(double_v, 114.514);
	vec__push(double_v, 1919.81);

	printed += snprintf(buf + printed, len - printed, "%.3f ", vec__at(double_v, 0));
	printed += snprintf(buf + printed, len - printed, "%.3f", vec__at(double_v, 1));

	vec__free(double_v);
}

void test10(char *buf, size_t len)
{
	short *short_v = vec__new(sizeof(short)), elem1 = 114, elem2 = 514;
	size_t printed = 0;

	vec__pushp(short_v, &elem1);
	vec__pushp(short_v, &elem2);

	printed += snprintf(buf + printed, len - printed, "%hd ", vec__at(short_v, 0));
	printed += snprintf(buf + printed, len - printed, "%hd", vec__at(short_v, 1));

	vec__free(short_v);
}

// vector modification test
void test11(char *buf, size_t len)
{
	size_t printed = 0;
	int *int_v = vec__new(sizeof(int));
	struct custom_struct *custom_struct_v = vec__new(sizeof(struct custom_struct));
	struct custom_struct *tmp, elem;

	vec__push(int_v, 10);
	vec__at(int_v, 0) = 11;
	printed += snprintf(buf + printed, len - printed, "%d ", vec__at(int_v, 0));

	struct custom_struct cstruct = {
		.d1 = 114.514,
		.s1 = 1919,
		.c = { [0] = 'c', [1] = 'u', [2] = 'n', [3] = 't', [4] = 0 },
		.p = NULL,
		.inner = { .a = 1, .b = 2, .f = 114.0f },
	};

	vec__push(custom_struct_v, cstruct);
	tmp = &vec__at(custom_struct_v, 0);
	tmp->d1 = 1.4;
	tmp->s1 = 69;
	tmp->c[0] = 'f', tmp->c[1] = 'o', tmp->c[2] = 'o', tmp->c[3] = 0;
	tmp->inner.b = 50;

	elem = vec__at(custom_struct_v, 0);
	printed += snprintf(buf + printed, len - printed, "%.3f %hd %s %d", elem.d1, elem.s1, elem.c, elem.inner.b);

	vec__free(int_v);
	vec__free(custom_struct_v);
}

// reservation test
void test12(char *buf, size_t len)
{
	size_t printed = 0;
	int *int_vector = vec__new(sizeof(int));

	if (vec__reserve(int_vector, 100)) {
		printed += snprintf(buf + printed, len - printed, "Reservation failed");
		return;
	}

	printed += snprintf(buf + printed, len - printed, "len %d capacity %d",
			    vec__len(int_vector), (int)vec__cap(int_vector));
	vec__free(int_vector);
}

int main(int argc, char *argv[])
{
	char buf[2048], verbose = 0;

	buf[0] = 0;

	if (argc > 1 && 
	    (!strcmp(argv[1], "-V") ||
	     !strcmp(argv[1], "-v") ||
	     !strcmp(argv[1], "--verbose")))
		verbose = 1;

	if (verbose)
		printf("\n");

	char *ans1 = "0 1 2 3 4";
	test1(buf, sizeof(buf));
	ASSERT(buf, ans1, 1);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans1)) {}

	char *ans2 = "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49";
	test2(buf, sizeof(buf));
	ASSERT(buf, ans2, 2);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans2)) {}

	char *ans3_1 = "114.514 1919 0x0 cunt", *ans3_2 = "114.514 1919 (nil) cunt";
	test3(buf, sizeof(buf));
	ASSERT_EITHER(buf, ans3_1, ans3_2, 3); // clang: 0x0, gcc: (nil)
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s or %s\n\n", buf, ans3_1, ans3_2)) {}

	char *ans4 = "cutiepie Denzel";
	test4(buf, sizeof(buf), "cutiepie", "Denzel");
	ASSERT(buf, ans4, 4);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans4)) {}

	char *ans5 = "wrong answer";
	test5(buf, sizeof(buf), "this test is designed to fail");
	ASSERT(buf, ans5, 5);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans5)) {}

	char *ans6 = "1 0 0 99 118";
	test6(buf, sizeof(buf));
	ASSERT(buf, ans6, 6);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans6)) {}

	char *ans7 = "0 1";
	test7(buf, sizeof(buf));
	ASSERT(buf, ans7, 7);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans7)) {}

	char *ans8 = "Randomized test";
	strcpy(buf, ans8);
	test8();
	ASSERT(buf, ans8, 8);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans8)) {}

	char *ans9 = "114.514 1919.810";
	test9(buf, sizeof(buf));
	ASSERT(buf, ans9, 9);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans9)) {}

	char *ans10 = "114 514";
	test10(buf, sizeof(buf));
	ASSERT(buf, ans10, 10);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans10)) {}

	char *ans11 = "11 1.400 69 foo 50";
	test11(buf, sizeof(buf));
	ASSERT(buf, ans11, 11);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans11)) {}

	// 128 * sizeof(int)
	char *ans12 = "len 0 capacity 512";
	test12(buf, sizeof(buf));
	ASSERT(buf, ans12, 12);
	if (verbose && printf("\n    output:          %s\n    supposed-to-be:  %s\n\n", buf, ans12)) {}

	return 0;
}
