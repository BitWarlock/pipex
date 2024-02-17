#include <libc.h>

int main(int argc, char *argv[], char  *envp[])
{
	int	i;

	i = 0;
	printf("Sub program: ");
	while (i < argc)
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\nSub envp ");
	i = 0;
	while (envp[i])
	{
		printf("%s ", envp[i]);
		i++;
	}
	return EXIT_SUCCESS;
}
