
#include "options.h"


void
print_usage(char* app_name)
{
	printf("Usage:\n%s [options] [file]\n"
			"\nIf file is present then that is the input source\n"
			"Otherwise it is stdin\n"
			"\nPossible options:\n"
			"-c, --chars \t print the byte counts\n"
			"-l, --lines \t print the line counts\n"
			"-w, --words \t print the word counts\n"
			"--help      \t show this message\n", app_name);
}


/* Returns true if @str matches of the options present in @opts
 */

bool
string_is_option(const char* str, int optsc, const char** optsv) 
{

	int i;
	for(i = 0; i < optsc; ++i) {
		if (!strcmp(str, optsv[i]))
			return true;
	}
	return false;
}


/* Parses the command line options provided
 * and stores the results in the @options struct.
 *
 * Returns whether the parsing succeded
 */
bool
parse_options(int argc, const char** argv, struct Options* options)
{
	const char* c_opts[] = {
		"-c",
		"--chars"
	};

	const char* l_opts[] = {
		"-l",
		"--lines"
	};

	const char* w_opts[] = {
		"-w",
		"--words"
	};

	const char* help[] = {
		"--help"
	};

	int i;
	const char* now;
	options->input = stdin;


	for(i = 1; i < argc; ++i) {

		now = argv[i];

		if (now[0] == '-') {
		/*it is an option*/

			if (string_is_option(now, 1, help))
				options->show_help = true;

			else if (string_is_option(now, 2, c_opts))
				options->chars = true;

			else if (string_is_option(now, 2, l_opts))
				options->lines = true;

			else if (string_is_option(now, 2, w_opts))
				options->words = true;

			else {
				printf("Invalid option: %s", now);
				return false;
			}
		} else {
		/* it is a filename */
			
			options->input = fopen(now, "r");

			if (options->input == NULL) {
				perror(argv[0]);
				return false;
			}
		}
	}

	return true;
}

