/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/19 16:26:09 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*add_command(char *arg, char *cmd)
{
	char	*str;

	str = ft_strjoin(arg, "/");
	str = ft_strjoin(str, cmd);
	free(arg);
	return (str);
}

char	*get_location(char *envp[], char *cmd)
{
	char	**strs;
	char	*tmp;
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			tmp = envp[i];
	strs = ft_split(tmp + 5, ':');
	i = 0;
	while (strs[i])
	{
		strs[i] = add_command(strs[i], cmd);
		if (access(strs[i], F_OK) == 0)
			return (strs[i]);
		i++;
	}
	return (free_split(strs), NULL);
}

void	execute_child(char *argv[], char *envp[], int *fds)
{
	char	*pos;
	char	**args;
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error(errno, argv[1]);
	dup2(fds[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fds[0]);
	args = ft_split(argv[2], ' ');
	pos = get_location(envp, args[0]);
	if (!pos)
	{
		free_split(args);
		print_error(errno, "Command");
	}
	if (execve(pos, args, envp) < 0)
	{
		free_split(args);
		print_error(errno, "execve");
	}
}

void	execute_parent(char *argv[], char *envp[], int *fds)
{
	char	**args;
	char	*pos;
	int	fd;

	args = ft_split(argv[3], ' ');
	fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		print_error(errno, argv[4]);
	dup2(fds[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fds[1]);
	pos = get_location(envp, args[0]);
	if (!pos)
	{
		free_split(args);
		print_error(errno, "Command");
	}
	if (execve(pos, args, envp) < 0)
	{
		free_split(args);
		print_error(errno, "execve");
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		print_error(EINVAL, "4 arguments");
	if (access(argv[1], F_OK) != 0)
		print_error(errno, argv[1]);
	if (pipe(fd) < 0)
		print_error(errno, "pipe");
	pid = fork();
	if (pid < 0)
		print_error(errno, "fork");
	if (pid == 0)
		execute_child(argv, envp, fd);
	execute_parent(argv, envp, fd);
	wait(NULL);
	return EXIT_SUCCESS;
}
