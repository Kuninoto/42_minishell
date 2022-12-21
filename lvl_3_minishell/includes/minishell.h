/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/20 18:31:48 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCESS 0
# define FAILURE -1

# include "../libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

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

// COMMANDS
/* Returns true if it has sucessfully executed an
implemented command or printed an env variable*/
bool		cmd_check(t_statement *statement, char **envp);
/* Returns true if it has sucessfully 
executed a binary from /usr/bin */
void		cmd_binaries(t_statement *statement, char **envp);
// Wannabe echo
void			cmd_echo(t_statement *statement);
// Wannabe pwd
void			cmd_pwd(void);
// Wannabe cd
void			cmd_cd(char *path);
// Wannabe env
void			cmd_env(char **envp);
// Expands the environment variable passed as parameter
void		print_env_variables(char *variable_name);

// Utils
// LINKED LISTS ---------------------------------

t_statement	*new_node(int argc);
/* Returns the size of the linked list 
which head is passed as a parameter */
size_t		lstsize(t_statement *head);
// Frees the linked list which head is passed as parameter
void		lstclear(t_statement **head);

void		exec_cmd(t_statement *current_node, char **envp);

// VECTOR ---------------------------------------

typedef struct s_vector {
	size_t	count;
	size_t	capacity;
	char	**storage;
}				t_vector;

t_statement	*parse_input(char *input, t_vector *var_vec);

// VECTOR UTILS ---------------------------------

// Returns an empty vector with the capacity of 1
static inline t_vector	vec_new(void)
{
	return ((t_vector){
		.count = 0,
		.capacity = 1,
		.storage = malloc(sizeof(char *))
	});
}

// Push an env variable to the vector
void	vec_push(t_vector *vector, char	*env_variable);
// Pop an env varible from the vector
char	*vec_pop(t_vector *vector);
// Doubles vector storage capacity
void	vec_realloc(t_vector *vector);
// Frees vector and all its inside fields
void	free_vec(t_vector *vector);
// Checks if user_var is on vector
char	*is_onvec(char *user_var, t_vector *vector);
// Saves user defined environment variables
void	save_user_vars(char *user_var, t_vector *var_vec);

#endif