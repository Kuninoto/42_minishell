/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:17:34 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/30 22:35:42 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

#define NON_NUMERIC_EXIT_ARG "minishell: exit: numeric argument required" 

void	cmd_exit(t_statement *head, int exit_status, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (head)
		p_lstclear(head);
	if (data)
		destroy(data);
	g_exit_status = exit_status;
	if (exit_status == EXIT_FAILURE)
		ft_putendl_fd(TOO_MANY_ARGS, STDERR_FILENO);
	else if (exit_status == 2)
		ft_putendl_fd(NON_NUMERIC_EXIT_ARG, STDERR_FILENO);
	exit(exit_status);
}
