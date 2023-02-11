/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:17:34 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/11 03:38:57 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	cmd_exit(int exit_status, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (data)
		destroy(data);
	g_exit_status = exit_status;
	if (exit_status == EXIT_FAILURE)
		ft_putendl_fd(EXIT_TOO_MANY_ARGS, STDERR_FILENO);
	else if (exit_status == 2)
		ft_putendl_fd(EXIT_NON_NUMERIC_ARG, STDERR_FILENO);
	exit(exit_status);
}
