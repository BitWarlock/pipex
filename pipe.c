/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/18 02:22:42 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <unistd.h>

char	**add_command(char **args, char *cmd)
{
	int	i;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (args[i])
	{
		args[i] = ft_strjoin(args[i], cmd);
		i++;
	}
	free(cmd);
	return (args);
}

char	*get_location(char *envp[], char *argv)
{
	char	**strs;
	char	*tmp;
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			tmp = envp[i];
	strs = ft_split(tmp + 5, ':');
	strs = add_command(strs, argv);
	i = 0;
	while (strs[i])
	{
		if (access(strs[i], F_OK) == 0)
			return (strs[i]);
		i++;
	}
	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
	return (NULL);
}

void	create_file(char *file, int *fd1)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDWR, 0777);
	if (fd < 0)
		print_error(EACCES);
	dup2(fd1[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	if (close(fd) < 0)
		print_error(EIO);
}

void	execute_child(char *argv[], char *envp[], int *fd)
{
	char	*pos;

	pos = get_location(envp, argv[2]);

	create_file(argv[1], fd);
	if (execve(pos, argv, envp) < 0)
		print_error(EINVAL);
	// strs = get_path(envp, argv[3]);
	// execve(strs[0], strs, envp);
}

void	execute_parent(char *argv[], char *envp[], int *fds)
{
	char	*pos;
	int	fd;

	fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		print_error(EIO);
	dup2(fds[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fds[1]);
	pos = get_location(envp, argv[3]);
	if (execve(pos, argv, envp) < 0)
		print_error(ENOENT);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		print_error(EINVAL);
	if (access(argv[1], F_OK) != 0)
		print_error(ENOENT);
	if (pipe(fd) == -1)
		print_error(EPIPE);
	pid = fork();
	if (pid < 0)
		print_error(ESRCH);
	if (pid == 0)
		execute_child(argv, envp, fd);
	waitpid(pid, NULL, 0);
	execute_parent(argv, envp, fd);
	// execute(argv, envp, fd);
	// check_args(argv, envp);
	return EXIT_SUCCESS;
}
