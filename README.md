## vec.h

A simple vector implementation for c

```c
int *int_v = vec__new(sizeof(int));
int elem1 = 13, elem2 = 14, elem3 = 17;

vec__push(int_v, elem1);
vec__push(int_v, elem2);
vec__push(int_v, elem3);

int tmp = vec__at(int_v, 1);
printf("second element: %d\n", tmp); /* second element: 14 */

// update element
vec__at(int_v, 0) = 23;

vec__pop(int_v);

int len = vec__len(int_v);
printf("vector length: %d\n", len); /* vector length: 2 */

vec__free(int_v);
```

### Quick start

**clone the repo**
```bash
git clone https://github.com/Sberm/vec.h.git
```

Run examples
```bash
make
./vec_test -v
```

See `test.c` for examples :)

### TODOs
- [] Crank up the vector size limit
