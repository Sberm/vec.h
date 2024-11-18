TARGETS := test.o vec.o
INCLUDE := -I.

all: vec_test

vec_test: $(TARGETS)
	gcc $(TARGETS) -o $@

vec.o: vec.c vec.h
	gcc -O2 -c $(INCLUDE) $<

test.o: test.c
	gcc -O2 -c $(INCLUDE) $<
