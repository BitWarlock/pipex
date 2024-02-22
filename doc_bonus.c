/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:37:10 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/22 21:41:23 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	doc(char *argv[], int *fd)
{
	char	*str;

	close(fd[0]);
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (!str)
		{
			free(str);
			print_error(EIO, "get_next_line");
		}
		if (!ft_strncmp(str, argv[2], ft_strlen(argv[2])) && \
		ft_strlen(str) == ft_strlen(argv[2]) + 1)
		{
			free(str);
			exit(0);
		}
		ft_printf(fd[1], str);
		free(str);
	}
}

void	pipe_doc(char *argv[])
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		print_error(errno, NULL);
	pid = fork();
	if (pid < 0)
		print_error(errno, NULL);
	if (pid == 0)
		doc(argv, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	print_error(int err, char *str)
{
	char	*error;

	error = strerror(err);
	if (!str)
		ft_printf(2, "Error: %s\n", error);
	else
		ft_printf(2, "Error: %s: %s\n", error, str);
	exit(EXIT_FAILURE);
}

void	free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	cmd_err(char *str, char **strs)
{
	(void)str;

}

int	add_file(char *str, char c)
{
	int	fd;

	if (c == 't')
	{
		fd = open(str, O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC, 0644);
		if (fd < 0)
			print_error(errno, str);
	}
	if (c == 'o')
	{
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, 0644);
		if (fd < 0)
			print_error(errno, str);
	}
	if (c == 'i')
	{
		fd = open(str, O_RDONLY | O_CLOEXEC);
		if (fd < 0)
			print_error(errno, str);
	}
	return (fd);
}
