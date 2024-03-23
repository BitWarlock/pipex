# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 18:11:02 by mrezki            #+#    #+#              #
#    Updated: 2024/03/21 22:14:26 by mrezki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG		= pipex
LIBFT		= libft.a
LIB_DIR		= ./libft
RM		= rm -rf
CFLAGS		= -Wall -Wextra -Werror

SRCS		= Mandatory/pipe.c Mandatory/helpers.c Mandatory/helpers_2.c

SRCS_B		= Bonus/pipe_bonus.c Bonus/doc_bonus.c Bonus/helpers_bonus.c

OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)


all: $(PROG)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	@echo "\033[32mCompiling pipex"
	@$(MAKE) -C $(LIB_DIR)
	@mv $(LIB_DIR)/$(LIBFT) .


$(PROG): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "\033[1;36m'pipex' is now ready."
	@echo "Usage: > ./pipex input_file cmd1 cmd2 output_file"

bonus: $(LIBFT) $(OBJS_B)
	@$(CC) $(CFLAGS) $^ -o $(PROG)
	@echo "\033[1;36m'pipex' is now ready."
	@echo "Usage:\n> ./pipex input_file cmd1 cmd2 ... output_file"
	@echo "> ./pipex here_doc LIMITER cmd1 cmd2 outfile"

clean:
	@$(RM) $(OBJS) $(OBJS_B)
	@$(MAKE) -C libft/ clean
	@echo "\033[38;2;188;31;54mCleanup Complete."

fclean: clean
	@$(RM) $(LIBFT) $(PROG) a.out .DS_Store
	@$(MAKE) -C libft/ fclean
	@echo "\033[38;2;188;31;54mFull Cleanup Complete."

re: fclean all

.PHONY: clean fclean
