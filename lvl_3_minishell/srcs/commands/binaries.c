/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2023/01/27 14:29:11 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

#define NOT_FOUND NULL

static char	**get_paths(t_vlst *envp_lst)
{
	t_vlst	*temp;

	temp = envp_lst;
	while (!streq("PATH", temp->var_name))
	{
		temp = temp->next;
		if (temp == NULL)
			return (NULL);
	}
	return (ft_split(temp->var_value, ':'));
}

static char	*get_bin_path(char *cmd, char **paths)
{
	size_t	i;
	char	*tmp;
	char	*bin_path;

	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		bin_path = join_free(tmp, cmd);
		if (access(bin_path, F_OK) == 0)
			return (bin_path);
		free(bin_path);
		i += 1;
	}
	printf("aqui!\n");
	return (NULL);
}

void	cmd_binaries(t_statement *statement, t_data *data)
{
	char	*binary_path;
	char	**paths;

	binary_path = statement->argv[0];
	paths = get_paths(data->envp_lst);
	if (is_absolute_path(statement))
	{
		if (execve(binary_path, statement->argv, data->envp) == -1)
		{
			perror(statement->argv[0]);
			free_matrix(paths);
			g_exit_status = 127;
			exit(127);
		}
		g_exit_status = EXIT_SUCCESS;
	}
	else
	{
		binary_path = get_bin_path(statement->argv[0], paths);
		if (binary_path == NOT_FOUND)
		{
			cmd_not_found(statement->argv[0]);
			free_matrix(paths);
			g_exit_status = 127;
			exit(127);
		}
		if (execve(binary_path, statement->argv, data->envp) == -1)
		{
			perror(statement->argv[0]);
			free(binary_path);
			free_matrix(paths);
			g_exit_status = 127;
			exit(127);
		}
		g_exit_status = EXIT_SUCCESS;
		free(binary_path);
	}
}
