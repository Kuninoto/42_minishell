# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roramos <roramos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 19:26:52 by nnuno-ca          #+#    #+#              #
#    Updated: 2022/12/28 19:58:26 by roramos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
RM = rm -rf

NAME = minishell
SRCS =  srcs/commands/binaries.c\
		srcs/commands/cd.c\
		srcs/commands/checks.c\
		srcs/commands/echo.c\
		srcs/commands/env.c\
		srcs/commands/export.c\
		srcs/commands/pwd.c\
		srcs/commands/save_user_vars.c\
		srcs/executes/cmds.c\
		srcs/executes/executables.c\
		srcs/executes/pipe.c\
		srcs/executes/redirects.c\
		srcs/utils/linked_lists/linked_lists_utils.c\
		srcs/utils/vector/vector_utils.c\
	   	srcs/utils/welcome_art.c\
	   	srcs/parser.c\
	   	main.c
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o minishell

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
	
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	
re: fclean all

.SILENT:
