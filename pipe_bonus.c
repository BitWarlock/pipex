/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:34:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/04 14:07:08 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		exit(EXIT_FAILURE);
	}
}

void	pipe_cmd(char **envp, char *cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		print_error("Pipe creation failed");
	pid = fork();
	if (pid < 0)
		print_error("Forking failed");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute_cmd(cmd, envp);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	cmd;
	int	out;
	int	inp;

	if (argc < 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 ... outfile");
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
		close(inp);
	}
	while (cmd < (argc - 2))
		pipe_cmd(envp, argv[cmd++]);
	while (waitpid(-1, NULL, 0) != -1)
		;
	dup2(out, STDOUT_FILENO);
	close(out);
	execute_cmd(argv[argc - 2], envp);
}
