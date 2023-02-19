/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/19 18:00:29 by nnuno-ca         ###   ########.fr       */
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

// MINISHELL

# define CL_ARGUMENTS_ERR "minishell: no support for command-line arguments"
# define NO_PIPE_PROMPT "minishell: no support for pipe prompt"
# define NO_SYTX_PROMPT "minishell: no support for syntax prompt"
# define PIPE_ERR "minishell: pipe() failed"
# define FORK_ERR "minishell: fork() failed"

// SYNTAX

# define UNCLOSED_QUOTES "minishell: unclosed quotes"
# define SYTX_ERR_PIPE "minishell: syntax error near unexpected token `|'"
# define NO_BRACE_PROMPT "minishell: no support for brace prompt"
# define ERR_BRACE_F "minishell: syntax error near unexpected token `)'"
# define ERR_RECT_BRACE_F "minishell: syntax error near unexpected token `}'"
# define SYTX_ERR_RDR "minishell: syntax error near unexpected token `newline'"

// EXIT CMD

# define EXIT_TOO_MANY_ARGS "minishell: exit: too many arguments"
# define EXIT_NON_NUMERIC_ARG "minishell: exit: numeric argument required" 

// CD CMD

# define CD_TOO_MANY_ARGS "minishell: cd: too many arguments"
# define OLDPWD_NOT_SET "minishell: cd: OLDPWD not set"

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

/* All functions regarding t_vars 
are prefixed with v_ referring to variables */
typedef struct s_vlst {
	char			*var_name;
	char			*var_value;
	bool			is_exported;
	struct s_vlst	*next;
}				t_vlst;

/* data keeps a pointer to the head node in
 case of a need to call panic() (fork or pipe error) */

typedef struct s_data {
	char		**envp;
	t_vlst		*envp_lst;
	t_statement	*head;
}				t_data;

void				child_signals(int signum);
void				dismiss_signal(int signum);
/* Setups Minishell. 
Casts argc and argv to void
Saves envp
Initializes lsts
Configs Signals
*/
void				setup_shell(char **envp, t_data *data,
						t_statement **statement_list);

/* COMMANDS */

/* Returns true if it has executed a builtin command */
bool				builtin(t_statement *statement, t_data *data);

/* Returns true if it has sucessfully 
executed a binary from PATH */
void				cmd_binaries(t_statement *statement, t_data *data);
// Wannabe echo
int					cmd_echo(t_statement *statement);
// Wannabe pwd
int					cmd_pwd(void);
// Wannabe cd
int					cmd_cd(char *path);

static inline int	cd_too_many_args(void)
{
	ft_putendl_fd(CD_TOO_MANY_ARGS, STDERR_FILENO);
	return (EXIT_FAILURE);
}
// Wannabe env
int					cmd_env(t_data *data);
// Wannabe export
int					cmd_export(t_statement *statement, t_data *data);
// Wannabe exit
// void				cmd_exit(int exit_status, t_data *data);
void				cmd_exit(t_statement *s, t_data *data);
/* Encapsulate if's. Norm Purposes */
void				call_cmd_exit(t_statement *statement, t_data *data);
// Wannabe unset
int					cmd_unset(char *var_name, t_vlst **head);

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


int					unclosed_quotes(char *str);
bool				invalid_syntax(char *input);
bool				invalid_syntax2(char *input);
bool				invalid_syntax3(char *input);
bool				valid_input(char *input, t_data *data);

bool				is_all_digits_or_signals(char *str);

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
void				p_lstclear(t_statement **head);

t_vlst				*v_new_node(char *var_name, char *var_value,
						bool is_exported);
void				v_lstadd_back(t_vlst **head, t_vlst *new);
t_vlst				*v_lstlast(t_vlst *node);
void				v_lstclear(t_vlst **head);

bool				get_exported_state(char *var_name, t_vlst **head);
char				*get_fromvlst(char *var_name, t_vlst **head);

/* same as get_fromvlst except that it
encapsulates the free procedure for <var_name> */
char				*get_varvalue_fromvlst(char *var_name, t_data *data);

int					save_user_vars(char *statement, t_vlst **head,
						bool to_export);

t_vlst				*init_envp_lst(char **envp);

size_t				get_nr_statements(char *input);

char				*remove_quotes(char	*parsed);

// EXPANDER UTILS

static inline bool	single_dollar(char *input_at_i)
{
	return ((!input_at_i[1]
			|| input_at_i[1] == ' '
			|| input_at_i[1] == '\"'));
}

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