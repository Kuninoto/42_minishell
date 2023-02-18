# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roramos <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 19:26:52 by nnuno-ca          #+#    #+#              #
#    Updated: 2023/02/18 20:24:37 by roramos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LINK = -I./includes
VPATH = srcs srcs/parser srcs/expander srcs/commands\
		srcs/commands/builtins srcs/executes srcs/utils srcs/utils/linked_lists
RM = rm -rf
LIBFT = ./libft/libft.a

UTILS = is_all_digits_or_signals panic destroy valid_input
UTILS_LL = p_llst_utils v_llst_utils v_llst_utils_v2
PARSER = parser parser_utils remove_quotes
EXPANDER = expander expander_utils
GENERAL = config_signals setup_shell
COMMANDS = binaries builtins 
BUILTINS = cd echo env exit export pwd unset
EXECUTES = exec_cmd executables pipe redirects

NAME = minishell
SRCS =	$(addsuffix .c, $(UTILS))\
		$(addsuffix .c, $(UTILS_LL))\
		$(addsuffix .c, $(PARSER))\
		$(addsuffix .c, $(EXPANDER))\
		$(addsuffix .c, $(GENERAL))\
		$(addsuffix .c, $(COMMANDS))\
		$(addsuffix .c, $(BUILTINS))\
		$(addsuffix .c, $(EXECUTES))\
		main.c
		
OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o minishell

$(LIBFT):
	$(MAKE) -C ./libft

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LINK)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJS)
	
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	
re: fclean all

noleaks: re
	valgrind ./minishell

noleaksfull: re
	valgrind --leak-check=full --show-leak-kinds=all -s ./minishell

run: re
	./minishell

.PHONY: all clean fclean re run

.SILENT:
