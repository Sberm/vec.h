#ifndef VEC_H
#define VEC_H

#include <stddef.h>

void *vec__new(size_t mem_size);
void vec__free(void *__vec);
void vec__pop(void *__vec);
size_t vec__len(void *__vec);

int __vec__push(void *__vec, void *elem, size_t elem_size);
#define vec__push(vec, elem) __vec__push((vec), &(elem), sizeof(*(typeof(vec))0))

void *__vec__at(void *vec, size_t pos);
#define vec__at(vec, pos) *(typeof((vec)))__vec__at((vec), (pos))

#endif
