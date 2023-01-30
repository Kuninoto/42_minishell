/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:00:47 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/30 22:20:36 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* writes minishell: <cmd> : error_msg to STDERR */
/* If error_msh is null calls perror() to get an error message */
void	put_error(char *cmd, char *error_msg)
{
	ft_putstr_fd("minishell:", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	else
		perror(NULL);
}
