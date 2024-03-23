/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:56:49 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/22 08:56:51 by mrezki           ###   ########.fr       */
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

void	close_fds(int a, int b, int c, int d)
{
	dup2(a, STDIN_FILENO);
	close(a);
	close(b);
	close(c);
	close(d);
}
