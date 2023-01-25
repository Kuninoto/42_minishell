/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/25 19:07:57 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define SUCCESS 0
# define FAILURE -1
# define OPERATORS "|<>"
# define QUOTES "\"\'"
# define DELIMS "\"\' "

/* ERROR MESSAGES */
# define PIPE_ERR "minishell: pipe() failed"
# define FORK_ERR "minishell: fork() failed"

/* typedef enum s_token {
	NOTHING,
	COMMAND,
	ARGUMENT,
	OPERATOR,
}				t_token; */

/*
	NONE,
	RDR_OUT_REPLACE, // >
	RDR_OUT_APPEND, // >>
	RDR_INPUT,	// <
	RDR_INPUT_UNTIL, // <<
	PIPE, // |
*/

typedef enum e_operator {
	NONE,
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
*/
void		setup_shell(int ac, char **av, char **envp, 
								t_data *data, t_statement **statement_list);

/* COMMANDS */

/* Returns true if it has sucessfully executed an
implemented command that doesn't need a fork */
bool				builtin_without_fork(t_statement *statement, t_data *data);

/* Returns true if it has sucessfully 
executed a binary from /usr/bin */
void				cmd_binaries(t_statement *statement, t_data *data);
// Wannabe echo
void				cmd_echo(t_statement *statement);
// Wannabe pwd
void				cmd_pwd(void);
// Wannabe cd
void				cmd_cd(char *path);
// Wannabe env
void				cmd_env(t_data *data);
// Wannabe export
void				cmd_export(t_data *data, char *var_name);
// Wannabe exit
void				cmd_exit(t_statement **head, int exit_status, t_data *data);

static inline void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

// Utils

static inline bool	is_absolute_path(t_statement *statement)
{
	if (is_onstr(statement->argv[0], '/'))
		return (true);
	return (false);
}

bool				is_all_digits(char *str);

void				destroy(t_data *data);

// LINKED LISTS ---------------------------------

t_statement			*new_node(int argc);
/* Returns the size of the linked list 
which head is passed as a parameter */
size_t				lstsize(t_statement *head);
/* Frees the linked list which head is passed as parameter */
void				lstclear(t_statement **head);

void				config_signals(void);

void					exec_cmd(t_statement *current_node, t_data *data);
void					exec_type(t_statement *statement_list, t_data *data);
void					exec_executables(t_statement *node, t_data *data);
void					exec_pipe(t_statement *node, t_data *data);
void					exec_redirects(t_statement *node, t_data *data);

size_t					get_nr_statements(char *input);

t_statement				*parser(char *input, t_data *data);

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

/* Push a str to the vector */
void		vec_push(t_vector *vector, char	*str);
/* Pop a str from the vector */
char		*vec_pop(t_vector *vector);
/* Doubles vector storage capacity */
void		vec_realloc(t_vector *vector);
/* Frees all vector's intern fields */
void		free_vec(t_vector *vector);
// Checks if str is on vector
char		*is_onvec(char *str, t_vector *vector);
// Idk
void		vec_pop_at(char *str, t_vector *vector);
// Saves user defined environment variables
static inline void	save_user_vars(char *user_var, t_vector *var_vec)
{
	
	is_onvec(user_var, var_vec);
	if ()
	vec_push(var_vec, ft_strtrim(user_var, " "));
}




void	print_operator(t_operator operator);

void	debug_args(t_statement *head);

#endif