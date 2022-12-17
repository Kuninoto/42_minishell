/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/17 19:09:42 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCESS 0
# define FAILURE -1

# include "../libft/libft.h"
# include "../includes/utils.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>

// CONSTANTS
# define OPERATORS "|<>&()"

/* typedef enum s_token {
	NOTHING,
	COMMAND,
	ARGUMENT,
	OPERATOR,
}				t_token; */

typedef enum	e_operator {
	NONE,
	AND, // &&
	OR,	// ||
	RDR_OUT_REPLACE, // >
	RDR_OUT_APPEND, // >>
	RDR_INPUT,	// <
	PIPE, // |
}				t_operator;

typedef struct s_statement {
	int					argc;
	char				**argv;
	t_operator			operator;
	struct s_statement	*next;
}				t_statement;


// Prints the minishell gradient ASCII art
void		welcome_art(void);
t_statement *parse_input(char *input);

// COMMANDS
/* Returns true if it has sucessfully 
executed a binary from /usr/bin */
bool		cmd_binaries(t_statement *statement, char **envp);
// Wannabe echo
void		cmd_echo(t_statement *statement);
// Wannabe pwd
void		cmd_pwd(void);
// Wannabe cd
void		cmd_cd(char *path);
// Wannabe env
void		cmd_env(char **envp);
// Expands the environment variable passed as parameter
void		print_env_variables(char *variable_name);

// Utils
// LINKED LISTS

t_statement	*new_node(int argc);
/* Returns the size of the linked list 
which head is passed as a parameter */
size_t		lstsize(t_statement *head);
// Frees the linked list which head is passed as parameter
void		lstclear(t_statement **head);

#endif