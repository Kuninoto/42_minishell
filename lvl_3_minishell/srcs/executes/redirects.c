/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:04:22 by roramos           #+#    #+#             */
/*   Updated: 2023/01/30 22:20:11 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_input_until(t_statement *node)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (streq(buff, node->next->argv[0]))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

static void	redirect_input(t_statement *node)
{
	int		in_file;

	if (node->next->argv[0])
	{
		if (access(node->next->argv[0], F_OK) == SUCCESS)
		{
			in_file = open(node->next->argv[0], O_RDONLY);
			dup2(in_file, STDIN_FILENO);
		}
		else
		{
			put_error(node->next->argv[0], NULL);
			exit(EXIT_FAILURE);
		}
	}
}

static void	redirect_output(t_statement *node)
{
	close(STDOUT_FILENO);
	if (node->operator == RDR_OUT_REPLACE)
		open(node->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (node->operator == RDR_OUT_APPEND)
		open(node->next->argv[0], O_WRONLY | O_APPEND, 0666);
}

void	exec_redirects(t_statement *node, t_data *data)
{
	if (node->operator == RDR_INPUT)
		redirect_input(node);
	else if (node->operator == RDR_INPUT_UNTIL)
		redirect_input_until(node);
	else
		redirect_output(node);
	node->operator = NONE;
	exec_cmd(node, data);
}
