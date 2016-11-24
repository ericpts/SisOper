
#include "options.h"


void
print_usage(char* app_name)
{
	printf("Usage:\n%s [options] [files]\n"
			"\nIf any files is present then those are the input source\n"
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
		"--bytes"
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

	int i = 1;
	const char* now;
	int files_start = argc;

	memset(options, 0x00, sizeof(struct Options));

	while(i < files_start) {

		now = argv[i];

		if (now[0] == '-') {
		/*it is an option*/

			if (string_is_option(now, 1, help))
				options->show_help = true;

			else if (string_is_option(now, 2, c_opts))
				options->bytes = true;

			else if (string_is_option(now, 2, l_opts))
				options->lines = true;

			else if (string_is_option(now, 2, w_opts))
				options->words = true;

			else {
				printf("Invalid option: %s", now);
				return false;
			}

			i++;
		} else {
		/* it is a filename */
			files_start--;
			argv[i] = argv[files_start];
			argv[files_start] = now;
		}
	}

	options->files = argv + files_start;
	options->filec = argc - files_start;

	return true;
}


#define def_show_fun(field) \
	bool show_##field(const struct Options options) {\
		return options.field == true ||\
		(!options.bytes && !options.lines && !options.words);\
	}

def_show_fun(bytes)
def_show_fun(lines)
def_show_fun(words)

#undef def_show_fn

