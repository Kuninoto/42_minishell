/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:00:09 by roramos           #+#    #+#             */
/*   Updated: 2023/01/22 13:58:40 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

//	bytes written on pipedes[1] can be read on pipedes[0]
void	exec_cmd(t_statement *current_node, t_data *data)
{
	if (current_node->operator == PIPE)
		exec_pipe(current_node, data);
	else if (current_node->operator == NONE)
		exec_executables(current_node, data);
	else
		exec_redirects(current_node, data);
	g_exit_status = EXIT_SUCCESS;
	exit(EXIT_SUCCESS);
}

void	exec_type(t_statement *statement_list, t_data *data)
{
//  Add error handling for a fork() fail i.e pid = -1
//	pid_t	child_pid;

	if (lstsize(statement_list) == 1)
	{
		if (!builtin_without_fork(statement_list, data)
			&& fork() == 0)
		{
			exec_cmd(statement_list, data);
			g_exit_status = EXIT_SUCCESS;
			exit(EXIT_SUCCESS);
		}
	}
	else if (fork() == 0)
		exec_cmd(statement_list, data);
}
