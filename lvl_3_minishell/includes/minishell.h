/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 02:52:09 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/11 18:49:10 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

// COMMANDS

// Wannabe echo
void	cmd_echo(char **inputs);
void	cmd_binaries(char **input);
void	cmd_pwd(void);
char	**parse_input(char *input);


#endif