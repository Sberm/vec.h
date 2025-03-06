## vec.h

A simple vector implementation for c

```c
int *int_v = vec__new(sizeof(int));
int elem1 = 13, elem2 = 14;

// optional, but makes vec__push() faster
vec__reserve(int_v, 3);

vec__push(int_v, elem1);
vec__push(int_v, elem2);
vec__push(int_v, 17); // you can push an rvalue too

// access the element at index 1
int tmp = vec__at(int_v, 1);
printf("second element: %d\n", tmp); /* second element: 14 */

// update the element at index 0
vec__at(int_v, 0) = 23;

// pop the last element
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

To use it in your project, checkout how to build and link to this library in the
`Makefile` script, and `#include "vec.h"` in your project to use all the functions. If
your are stuck, check `test.c` for examples, as it uses `vec.h`; And if things aren't
getting better, please file a GitHub issue describing your problem and include the error
messages, thanks!

Again, check `test.c` and `Makefile` for examples :)

### TODOs

- [x] Crank up the vector size limit (it's already been done before)
