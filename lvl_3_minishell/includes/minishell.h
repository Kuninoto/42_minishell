/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/10 04:16:12 by nnuno-ca         ###   ########.fr       */
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
# define REDIRECTS "><"

/* ERROR MESSAGES */

# define CL_ARGUMENTS_ERR "no support for command-line arguments"
# define NO_PIPE_PROMPT "minishell: no support for pipe prompt"
# define UNCLOSED_QUOTES "minishell: unclosed quotes"
# define SYTX_ERR_PIPE "minishell: syntax error near unexpected token `|'"
# define SYTX_ERR_RDR "minishell: syntax error near unexpected token `newline'"

# define PIPE_ERR "pipe() failed"
# define FORK_ERR "fork() failed"

# define TOO_MANY_ARGS "exit: too many arguments"

typedef enum e_operator {
	NONE,
	RDR_OUT_REPLACE,
	RDR_OUT_APPEND,
	RDR_INPUT,
	RDR_INPUT_UNTIL,
	PIPE,
}				t_operator;

/* All functions regarding t_statemnent list are
prefixed with p_ referring to parser */
typedef struct s_statement {
	int					argc;
	char				**argv;
	t_operator			operator;
	struct s_statement	*next;
}				t_statement;

/* All functions regarding t_vars are prefixed
with v_ referring to variables */
typedef struct s_vlst {
	char			*var_name;
	char			*var_value;
	bool			is_exported;
	struct s_vlst	*next;
}				t_vlst;

typedef struct s_data {
	char		**envp;
	t_vlst		*envp_lst;
	t_statement	*head;
}				t_data;

/* Setups Minishell. 
Casts argc and argv to void
Saves envp
Initializes lsts
Configs Signals
*/
void				setup_shell(char **envp, t_data *data,
						t_statement **statement_list);

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
void				cmd_export(char *var_name, t_data *data);
// Wannabe exit
void				cmd_exit(int exit_status, t_data *data);
// Wannabe unset
void				cmd_unset(char *var_name, t_vlst **head);

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

bool				valid_input(char *input, t_data *data);

bool				is_all_digits(char *str);

void				destroy(t_data *data);

void				config_signals(void);

void				exec_cmd(t_statement *current_node, t_data *data);
void				exec_type(t_statement *statement_list, t_data *data);
void				exec_executables(t_statement *node, t_data *data);
void				exec_pipe(t_statement *node, t_data *data);
void				exec_redirects(t_statement *node, t_data *data);

// LINKED LISTS ---------------------------------

t_statement			*p_new_node(int argc);
/* Returns the size of the linked list 
which head is passed as a parameter */
size_t				p_lstsize(t_statement *head);
/* Frees the linked list which head is passed as parameter */
void				p_lstclear(t_statement *head);

t_vlst				*v_new_node(char *var_name, char *var_value,
						bool is_exported);
void				v_lstadd_back(t_vlst **head, t_vlst *new);
t_vlst				*v_lstlast(t_vlst *node);
void				v_lstclear(t_vlst **head);

bool				get_exported_state(char *var_name, t_vlst **head);
char				*get_fromvlst(char *var_name, t_vlst **head);

void				save_user_vars(char *statement, t_vlst **head,
						bool to_export);

t_vlst				*init_vars_lst(void);
t_vlst				*init_envp_lst(char **envp);

size_t				get_nr_statements(char *input);

char				*remove_quotes(char	*parsed);

// EXPANDER UTILS
size_t				exit_status_size(void);
size_t				expand_size(char *input, size_t *i, t_data *data);
int					expanded_size(char *input, t_data *data);

char				*expander(char *input, t_data *data);

// PARSER UTILS
t_operator			get_operator(char *operator);
size_t				get_argc(char **parsed);
size_t				get_token_len(char *input_at_i);
size_t				get_nr_statements(char *input);

t_statement			*parser(char *input);

void				print_operator(t_operator operator);

void				panic(t_data *data, char *error_msg, int exit_status);

#endif