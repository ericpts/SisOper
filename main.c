#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "options.h"

int main(int argc, char** argv)
{

	struct Options options;

	memset(&options, 0x00, sizeof(options));

	if (!parse_options(argc, (const char**)argv, &options) || options.show_help) {
		print_usage(argv[0]);
		return 0;
	}


	return 0;
}
