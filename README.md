## vec.h

A simple vector implementation for c

```c
int *int_v = vec__new(sizeof(int));
int elem1 = 13, elem2 = 14, elem3 = 17;

vec__push(int_v, elem1);
vec__push(int_v, elem2);
vec__push(int_v, elem3);

/* second element: 14 */
int tmp = vec__at(int_v, 1);
printf("second element: %d\n", tmp);

vec__pop(int_v);

/* vector length: 2 */
int len = vec__len(int_v);
printf("vector length: %d\n", len);

vec__free(int_v);
```

### Quick start

**clone the repo**
```bash
git clone $
```

Run examples
```bash
make
./vec_test -v
```

See `test.c` for examples :)
