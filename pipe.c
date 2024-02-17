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

void	execute(char *argv[], char *envp[])
{
	char	**strs;
	char	*tmp;
	int	found;
	int	i;

	i = -1;
	found = 0;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			tmp = envp[i];
	strs = ft_split(tmp + 5, ':');
	strs = add_command(strs, argv[2]);
	i = 0;
	while (strs[i])
	{
		if ((execve(strs[i], argv, envp) >= 0))
		{
			found = 1;
			tmp = strs[i];
			ft_printf(0, "%s\n\n\n", tmp);
			break ;
		}
		i++;
	}
	// if (!found)
	// {
	// 	ft_printf(2, "Error: <%s> Command not found\n", argv[2]);
	// 	exit(EXIT_FAILURE);
	// }
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;

	if (argc != 5)
		print_error(EINVAL);
	if (access(argv[1], F_OK) != 0)
		print_error(ENOENT);
	pid = fork();
	if (pid < 0)
		print_error(ESRCH);
	if (pid == 0)
		execute(argv, envp);
	// check_args(argv, envp);
	return EXIT_SUCCESS;
}
