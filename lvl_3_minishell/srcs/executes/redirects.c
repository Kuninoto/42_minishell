/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:04:22 by roramos           #+#    #+#             */
/*   Updated: 2022/12/22 15:22:22 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_input_until(t_statement *node)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (streq(buff, node->next->argv[0]))
			break;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	free (buff);	
}

static void	redirect_output(t_statement *node)
{
	close(STDOUT_FILENO); // 1
	if (node->operator == RDR_OUT_APPEND)
		open(node->next->argv[0], O_WRONLY|O_APPEND, 0777);
	else if (node->operator == RDR_OUT_REPLACE)
		open(node->next->argv[0], O_WRONLY|O_TRUNC|O_CREAT, 0777);	
}

void	exec_redirects(t_statement *node, char **envp, t_vector *envp_vec)
{
	if (node->operator == RDR_INPUT)
	{
		close(STDIN_FILENO); // 0
		open(node->next->argv[0], O_RDONLY);
	}
	else if (node->operator == RDR_INPUT_UNTIL)
		redirect_input_until(node);
	else
		redirect_output(node);
	node->operator = NONE;
	exec_cmd(node, envp, envp_vec);
}