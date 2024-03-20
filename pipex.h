/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:35:17 by mrezki            #+#    #+#             */
/*   Updated: 2024/03/20 22:57:15 by mrezki           ###   ########.fr       */
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

int		open_file(char *str, char c);
void	print_error(char *str, char *s);
void	cmd_err(char **strs);
void	free_split(char **str);
void	pipe_cmd(char *argv[], char *envp[], int *fd);
void	execute_child(char *argv[], char *envp[], int *fds);
void	execute_parent(char *argv[], char *envp[], int *fds);

#endif // !PIPEX_H
