/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:06:14 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/23 00:22:30 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 0 as length parameter lets getcwd() copy the entire 
/ absolute path without length restrictions */
void	cmd_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (path == NULL)
	{
		perror("minishell:");
		return ;
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
}
