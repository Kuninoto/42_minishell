/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:00:09 by roramos           #+#    #+#             */
/*   Updated: 2022/12/29 17:38:33 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	bytes written on pipedes[1] can be read on pipedes[0]
void	exec_cmd(t_statement *current_node, char **envp, t_vector *envp_vec)
{
	if (current_node->operator == PIPE)
		exec_pipe(current_node, envp, envp_vec);
	else if (current_node->operator == NONE)
		exec_executables(current_node, envp, envp_vec);
	else
		exec_redirects(current_node, envp, envp_vec);
	exit(EXIT_SUCCESS);
}

void	exec_type(t_statement *statement_list, char **envp,
t_vector *envp_vec, t_vector *var_vec)
{
	if (lstsize(statement_list) == 1)
	{
		if (!cmd_check_singles(statement_list, envp_vec, var_vec)
			&& fork() == 0)
		{
			exec_cmd(statement_list, envp, envp_vec);
			exit(EXIT_SUCCESS);
		}
	}
	else if (fork() == 0)
		exec_cmd(statement_list, envp, envp_vec);
}
