#include <libc.h>

int main(int argc, char *argv[], char *envp[])
{
	printf("Main\n");
	execve("ls", argv, envp);

	return EXIT_SUCCESS;
}
