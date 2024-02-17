/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/17 23:23:11 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/errno.h>
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
	return (args);
}

char	**get_path(char *envp[], char *argv)
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
	return (strs);
}

void	create_file(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
		print_error(EACCES);
	dup2(fd, STDOUT_FILENO);
	if (close(fd) < 0)
		print_error(EIO);
}

void	execute(char *argv[], char *envp[], int fd[2])
{
	pid_t	pid;
	char	**strs;

	strs = get_path(envp, argv[1]);
	pid = fork();
	if (pid < 0)
		print_error(ESRCH);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		strs = get_path(envp, argv[3]);
		execve(strs[0], strs, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		strs = get_path(envp, argv[2]);
		create_file(argv[4]);
		execve(strs[0], strs, envp);
	}
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
		execute(argv, envp, fd);
	// check_args(argv, envp);
	return EXIT_SUCCESS;
}
