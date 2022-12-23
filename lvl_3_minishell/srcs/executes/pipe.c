/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:58:39 by roramos           #+#    #+#             */
/*   Updated: 2022/12/23 16:03:51 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	left_side(t_statement *node, char **envp, t_vector *envp_vec, int pipedes[2])
{
	close(STDOUT_FILENO);
	dup(pipedes[1]);
	close(pipedes[0]);
	close(pipedes[1]);
	exec_cmd(node, envp, envp_vec);
}

static void	right_side(t_statement *node, char **envp, t_vector *envp_vec, int pipedes[2])
{
	close(STDIN_FILENO);
	dup(pipedes[0]);
	close(pipedes[0]);
	close(pipedes[1]);
	exec_cmd(node->next, envp, envp_vec);
}

void	exec_pipe(t_statement *node, char **envp, t_vector *envp_vec)
{
	pid_t pid;
	int	pipedes[2];
	int	status;

	node->operator = NONE;
	if (pipe(pipedes) == -1)
		panic("Failed to pipe");
	pid = fork();
	if (pid == 0)
		left_side(node, envp, envp_vec, pipedes);
	pid = fork();
	if (pid == 0)
		right_side(node, envp, envp_vec, pipedes);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(pid, &status, 0);
	waitpid(pid, &status, 0);
}