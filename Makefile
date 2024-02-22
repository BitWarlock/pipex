# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezki <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 18:11:02 by mrezki            #+#    #+#              #
#    Updated: 2024/02/22 21:43:09 by mrezki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG		= pipex
LIBFT		= libft.a
LIB_DIR		= ./libft
RM		= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g

SRCS		= pipe.c errors.c

SRCS_B		= pipe_bonus.c doc_bonus.c

OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)


all: $(PROG)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	@echo "\033[33mCompiling pipex"
	@$(MAKE) -C $(LIB_DIR)
	@mv $(LIB_DIR)/$(LIBFT) .


$(PROG): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "\033[32mCompilation successful. 'pipex' is ready."
	@echo "Usage: > ./pipex input_file cmd1 cmd2 output_file"

bonus: $(LIBFT) $(OBJS_B)
	@$(CC) $(CFLAGS) $^ -o $(PROG)
	@echo "\033[32mCompilation successful. 'pipex' is ready."
	@echo "Usage:\n> ./pipex input_file cmd1 cmd2 ... output_file"
	@echo "> ./pipex here_doc LIMITER cmd1 cmd2 outfile"

clean:
	@$(RM) $(OBJS) $(OBJS_B)
	@$(MAKE) -C libft/ clean
	@echo "\033[31mCleanup Complete."

fclean: clean
	@$(RM) $(LIBFT) $(PROG) a.out .DS_Store
	@$(MAKE) -C libft/ fclean
	@echo "\033[31mFull Cleanup Complete."

re: fclean all

.PHONY: clean fclean
