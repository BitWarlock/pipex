/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:37:10 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/04 14:11:39 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	ft_printf(2, "Error: %s\n", str);
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
	ft_printf(2, "Error: %s: Command not found\n", strs[0]);
	free_split(strs);
	exit(EXIT_FAILURE);
}

int	add_file(char *str, char c)
{
	int	fd;

	if (c == 'o')
	{
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, 0644);
		if (fd < 0)
			print_error("Output file creation failed");
	}
	if (c == 'i')
	{
		fd = open(str, O_RDONLY | O_CLOEXEC);
		if (fd < 0)
			print_error("Input file opening failed");
	}
	return (fd);
}
