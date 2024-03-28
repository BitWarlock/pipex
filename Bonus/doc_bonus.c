/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:37:10 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/21 05:31:28 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	doc(char *argv[], int *fd)
{
	char	*str;

	close(fd[0]);
	while (1)
	{
		ft_printf(1, "here_doc > ");
		str = get_next_line(STDIN_FILENO);
		if (!str)
		{
			free(str);
			print_error("get_next_line failed", NULL);
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
	close(fd[1]);
}

void	pipe_doc(char *argv[], int argc)
{
	int		fd[2];
	int		stin;
	pid_t	pid;

	stin = dup(STDIN_FILENO);
	if (argc < 6)
		print_error("Usage: ./pipex here_doc LIMITER cmd1 cmd2 outfile", NULL);
	if (pipe(fd) < 0)
		print_error("Pipe creation failed", NULL);
	pid = fork();
	if (pid < 0)
		print_error("Forking failed", NULL);
	if (pid == 0)
		doc(argv, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	print_error(char *str, char *input)
{
	if (input)
	{
		ft_printf(2, "Error: %s: %s.\n", str, input);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_printf(2, "Error: %s\n", str);
		exit(EXIT_FAILURE);
	}
}

void	free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	add_file(char *str, char c, int *i)
{
	int	fd;

	if (c == 't')
	{
		*i = 3;
		fd = open(str, O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC, 0644);
		if (fd < 0)
			print_error("Output file creation failed", str);
	}
	if (c == 'o')
	{
		*i = 2;
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, 0644);
		if (fd < 0)
			print_error("Output file creation failed", str);
	}
	if (c == 'i')
	{
		*i = 2;
		fd = open(str, O_RDONLY | O_CLOEXEC);
		if (fd < 0)
			print_error("Input file opening failed", str);
	}
	return (fd);
}
