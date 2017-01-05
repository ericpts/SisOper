#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void print_usage(char* prog_name)
{
	printf("Usage: %s p1 p2 [pn...]\n", prog_name);
}

int main(int argc, char** argv)
{
	if (argc < 3) 
	{
		print_usage(argv[0]);
		return -1;
	}

	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	const int cpid = fork();

	if (cpid == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) 
		//child
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		if (argc == 3)
		/* base case */ 
		{
			execl(argv[2], argv[2], NULL);
		}
		else
		{
			//overwrite p1 with prog's name
			argv[1] = argv[0];
			execv(argv[1], argv + 1);
		}
	} 
	else
		//parent
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		execl(argv[1], NULL);
	}

	
	return 0;
}
