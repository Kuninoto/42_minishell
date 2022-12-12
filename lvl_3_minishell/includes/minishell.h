/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/12 01:48:50 by nnuno-ca         ###   ########.fr       */
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

void	welcome_art(void);
char	**parse_input(char *input);

// COMMANDS

// Returns true if it has sucessfully executed a binary
bool	cmd_binaries(char **inputs, char **envp);
// Wannabe echo
void	cmd_echo(char **inputs);
// Wannabe pwd
void	cmd_pwd(void);
// Wannabe cd
void	cmd_cd(char *path);
// Wannabe env
void	cmd_env(char **envp);

void	print_env_variables(char *variable_name);

#endif