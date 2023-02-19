/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:00:09 by roramos           #+#    #+#             */
/*   Updated: 2023/02/19 22:53:27 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

void	exec_cmd(t_statement *current_node, t_data *data)
{
	signal(SIGINT, child_signals);
	if (current_node->operator == PIPE)
		exec_pipe(current_node, data);
	else if (current_node->operator == NONE)
		exec_executables(current_node, data);
	else
		exec_redirects(current_node, data);
	exit(g_exit_status);
}

void	exec_type(t_statement *statement_list, t_data *data)
{
	int		temp_status;

	if (p_lstsize(statement_list) == 1)
	{
		if (!builtin(statement_list, data) && fork() == 0)
		{
			signal(SIGINT, child_signals);
			exec_executables(statement_list, data);
		}
	}
	else if (fork() == 0)
		exec_cmd(statement_list, data);
	waitpid(-1, &temp_status, 0);
	if (!WTERMSIG(temp_status))
		g_exit_status = temp_status >> 8;
}

/* 127, i.e command not found, comes from waitpid as 32512. 32512 >> 8 = 127 */
