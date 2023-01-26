/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:17:34 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/26 17:04:07 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

#define NON_NUMERIC_EXIT_ARG "minishell: exit: numeric argument required" 

void	cmd_exit(t_statement **head, int exit_status, t_data *data)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	p_lstclear(head);
	destroy(data);
	g_exit_status = exit_status;
	if (exit_status == 2)
		ft_putendl_fd(NON_NUMERIC_EXIT_ARG, STDERR_FILENO);
	exit(exit_status);
}
