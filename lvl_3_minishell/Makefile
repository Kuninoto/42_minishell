# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 19:26:52 by nnuno-ca          #+#    #+#              #
#    Updated: 2023/01/21 00:18:28 by nnuno-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes
RM = rm -rf
LIBFT = ./libft/libft.a

NAME = minishell
SRCS =  srcs/commands/binaries.c\
		srcs/commands/builtins.c\
		srcs/commands/builtins/cd.c\
		srcs/commands/builtins/echo.c\
		srcs/commands/builtins/env.c\
		srcs/commands/builtins/exit.c\
		srcs/commands/builtins/export.c\
		srcs/commands/builtins/pwd.c\
		srcs/executes/cmds.c\
		srcs/executes/executables.c\
		srcs/executes/pipe.c\
		srcs/executes/redirects.c\
		srcs/utils/linked_lists/linked_lists_utils.c\
		srcs/utils/vector/vector_actions.c\
		srcs/utils/vector/vector_utils.c\
		srcs/utils/is_all_digits.c\
		srcs/utils/destroy.c\
	   	srcs/config_signals.c\
		srcs/setup_shell.c\
	   	srcs/parser.c\
	   	main.c
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) -lreadline -o minishell

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
	
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	
re: fclean all

.SILENT:
