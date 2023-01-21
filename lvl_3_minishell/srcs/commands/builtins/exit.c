/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:17:34 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/20 22:10:28 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_status;

void	cmd_exit(t_statement **head, int exit_status, t_data *data)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	lstclear(head);
	destroy(data);
	g_exit_status = exit_status;
	if (exit_status == 2)
		ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR_FILENO);
	exit(exit_status);
}
