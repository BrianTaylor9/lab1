#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int fds[2];
	pipe(fds);
	// int ret = fork();
	// if (ret == 0) {

	// }
	dup2(fd[1], STDOUT_FILENO);
	system(argv[1]);
	dup2(fd[0], STDIN_FILENO);
	system(argv[2]);
	return 0;
}
