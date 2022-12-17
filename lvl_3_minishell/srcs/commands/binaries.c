/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2022/12/17 19:18:50 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_binaries(t_statement *statement, char **envp)
{
	char	*binary_path;
	bool	executed;

	binary_path = statement->argv[0];
	executed = true;
	/* if (!statement->cmd)
		return (executed); */
	if (statement->argv[0][0] == '.' || statement->argv[0][0] == '/')
	{
		if (execve(binary_path, statement->argv, envp) == -1)
		{
			printf("%s: command not found\n", statement->argv[0]);
			executed = false;
		}
	}
	else
	{	
		binary_path = ft_strjoin("/usr/bin/", statement->argv[0]);
		if (execve(binary_path, statement->argv, envp) == -1)
		{
			printf("%s: command not found\n", statement->argv[0]);
			executed = false;
			free(binary_path);
		}
	}
	return (executed);
}
