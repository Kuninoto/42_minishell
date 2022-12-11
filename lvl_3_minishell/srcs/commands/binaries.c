/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2022/12/11 20:06:07 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_binaries(char **inputs)
{
	char 	*envp[] = {"PATH=", "TERM=", NULL};
	char	*binary_path;
	char	*args[] = {NULL};
	int		i;

	envp[0] = join_freev2(envp[0], getenv("PATH"));
	envp[1] = join_freev2(envp[1], getenv("TERM"));
 	binary_path = ft_strjoin("/usr/bin/", inputs[0]);
	args[0] = binary_path;
	
	i = 0;
	while (inputs[++i])
		args[i] = inputs[i];
	args[i] = NULL;
	if (execve(binary_path, args, envp) == -1)
		printf("%s: command not found\n", inputs[0]);
	free(envp[0]);
	free(envp[1]);
	free(args[0]);
	free(binary_path);
}