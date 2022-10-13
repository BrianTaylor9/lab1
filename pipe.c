#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int saved_stdout = dup(1);
    int fds[2];
	int i;
	for (i = 1; i < argc - 1; i++) {
    	pipe(fds);
    	int ret = fork();
    	if (ret == 0) {
        	dup2(fds[1], 1);
			if (execlp(argv[i], argv[i], (char *)NULL) == -1) {
				perror(argv[i]);
				return -1;
			}
        	exit(0);
    	}
    	else if (ret > 0) {
			int status;
			waitpid(ret, &status, 0);
        	dup2(fds[0], 0);
			close(fds[1]);
    	}
		else {
		}
	}
    dup2(saved_stdout, 1);
	if (execlp(argv[argc-1], argv[argc-1], (char *)NULL) == -1) {
		perror(argv[argc-1]);
		return -1;
	}
    return 0;
}

