#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int saved_stdout = dup(1);
    int fds[2];
	int i;
	if (argc == 1) { // no arguments
		errno = EINVAL;
		return -1;
	}
	for (i = 1; i < argc - 1; i++) {
    	pipe(fds);
    	int ret = fork();

		// child process
    	if (ret == 0) {
        	dup2(fds[1], 1); // directs output to write-end of pipe
			if (execlp(argv[i], argv[i], (char *)NULL) == -1) {
				perror(argv[i]);
				return -1;
			}
        	exit(0);
    	}

		// parent process
    	else if (ret > 0) {
			int status;
			waitpid(ret, &status, 0);
        	dup2(fds[0], 0);
			close(fds[1]);
			close(fds[0]);
    	}

		// fork failed
		else {
			return -1;
		}

	}
    dup2(saved_stdout, 1); // redirect output to standard output
	if (execlp(argv[argc-1], argv[argc-1], (char *)NULL) == -1) {
		perror(argv[argc-1]);
		return -1;
	}
    return 0;
}

