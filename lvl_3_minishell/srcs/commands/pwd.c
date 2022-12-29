/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:06:14 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 17:49:19 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 0 as length parameter lets getcwd() copy the entire 
/ absolute path without length restrictions */
void	cmd_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (path == NULL)
	{
		perror("Failed to execute getcwd()");
		return ;
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(path);
}
