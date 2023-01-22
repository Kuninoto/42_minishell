/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2023/01/22 15:22:07 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

#define NOT_FOUND NULL

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

void	cmd_binaries(t_statement *statement, t_data *data)
{
	char	*binary_path;

	binary_path = statement->argv[0];
	if (is_absolute_path(statement))
	{
		if (execve(binary_path, statement->argv, data->envp) == -1)
		{
			perror(statement->argv[0]);
			g_exit_status = 127;
			exit(127);
		}
		g_exit_status = EXIT_SUCCESS;
	}
	else
	{
		binary_path = get_bin_path(statement->argv[0], data->paths);
		if (binary_path == NOT_FOUND)
		{
			cmd_not_found(statement->argv[0]);
			g_exit_status = 127;
			exit(127);
		}
		if (execve(binary_path, statement->argv, data->envp) == -1)
		{
			perror(statement->argv[0]);
			free(binary_path);
			g_exit_status = 127;
			exit(127);
		}
		g_exit_status = EXIT_SUCCESS;
		free(binary_path);
	}
}
