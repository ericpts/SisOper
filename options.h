#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void
print_usage(char* app_name);

struct Options {
	bool chars;
	bool lines;
	bool words;

	bool show_help;

	FILE* input;
};

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
