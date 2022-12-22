/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2022/12/22 19:19:32 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
