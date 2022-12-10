# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/10 02:03:24 by nnuno-ca          #+#    #+#              #
#    Updated: 2022/12/10 02:04:35 by nnuno-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
RM = rm -rf

NAME = minishell
SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o minishell

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS) $(BONUS_OBJS)
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) $(BONUS_NAME)
re: fclean all

.SILENT:
