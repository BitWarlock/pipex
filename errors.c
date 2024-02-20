/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:37:10 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/20 21:03:27 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int err, char *str)
{
	char	*error;

	error = strerror(err);
	if (!str)
		ft_printf(2, "Error: %s\n", error);
	else
		ft_printf(2, "Error: %s, %s\n", error, str);
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
	ft_printf(2, "Error: %s: Command not found\n", strs[0]);
	free(str);
	free_split(strs);
	exit(EXIT_FAILURE);
}

int	add_file(char *str, char c)
{
	int	fd;

	if (c == 'o')
	{
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			print_error(errno, str);
	}
	if (c == 'i')
	{
		fd = open(str, O_RDONLY);
		if (fd < 0)
			print_error(errno, str);
	}
	return (fd);
}
