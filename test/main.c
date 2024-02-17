#include <libc.h>
#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>

int main(int argc, char **argv)
{
	pid_t	pid;
	int fd[2];
	char str[500];
	char c;

	int fd0 = open("outfile", O_CREAT | O_RDWR, 0777);
	if (pipe(fd) == -1)
		exit(1);
	pid = fork();

	if (pid == 0)
	{
		// dup2(fd[1], 1);
		write(fd[1], "123456789", 9);
		exit(0);
	}
	close(fd[1]);
	// dup2(fd[0], 0);
	while ((read(fd[0], &c, 1)) > 0)
		write (1, &c, 1);
	close(fd[0]);
	return EXIT_SUCCESS;
	// int i;
	//
	// for( i=1; i<argc-1; i++)
	// {
	// 	int pd[2];
	// 	pipe(pd);
	//
	// 	if (!fork()) {
	// 		dup2(pd[1], 1); // remap output back to parent
	// 		execlp(argv[i], argv[i], NULL);
	// 		perror("exec");
	// 		abort();
	// 	}
	//
	// 	// remap output from previous child to input
	// 	dup2(pd[0], 0);
	// 	close(pd[1]);
	// }
	//
	// execlp(argv[i], argv[i], NULL);
	// perror("exec");
	// abort();
}
