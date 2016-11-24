#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

static int Vector_grow(struct Vector* vector)
{
	assert(vector->size == vector->capacity);

	int new_capacity = vector->capacity * 2;

	void** new_data = (void **)malloc((sizeof (void*)) * new_capacity);
	
	if (new_data == NULL)
		return -1;

	memcpy(new_data, vector->data, sizeof(void*) * vector->capacity);

	free(vector->data);
	vector->data = new_data;
	vector->capacity = new_capacity;

	return 0;
}

int Vector_init(struct Vector* vector)
{
	vector->size = 0;
	vector->capacity = 4;
	vector->data = (void **) malloc((sizeof (void*)) * vector->capacity);

	if (vector->data == NULL) 
		return -1;

	return 0;
}
void Vector_free(struct Vector* vector)
{
	free(vector->data);
	vector->capacity = vector->size = 0;
}

int Vector_add(struct Vector* vector, void* item)
{
	if (vector->size == vector->capacity) {
		if (Vector_grow(vector) == -1)
			return -1;
	}

	vector->data[vector->size] = item;
	vector->size++;

	return 0;
}
