/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:35:17 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/22 19:54:48 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

int		add_file(char *str, char c);
void	print_error(int err, char *str);
void	cmd_err(char *str, char **strs);
void	free_split(char **str);
void	doc(char *argv[], int *fd);
void	pipe_doc(char *argv[]);

#endif // !PIPEX_H