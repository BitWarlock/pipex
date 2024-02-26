/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/26 10:34:01 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*add_command(char *arg, char *cmd)
{
	char	*str;
	char	*res;

	str = ft_strjoin(arg, "/");
	res = ft_strjoin(str, cmd);
	free(str);
	return (res);
}

char	*get_location(char *envp[], char *cmd)
{
	int		i;
	char	**strs;
	char	*tmp;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			tmp = envp[i];
	strs = ft_split(tmp + 5, ':');
	i = 0;
	while (strs[i])
	{
		tmp = add_command(strs[i], cmd);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	free_split(strs);
	return (cmd);
}

void	execute_child(char *argv[], char *envp[], int *fds)
{
	int		fd1;
	char	*pos;
	char	**args;

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
	int		fd;
	char	**args;
	char	*pos;

	fd = add_file(argv[4], 'o');
	args = ft_split(argv[3], ' ');
	dup2(fds[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fds[1]);
	pos = get_location(envp, args[0]);
	close(fds[0]);
	if (execve(pos, args, envp) < 0)
		cmd_err(pos, args);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (argc != 5)
		print_error(EINVAL, "<./pipex infile cmd1 cmd2 outfile>");
	if (pipe(fd) < 0)
		print_error(errno, NULL);
	pid = fork();
	if (pid < 0)
		print_error(errno, "fork");
	if (pid == 0)
		execute_child(argv, envp, fd);
	pid2 = fork();
	if (pid2 == 0)
		execute_parent(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	while (wait(NULL) > 0)
		;
	return (0);
}
