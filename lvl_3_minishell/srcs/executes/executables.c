/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:02:09 by roramos           #+#    #+#             */
/*   Updated: 2022/12/29 17:38:47 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_executables(t_statement *node, char **envp, t_vector *envp_vec)
{
	if (cmd_check(node, envp, envp_vec))
		return ;
	cmd_binaries(node, envp);
	exit(EXIT_SUCCESS);
}
