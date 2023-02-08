/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:17:34 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/08 14:35:59 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

#define NON_NUMERIC_EXIT_ARG "minishell: exit: numeric argument required" 

void	cmd_exit(int exit_status, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (data)
		destroy(data);
	g_exit_status = exit_status;
	if (exit_status == EXIT_FAILURE)
		ft_putendl_fd(TOO_MANY_ARGS, STDERR_FILENO);
	else if (exit_status == 2)
		ft_putendl_fd(NON_NUMERIC_EXIT_ARG, STDERR_FILENO);
	exit(exit_status);
}
