/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/21 22:14:48 by mrezki           ###   ########.fr       */
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

	fd1 = open_file(argv[1], 'i');
	args = ft_split(argv[2], ' ');
	dup2(fd1, STDIN_FILENO);
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	pos = get_location(envp, args[0]);
	close(fds[1]);
	if (execve(pos, args, envp) < 0)
		cmd_err(args);
}

void	execute_parent(char *argv[], char *envp[], int *fds)
{
	int		fd;
	char	**args;
	char	*pos;

	fd = open_file(argv[4], 'o');
	args = ft_split(argv[3], ' ');
	dup2(fds[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fds[1]);
	pos = get_location(envp, args[0]);
	close(fds[0]);
	if (execve(pos, args, envp) < 0)
		cmd_err(args);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];

	if (argc != 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 outfile", NULL);
	if (pipe(fd) < 0)
		print_error("Pipe creation failed", NULL);
	pipe_cmd(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	while ((wait(NULL)) != -1)
		continue ;
	return (0);
}
