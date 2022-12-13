/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/13 01:52:07 by nnuno-ca         ###   ########.fr       */
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

typedef struct s_simple_command {
	char	*command;
	char	**arguments;
}				t_simple_command;

void	welcome_art(void);
char	**parse_input(char *input);

// COMMANDS

/*
	Returns true if it has sucessfully 
	executed a binary from /usr/bin 
*/
bool	cmd_binaries(char **parsed, char **envp);
// Wannabe echo
void	cmd_echo(char **parsed);
// Wannabe pwd
void	cmd_pwd(void);
// Wannabe cd
void	cmd_cd(char *path);
// Wannabe env
void	cmd_env(char **envp);
// Expands the environment variable passed as parameter
void	print_env_variables(char *variable_name);

#endif