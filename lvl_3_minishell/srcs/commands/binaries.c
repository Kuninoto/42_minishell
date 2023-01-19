/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2023/01/19 01:50:33 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* TO DO: search for binary path on the whole PATH env variable not just on /usr/bin 
split ':' acess  in every possible path until it finds a possible path */
void	cmd_binaries(t_statement *statement, char **envp)
{
	char	*binary_path;

	binary_path = statement->argv[0];
	if (statement->argv[0][0] == '.' || statement->argv[0][0] == '/')
	{
		if (execve(binary_path, statement->argv, envp) == -1)
		{
			printf("%s: command not found\n", statement->argv[0]);
			exit(127);
		}
	}
	else
	{	
		binary_path = ft_strjoin("/usr/bin/", statement->argv[0]);
		if (execve(binary_path, statement->argv, envp) == -1)
		{
			printf("%s: command not found\n", statement->argv[0]);
			free(binary_path);
			exit(127);
		}
		free(binary_path);
	}
}
