#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

#include "vector.h"

int print_usage(const char* prog)
{
	printf("Usage: %s Dir1 Dir2\n", prog);
	return 0;
}

int read_directory(const char* const dirname, struct Vector* const vector)
{
	//fprintf(stderr, "reading from directory %s\n", dirname);
	DIR *dir = opendir(dirname);
	if (dir == NULL) {
		int error = errno;
		printf("Error opening directory %s: %s\n", dirname, strerror(error));
		return -1;
	}

	struct dirent* ent;

	int error = 0;

	while (true) {

		errno = 0;
		ent = readdir(dir);
		error = errno;

		if (ent == NULL)
			break;

		if (strcmp(ent->d_name, "..") == 0)
			continue;

		if (strcmp(ent->d_name, ".") == 0)
			continue;

		int n = strlen(dirname) + 1 + strlen(ent->d_name) + 1;
		char* fname = (char*) malloc(n);
		if (fname == NULL) {
			perror(NULL);
			return -4;
		}

		{
			int ret = snprintf(fname, n, "%s/%s", dirname, ent->d_name);
			if (ret < 0) {
				perror("Error in snprintf");
				free(fname);
				return -5;
			}
		}

		struct stat buf;
		{
			int ret = stat(fname, &buf);

			if (ret == -1) {
				int error = errno;
				printf("Error reading stats for %s: %s\n", fname, strerror(error));
				free(fname);
				return -3;
			}
		}

		/* append the file to the vector */
		if (S_ISREG(buf.st_mode)) {

			if (Vector_add(vector, fname) < 0) {
				perror("Error in adding to vector");
				free(fname);
				return -6;
			}
			/* recurse down */
		} else if (S_ISDIR(buf.st_mode)) {
			read_directory(fname, vector);
		}
	}

	if (error) {
		printf("Error in reading directory %s: %s\n", dirname, strerror(error));
		return -2;
	}

	return 0;
}

void print_diff(struct Vector* v1, struct Vector* v2)
{
	for(int i = 0; i < v1->size; ++i) {
		bool found = false;
		for(int j = 0; j < v2->size; ++j) {
			if (strcmp((char*)v1->data[i], (char*)v2->data[j]) == 0)
				found = true;
		}
		if (!found)
			printf("%s\n", (char*)v1->data[i]);
	}
}

void dealloc_vector(struct Vector* v)
{
	for(int i = 0; i < v->size; ++i)
	{
		free(v->data[i]);
	}
	Vector_free(v);
}

int main(int argc, char** argv)
{
	if (argc != 3) {
		print_usage(argv[0]);
	}

	struct Vector v1;
	if (Vector_init(&v1)) {
		perror("Error initializing vector1");
		return -100;
	}
	
	{
		int ret = read_directory(argv[1], &v1);
		if (ret < 0) {
			printf("Errored while processing directory %s\nExiting...\n", argv[1]);
			dealloc_vector(&v1);
			return ret;
		}
	}

	struct Vector v2;
	if (Vector_init(&v2)) {
		perror("Error initializing vector2");
		dealloc_vector(&v1);
		return -101;
	}
	
	{
		int ret = read_directory(argv[2], &v2);
		if (ret < 0) {
			dealloc_vector(&v1);
			dealloc_vector(&v2);
			printf("Erorred while processing directory %s\nExiting...\n", argv[2]);
			return ret;
		}
	}

	printf("Files only found in %s:\n", argv[1]);
	print_diff(&v1, &v2);
	printf("=============================\n");

	printf("Files only found in %s:\n", argv[2]);
	print_diff(&v2, &v1);
	printf("=============================\n");

	dealloc_vector(&v1);
	dealloc_vector(&v2);

	return 0;
}
