

struct Vector {

	void **data;
	int size;
	int capacity;

};

int Vector_init(struct Vector*);
void Vector_free(struct Vector*);

/* Returns 0 if all went well
 * and -1 in case there was an error
 * (and errno is set appropiatly)
 */
int Vector_add(struct Vector*, void*);
