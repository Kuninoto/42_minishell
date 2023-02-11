/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:20:58 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/11 03:06:03 by nnuno-ca         ###   ########.fr       */
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
