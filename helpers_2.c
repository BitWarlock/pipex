/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:42:27 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/20 23:01:46 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_cmd(char *argv[], char *envp[], int *fd)
{
	pid_t	pid;
	pid_t	pid2;

	pid = fork();
	if (pid < 0)
		print_error("Forking failed", NULL);
	if (pid == 0)
		execute_child(argv, envp, fd);
	pid2 = fork();
	if (pid2 == 0)
		execute_parent(argv, envp, fd);
}
