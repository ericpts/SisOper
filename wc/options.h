#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void
print_usage(char* app_name);

struct Options {
	bool bytes;
	bool lines;
	bool words;

	bool show_help;

	const char** files;
	int filec;
};

bool show_bytes(const struct Options options);
bool show_lines(const struct Options options);
bool show_words(const struct Options options);

/* Returns true if @str matches of the options present in @opts
 */

bool string_is_option(const char* str, int optsc, const char** optsv);


/* Parses the command line options provided
 * and stores the results in the @options struct.
 *
 * Returns whether the parsing succeded
 */
bool
parse_options(int argc, const char** argv, struct Options* options);

#endif
