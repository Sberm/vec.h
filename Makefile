TARGETS := test.o vec.o
INCLUDE := -I.

all: vec_test

vec_test: $(TARGETS)
	gcc $(TARGETS) -o $@

%.o: %.c
	gcc -O2 -c $(INCLUDE) $^
