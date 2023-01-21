/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 00:12:48 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCESS 0
# define FAILURE -1

# include "libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

/* CONSTANTS */

# define OPERATORS "|<>&()"

/* ERROR MESSAGES */
# define PIPE_ERR "pipe() failed"
# define FORK_ERR "fork() failed"

/* typedef enum s_token {
	NOTHING,
	COMMAND,
	ARGUMENT,
	OPERATOR,
}				t_token; */

/*
	NONE,
	AND, // &&
	OR,	// ||
	RDR_OUT_REPLACE, // >
	RDR_OUT_APPEND, // >>
	RDR_INPUT,	// <
	RDR_INPUT_UNTIL, // <<
	PIPE, // |
*/

typedef enum e_operator {
	NONE,
	AND,
	OR,
	RDR_OUT_REPLACE,
	RDR_OUT_APPEND,
	RDR_INPUT,
	RDR_INPUT_UNTIL,
	PIPE,
}				t_operator;

typedef struct s_statement {
	int					argc;
	char				**argv;
	t_operator			operator;
	struct s_statement	*next;
}				t_statement;

/* Vector data structure */
typedef struct s_vector {
	size_t	count;
	size_t	capacity;
	char	**storage;
}				t_vector;

typedef struct s_data {
	char		**envp;
	char		**paths;
	t_vector	var_vec;
	t_vector	envp_vec;
}				t_data;

/* Setups Minishell. 
Casts argc and argv to void
Saves envp
Initializes Vecs
Configs Signals
Prints Welcome Art
*/
void		setup_shell(int ac, char **av, char **envp, 
								t_data *data, t_statement **statement_list);

/* COMMANDS */

/* Returns true if it has sucessfully executed an
implemented command that doesn't need a fork */
bool		builtin_without_fork(t_statement *statement, t_data *data);

/* Returns true if it has sucessfully 
executed a binary from /usr/bin */
void		cmd_binaries(t_statement *statement, t_data *data);
// Wannabe echo
void		cmd_echo(t_statement *statement);
// Wannabe pwd
void		cmd_pwd(void);
// Wannabe cd
void		cmd_cd(char *path);
// Wannabe env
void		cmd_env(t_data *data);
// Wannabe export
void		cmd_export(t_data *data, char *var_name);
// Wannabe exit
void		cmd_exit(t_statement **head, int exit_status, t_data *data);

// Utils
// LINKED LISTS ---------------------------------

t_statement	*new_node(int argc);
/* Returns the size of the linked list 
which head is passed as a parameter */
size_t		lstsize(t_statement *head);
/* Frees the linked list which head is passed as parameter */
void		lstclear(t_statement **head);

void		config_signals(void);

void		exec_cmd(t_statement *current_node, t_data *data);
void		exec_type(t_statement *statement_list, t_data *data);
void		exec_executables(t_statement *node, t_data *data);
void		exec_pipe(t_statement *node, t_data *data);
void		exec_redirects(t_statement *node, t_data *data);

t_statement	*parse_input(char *input, t_data *data, int g_exit_status);

// VECTOR UTILS ---------------------------------

/* Returns an empty vector with the capacity of 1 */
static inline t_vector	vec_new(void)
{
	return ((t_vector){
		.count = 0,
		.capacity = 1,
		.storage = malloc(sizeof(char *))
	});
}

/* Push an env variable to the vector */
void		vec_push(t_vector *vector, char	*env_variable);
/* Pop an env varible from the vector */
char		*vec_pop(t_vector *vector);
/* Doubles vector storage capacity */
void		vec_realloc(t_vector *vector);
/* Frees all vector's intern fields */
void		free_vec(t_vector *vector);
// Checks if user_var is on vector
char		*is_onvec(char *user_var, t_vector *vector);
// Idk
void		vec_pop_at(char *user_var, t_vector *vector);
// Saves user defined environment variables
static inline void	save_user_vars(char *user_var, t_vector *var_vec)
{
	vec_push(var_vec, ft_strtrim(user_var, " "));
}


bool		is_all_digits(char *str);

void		destroy(t_data *data);

#endif