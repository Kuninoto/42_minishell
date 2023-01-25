/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:58:39 by roramos           #+#    #+#             */
/*   Updated: 2023/01/25 19:11:55 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	left_side(t_statement *nd, t_data *data, int pdes[2])
{
	close(STDOUT_FILENO);
	dup(pdes[1]);
	close(pdes[0]);
	close(pdes[1]);
	exec_cmd(nd, data);
}

static void	right_side(t_statement *nd, t_data *data, int pdes[2])
{
	close(STDIN_FILENO);
	dup(pdes[0]);
	close(pdes[0]);
	close(pdes[1]);
	exec_cmd(nd->next, data);
}

void	exec_pipe(t_statement *node, t_data *data)
{
	pid_t	child_pid;
	int		pipedes[2];
	int		status;

	node->operator = NONE;
	if (pipe(pipedes) == -1)
		panic(PIPE_ERR);
	child_pid = fork();
	if (child_pid == 0)
		left_side(node, data, pipedes);
	child_pid = fork();
	if (child_pid == 0)
		right_side(node, data, pipedes);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(child_pid, &status, 0);
	waitpid(child_pid, &status, 0);
}
