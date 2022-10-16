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
		return EINVAL;
	}
	for (i = 1; i < argc - 1; i++) {
    	pipe(fds);
    	int ret = fork();

		// child process
    	if (ret == 0) {
        	dup2(fds[1], 1); // directs output to write-end of pipe
			if (execlp(argv[i], argv[i], NULL) == -1) {
				return errno;
			}
    	}

		// parent process
    	else if (ret > 0) {
			int status;
			waitpid(ret, &status, 0);
			if (!WIFEXITED(status)) {
				return WEXITSTATUS;
			}
        	dup2(fds[0], 0); // input reads from read-end of pipe
			close(fds[1]);
			close(fds[0]);
    	}

		// fork failed
		else {
			return errno;
		}

	}
    dup2(saved_stdout, 1); // redirect output to standard output
	close(saved_stdout);
	if (execlp(argv[argc-1], argv[argc-1], NULL) == -1) {
		return errno;
	}
    return 0;
}

