/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2022/12/14 18:15:41 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_binaries(t_statement *statement, char **envp)
{
	bool	executed;
	char	*binary_path;

	executed = true;
	/* if (!statement->cmd)
		return (executed); */
	if (statement->cmd[0] == '.' || statement->cmd[0] == '/')
		binary_path = statement->cmd;
	else
		binary_path = ft_strjoin("/usr/bin/", statement->cmd);
	if (execve(binary_path, statement->args, envp) == -1)
	{
		printf("%s: command not found\n", statement->cmd);
		executed = false;
	}
	return (executed);
//!	free(binary_path);
}
