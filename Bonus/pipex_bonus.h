/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:35:17 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/20 23:48:48 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

int		add_file(char *str, char c, int *i);
void	print_error(char *str, char *input);
void	cmd_err(char *str, char **strs);
void	free_split(char **str);
void	doc(char *argv[], int *fd);
void	pipe_doc(char *argv[], int i);
char	*add_command(char *arg, char *cmd);
void	close_fds(int a, int b, int c, int d);

#endif // !PIPEX_H
