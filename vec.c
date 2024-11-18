#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define DEFAULT_VEC_SIZE 16

struct vec {
	size_t len; /* number of members */
	size_t mem_size;
	size_t capacity; /* in bytes */
	char *raw;
};

void *vec__new(size_t mem_size)
{
	struct vec *vec = malloc(sizeof(struct vec));

	if (vec == NULL)
		return NULL;

	vec->raw = malloc(DEFAULT_VEC_SIZE);
	if (vec->raw == NULL)
		return NULL;

	vec->len = 0;
	vec->mem_size = mem_size;
	vec->capacity = DEFAULT_VEC_SIZE;

	return vec;
}

void vec__free(void *__vec)
{
	struct vec *vec = __vec;

	free(vec->raw);
	free(vec);
}

int __vec__expand(struct vec *vec, size_t new_size)
{
	size_t capacity = vec->capacity;
	void *__new;

	while (capacity < new_size)
		capacity <<= 1;

	__new = realloc(vec->raw, capacity);
	if (__new == NULL)
		return -1;

	vec->raw = __new;
	vec->capacity = capacity;

	return 0;
}

int __vec__push(void *__vec, void *elem, size_t elem_size)
{
	struct vec *vec = __vec;
	size_t new_size;

	assert(vec->mem_size == elem_size);
	new_size = vec->len * vec->mem_size + elem_size;

	if (new_size > vec->capacity && __vec__expand(vec, new_size)) {
		return -1;
	}
		
	memcpy(vec->raw + vec->len * vec->mem_size, elem, elem_size);
	++vec->len;
	
	return 0;
}

void vec__pop(void *__vec)
{
	struct vec *vec = __vec;

	if (vec->len > 0)
		--vec->len;
}

void *__vec__at(void *__vec, size_t pos)
{
	struct vec *vec = __vec;

	return vec->raw + pos * vec->mem_size;
}

size_t vec__len(void *__vec)
{
	struct vec *vec = __vec;

	return vec->len;
}
