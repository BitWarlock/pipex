#include <libc.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t	pid;
	int	i;
	int	fd[2];

	for (i = 1; i < argc - 1; i++)
	{
		if (pipe(fd) < 0)
      			exit(1);
		if ((pid = fork()) < 0)
			exit(1);
		if (pid == 0)
		{
			dup2(fd[0], 0);
			dup2(fd[1], 1);
			if (i == argc - 1)
				close(fd[0]);
			close(fd[1]);
			execlp(argv[i], argv[i], NULL);
		}
		waitpid(pid, NULL, 0);
		close(fd[1]);
		//close(fd[0]);
	}
	dup2(fd[0], 0);
	//while(1);
	execlp(argv[i], argv[i], NULL);
	return EXIT_SUCCESS;
}
