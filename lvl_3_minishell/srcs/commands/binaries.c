/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2022/12/12 02:21:54 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_binaries(char **inputs, char **envp)
{
	bool	executed;
	char	*binary_path;
	char	*args[] = {"", NULL};
	int		i;

	executed = true;
	if (inputs[0][0] == '.' || inputs[0][1] == '/')
		binary_path = inputs[0];
	else
		binary_path = ft_strjoin("/usr/bin/", inputs[0]);
	args[0] = binary_path;
	i = 0;
	while (inputs[++i])
		args[i] = inputs[i];
	args[i] = NULL;
	if (execve(binary_path, args, envp) == -1)
	{
		printf("%s: command not found\n", inputs[0]);
		executed = false;
	}
	free(args[0]);
	return (executed);
//	free(binary_path);
}
