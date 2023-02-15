/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:20:58 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/15 21:57:48 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(char *path)
{
	char	*error_msg;

	if (path == NULL || streq(path, "~"))
		return (chdir(getenv("HOME")));
	if (chdir(path) == SUCCESS)
		return (EXIT_SUCCESS);
	error_msg = ft_strjoin("minishell: cd: ", path);
	perror(error_msg);
	free(error_msg);
	return (EXIT_FAILURE);
}

/* 	if (streq(path, "-"))
	{
		oldpwd = get_fromvlst("OLDPWD", &data->envp_lst);
		if (!oldpwd)
		{	
			ft_putendl_fd(OLDPWD_NOT_SET, STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		return (chdir(oldpwd));
	}
	if (chdir(path) == SUCCESS)
	{
		oldpwd = ft_strjoin("OLDPWD=", path);
		save_user_vars(oldpwd, &data->envp_lst, true);
		free(oldpwd);
		return (EXIT_SUCCESS);
	} */
