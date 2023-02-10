/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:00:09 by roramos           #+#    #+#             */
/*   Updated: 2023/02/10 05:24:15 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/* void	print_operator(t_operator operator)
{
	const char *operators[6] = {"NONE", ">", ">>", "<", "<<", "|"};
	printf("OPERATOR = %s", operators[operator]);
}
 */

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
	if (p_lstsize(statement_list) == 1)
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
