/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2022/12/11 19:08:30 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_binaries(char **inputs)
{
	char	*binary_path;
	char 	*envp[] = {"PATH=", "TERM=", NULL};
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
	free(binary_path);
}