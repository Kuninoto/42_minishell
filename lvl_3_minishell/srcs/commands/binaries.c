/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2023/01/19 18:34:53 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_exit_status;

char	*get_bin_path(char *cmd, char **paths)
{
	size_t	i;
	char	*tmp;
	char	*bin_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		bin_path = join_free(tmp, cmd);
		if (access(bin_path, F_OK) == 0)
			return (bin_path);
		free(bin_path);
		i += 1;
	}
	return (NULL);
}

/* TO DO: search for binary path on the whole PATH env variable not just on /usr/bin 
split ':' acess  in every possible path until it finds a possible path */
void	cmd_binaries(t_statement *statement, t_data *data)
{
	char	*binary_path;

	binary_path = statement->argv[0];
	if (statement->argv[0][0] == '.' || statement->argv[0][0] == '/')
	{
		if (execve(binary_path, statement->argv, data->envp) == -1)
		{
			printf("%s: command not found\n", statement->argv[0]);
			g_exit_status = 127;
			exit(127);
		}
	}
	else
	{	
		binary_path = get_bin_path(statement->argv[0], data->paths);
		if (binary_path == NULL || execve(binary_path, statement->argv, data->envp) == -1)
		{
			printf("%s: command not found\n", statement->argv[0]);
			free(binary_path);
			g_exit_status = 127;
			exit(127);
		}
		free(binary_path);
	}
}
