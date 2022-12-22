/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:00:09 by roramos           #+#    #+#             */
/*   Updated: 2022/12/22 18:56:24 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_statement *current_node, char **envp, t_vector *envp_vec)
{
	//	bytes written on pipedes[1] can be read on pipedes[0]
	if (current_node->operator == PIPE)
		exec_pipe(current_node, envp, envp_vec);
	else if (current_node->operator == NONE)
		exec_executables(current_node, envp, envp_vec);
	else
		exec_redirects(current_node, envp, envp_vec);
	exit(EXIT_SUCCESS);
}