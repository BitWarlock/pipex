/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/21 05:40:36 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
			return (free_split(strs), tmp);
		free(tmp);
		i++;
	}
	free_split(strs);
	return (ft_strdup(cmd));
}

void	execute_cmd(char *argv, char *envp[])
{
	char	*pos;
	char	**args;

	args = ft_split(argv, ' ');
	pos = get_location(envp, args[0]);
	if (execve(pos, args, envp) < 0)
	{
		ft_printf(2, "Error: %s: Command not found\n", args[0]);
		free_split(args);
		free(pos);
		exit(EXIT_FAILURE);
	}
}

void	pipe_cmd(char **envp, char *cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		print_error("Pipe creation failed", NULL);
	pid = fork();
	if (pid < 0)
		print_error("Forking failed", NULL);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_cmd(cmd, envp);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

void	last_cmd(char *cmd, char **envp, int out)
{
	char	*pos;
	char	**args;
	pid_t	pid;

	args = ft_split(cmd, ' ');
	pos = get_location(envp, args[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
		if (execve(pos, args, envp) < 0)
		{
			ft_printf(2, "Error: %s: Command not found\n", args[0]);
			free_split(args);
			free(pos);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		free_split(args);
		free(pos);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	cmd;
	int	out;
	int	inp;
	int	stin;

	if (argc < 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 ... outfile", NULL);
	stin = dup(STDIN_FILENO);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && 8 == ft_strlen(argv[1]))
	{
		pipe_doc(argv, argc);
		out = add_file(argv[argc - 1], 't', &cmd);
	}
	else
	{
		out = add_file(argv[argc - 1], 'o', &cmd);
		inp = add_file(argv[1], 'i', &cmd);
		dup2(inp, STDIN_FILENO);
	}
	while (cmd < argc - 2)
		pipe_cmd(envp, argv[cmd++]);
	last_cmd(argv[argc - 2], envp, out);
	close_fds(stin, out, inp, 3);
	while (wait(NULL) != -1)
		continue ;
}
