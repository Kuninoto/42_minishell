/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:04:22 by roramos           #+#    #+#             */
/*   Updated: 2023/01/22 14:31:39 by nnuno-ca         ###   ########.fr       */
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

static void	redirect_output(t_statement *node)
{
	close(STDOUT_FILENO);
	if (node->operator == RDR_OUT_REPLACE)
		open(node->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (node->operator == RDR_OUT_APPEND)
		open(node->next->argv[0], O_WRONLY | O_APPEND, 0666);
}

/* static void realloc_argv(t_statement *node)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(get_nr_statements(node->argv) + 2 * sizeof(char *));
	while (node->argv[i])
	{
		new_argv[i] = node->argv[i];
		i += 1;
	}
	new_argv[i] = get_input_from_file(node->next->argv[0]);
	new_argv[i] = NULL;
	free(node->argv);
	node->argv = new_argv;
} */

void	exec_redirects(t_statement *node, t_data *data)
{
	int		in_file;
	char	*error_msg;

	if (node->operator == RDR_INPUT)
	{
		if (node->next->argv[0])
		{
			if (access(node->next->argv[0], F_OK) == SUCCESS)
			{
				in_file = open(node->next->argv[0], O_RDONLY);
				dup2(in_file, STDIN_FILENO);
			}
			else
			{
				error_msg = ft_strjoin("minishell: ", node->next->argv[0]);
				perror(error_msg);
				free(error_msg);
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (node->operator == RDR_INPUT_UNTIL)
		redirect_input_until(node);
	else
		redirect_output(node);
	node->operator = NONE;
	exec_cmd(node, data);
}
