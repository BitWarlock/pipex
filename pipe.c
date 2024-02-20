/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/20 20:41:34 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



char	*add_command(char *arg, char *cmd)
{
	char	*str;
	char	*res;

	str = ft_strjoin(arg, "/");
	res = ft_strjoin(str, cmd);
	free(arg);
	free(str);
	return (res);
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
	int	fd1;

	fd1 = add_file(argv[1], 'i');
	dup2(fd1, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	args = ft_split(argv[2], ' ');
	pos = get_location(envp, args[0]);
	if (execve(pos, args, envp) < 0)
		cmd_err(pos, args);
}

void	execute_parent(char *argv[], char *envp[], int *fds)
{
	char	**args;
	char	*pos;
	int	fd;

	fd = add_file(argv[4], 'o');
	args = ft_split(argv[3], ' ');
	dup2(fds[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fds[1]);
	pos = get_location(envp, args[0]);
	if (execve(pos, args, envp) < 0)
		cmd_err(pos, args);
}


int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		print_error(EINVAL, "<./pipex infile cmd1 cmd2 outfile>");
	if (pipe(fd) < 0)
		print_error(errno, NULL);
	pid = fork();
	if (pid < 0)
		print_error(errno, "fork");
	if (pid == 0)
		execute_child(argv, envp, fd);
	else
	{
		wait(NULL);
		execute_parent(argv, envp, fd);
	}
	return (0);
}
