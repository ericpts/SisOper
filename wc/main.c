#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "options.h"

struct Results {
	int words;
	int bytes;
	int lines;
};

/* Parses @fd and stores the @results
 *
 * Returns -1 if there was an error (and errno is set appropiatly)
 * or the total number of characters processed
 */
int parse_file(int fd, struct Results *results) 
{
	enum {
		inWord,
		inSpace
	} word_state = inSpace;

	unsigned char buff[BUFSIZ];

	memset(results, 0x00, sizeof(struct Results));

	int total = 0;

	ssize_t cnt;

	while ((cnt = read(fd, buff, BUFSIZ)) != 0) 
	{
		if (cnt == -1)
			return -1;

		total += cnt;

		for(int i = 0; i < cnt; ++i) 
		{
			unsigned char c = buff[i];

			results->bytes++;

			if (c == '\n')
				results->lines++;

			if (isspace(c)) {

				if (word_state == inWord)
					results->words++;

				word_state = inSpace;
			} else {

				word_state = inWord;
			}
		}
	}

	/* Handle the special case when the file
	 * ends with an word
	 */
	if (word_state == inWord)
		results->words++;

	return total;
}


void show_results(const struct Results results, const struct Options options)
{
	if (show_lines(options))
		printf("%d ", results.lines);

	if (show_words(options))
		printf("%d ", results.words);

	if (show_bytes(options))
		printf("%d ", results.bytes);
}

int main(int argc, char** argv)
{
	struct Options options;

	if (!parse_options(argc, (const char**)argv, &options) || options.show_help) {
		print_usage(argv[0]);
		return 0;
	}

	if (options.filec == 0) {
	/* stdin */

		struct Results results;
		int ret = parse_file(0, &results);

		if (ret == -1)  {
			printf("%s: Error reading from stdin\n", argv[0]);
		} else {
			show_results(results, options);
			printf("\n");
		}
		
	} else {

		struct Results total;
		memset(&total, 0x00, sizeof(total));

		int i;
		for (i = 0; i < options.filec; ++i) {
			const char* fname = options.files[i];

			int fd = open(fname, O_RDONLY);

			if (fd == -1) {
				int error = errno;
				printf("Error opening %s: %s\n", fname, strerror(error));
				continue;
			}

			struct Results results;
			int ret = parse_file(fd, &results);

			if (ret == -1) {
				int error = errno;
				printf("Error reading from %s: %s\n", fname, strerror(error));
				continue;

			}

			show_results(results, options);

			printf("%s\n", fname);

			total.lines += results.lines;
			total.words += results.words;
			total.bytes += results.bytes;

			if (close(fd) == -1) {
				int error = errno;
				printf("Error closing %s: %s\n", fname, strerror(error));
			}
		}

		if (options.filec > 1) {
			show_results(total, options);
			printf("total\n");
		}

	}


	return 0;
}
