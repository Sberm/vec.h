TARGETS := test.o vec.o
INCLUDE := -I.
CFLAGS := -O2 -Wall -Wextra -Wstrict-overflow=5

all: vec_test

vec_test: $(TARGETS)
	gcc $(CFLAGS) $(TARGETS) -o $@

vec.o: vec.c vec.h
	gcc $(CFLAGS) -c $(INCLUDE) $<

test.o: test.c
	gcc $(CFLAGS) -c $(INCLUDE) $<

clean:
	rm -rf $(TARGETS) vec_test
