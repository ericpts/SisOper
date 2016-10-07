#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

struct Options {
	bool chars;
	bool lines;
	bool words;

	bool show_help;

	FILE* input;
};

bool string_is_option(const char* str, const char* opts[], int opts_c) {
	int i;
	for(i = 0; i < opts_c; ++i) {
		if (!strcmp(str, opts[i]))
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
	int cmp_res;

	for(i = 1; i < argc; ++i) {

		const char* now = argv[i];

		if (now[0] == '-') {
		/*it is an option*/

			if (string_is_option(now, help, 1))
				options->show_help = true;

			else if (string_is_option(now, c_opts, 2))
				options->chars = true;

			else if (string_is_option(now, l_opts, 2))
				options->lines = true;

			else if (string_is_option(now, w_opts, 2))
				options->words = true;

			else {
				printf("Invalid option: %s", now);
				return false;
			}
			

		
		}


	}
}

int main(int argc, char** argv)
{

	struct Options options;

	memset(&options, 0x00, sizeof(options));

	if (!parse_options(argc, (const char**)argv, &options) || options.show_help) {
		print_usage(argv[0]);
		return 0;
	}

}
