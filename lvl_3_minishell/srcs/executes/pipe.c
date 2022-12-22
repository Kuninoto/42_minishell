/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:58:39 by roramos           #+#    #+#             */
/*   Updated: 2022/12/22 19:33:08 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_pipe(t_statement *node, char **envp, t_vector *envp_vec)
{
	pid_t mshell_pid;
	int	pipedes[2];
	int	status;

	node->operator = NONE;
	if (pipe(pipedes) == -1)
		panic("Failed to pipe");
	// left side
	mshell_pid = fork();
	if (mshell_pid == 0)
	{
		close(STDOUT_FILENO); // fd 1
		dup(pipedes[1]);	// fd output
		close(pipedes[0]);
		close(pipedes[1]);
		exec_cmd(node, envp, envp_vec);
	}
	mshell_pid = fork();
	// right side
	if (mshell_pid == 0)
	{
		close(STDIN_FILENO); // fd 0
		dup(pipedes[0]);	// input
		close(pipedes[0]);
		close(pipedes[1]);
		exec_cmd(node->next, envp, envp_vec);
	}
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(mshell_pid, &status, 0);
	waitpid(mshell_pid, &status, 0);
}