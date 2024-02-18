# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezki <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 18:11:02 by mrezki            #+#    #+#              #
#    Updated: 2024/02/18 02:23:55 by mrezki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG		= pipex
LIBFT		= libft.a
LIB_DIR		= ./libft
RM		= rm -rf
CFLAGS		= -Wall -Wextra -Werror

SRCS		= pipe.c errors.c

OBJS		= $(SRCS:.c=.o)


all: $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)
	mv $(LIB_DIR)/$(LIBFT) .


$(PROG): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libft/ clean

fclean: clean
	$(RM) $(LIBFT) $(PROG) a.out .DS_Store
	$(MAKE) -C libft/ fclean

re: fclean all

.PHONY: clean
