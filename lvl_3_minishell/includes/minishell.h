/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/14 18:50:59 by nnuno-ca         ###   ########.fr       */
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

typedef enum	e_operator {
	NONE,	// 0
	AND,	// &&	1
	OR,		// ||	2
	REDIRECT_OUTPUT_REPLACE, // > (replace)	3
	REDIRECT_OUTPUT_APPEND, // >> (append)	4
	REDIRECT_INPUT,	// <	5
	PIPE,	// |	6
}				t_operator;

typedef struct s_statement {
	char		*cmd;
	char		**args;
	t_operator	operator;
	struct s_statement	*next;
}				t_statement;

// LINKED LIST
t_statement *new_node(size_t nr_statements);
int			lstsize(t_statement *lst);
void		lstclear(t_statement **head);

void		welcome_art(void);
t_statement *parse_input(char *input);

// COMMANDS

/*
	Returns true if it has sucessfully 
	executed a binary from /usr/bin 
*/
bool	cmd_binaries(t_statement *statement, char **envp);
// Wannabe echo
void	cmd_echo(t_statement *statement);
// Wannabe pwd
void	cmd_pwd(void);
// Wannabe cd
void	cmd_cd(char *path);
// Wannabe env
void	cmd_env(char **envp);
// Expands the environment variable passed as parameter
void	print_env_variables(char *variable_name);

#endif