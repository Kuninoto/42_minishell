/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:00:09 by roramos           #+#    #+#             */
/*   Updated: 2023/02/11 16:13:39 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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
	pid_t	child_pid;
	int		temp_status;

	if (streq(statement_list->argv[0], "exit"))
	{
		call_cmd_exit(statement_list, data);
		return ;
	}
	child_pid = fork();
	if (child_pid == -1)
		panic(data, FORK_ERR, EXIT_FAILURE);
	if (child_pid == 0)
		exec_cmd(statement_list, data);
	else
	{
		waitpid(child_pid, &temp_status, 0);
		g_exit_status = temp_status >> 8;
	}
}

/* 127, i.e command not found, comes from waitpid as 32512. 32512 >> 8 = 127 */
