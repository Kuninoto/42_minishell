/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:20:58 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/22 14:26:28 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_cd(char *path)
{
	char	*error_msg;

	if (path == NULL || streq(path, "~"))
	{
		chdir(getenv("HOME"));
		return ;
	}
	if (chdir(path) == SUCCESS)
		return ;
	error_msg = ft_strjoin("minishell: cd: ", path);
	perror(error_msg);
	free(error_msg);
}
