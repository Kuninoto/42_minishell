/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:50 by roramos           #+#    #+#             */
/*   Updated: 2023/02/20 00:50:56 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

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

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		bin_path = join_free(tmp, cmd);
		if (access(bin_path, F_OK | X_OK) == 0)
			return (bin_path);
		free(bin_path);
		i += 1;
	}
	return (NULL);
}

static void	exit_and_free_matrix(char **paths, char *cmd, int exit_status)
{
	if (cmd)
		perror(cmd);
	free_matrix(paths);
	if (!WIFSIGNALED(g_exit_status))
		g_exit_status = exit_status;
	exit(g_exit_status);
}

/* static void save_current_bin_on_env(char *bin_path, t_vlst **head)
{
	char	*temp;

	temp = ft_strjoin("_=", bin_path);
	save_user_vars(temp, head, true);
} */

void	cmd_binaries(t_statement *statement, t_data *data)
{
	char	*bin_path;
	char	**paths;

	bin_path = statement->argv[0];
	paths = get_paths(data->envp_lst);
	if (is_absolute_path(statement))
	{
	//	save_current_bin_on_env(bin_path, &data->envp_lst);
		if (execve(bin_path, statement->argv, data->envp) == -1)
			exit_and_free_matrix(paths, statement->argv[0], 127);
		exit_and_free_matrix(paths, NULL, EXIT_SUCCESS);
		return ;
	}
	bin_path = get_bin_path(statement->argv[0], paths);
	if (bin_path == NOT_FOUND)
	{
		cmd_not_found(statement->argv[0]);
		exit_and_free_matrix(paths, NULL, 127);
	}
//	save_current_bin_on_env(bin_path, &data->envp_lst);
	if (execve(bin_path, statement->argv, data->envp) == -1)
	{
		free(bin_path);
		exit_and_free_matrix(paths, statement->argv[0], 127);
	}
	free(bin_path);
	exit_and_free_matrix(paths, NULL, EXIT_SUCCESS);
}
