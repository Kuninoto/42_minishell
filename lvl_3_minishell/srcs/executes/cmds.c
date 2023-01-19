/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:00:09 by roramos           #+#    #+#             */
/*   Updated: 2023/01/19 23:06:03 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_exit_status;

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
	if (lstsize(statement_list) == 1)
	{
		if (streq("exit", statement_list->argv[1]))
		{
			printf("tumae = %s\n", statement_list->argv[1]);
			if (is_all_digits(statement_list->argv[1]))
				cmd_exit(&statement_list, ft_atoi(statement_list->argv[1]), data);
			else
				cmd_exit(&statement_list, 2, data);
		}
		else if (!cmd_check_singles(statement_list, data)
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
