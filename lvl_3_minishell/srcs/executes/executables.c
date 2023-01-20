/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:02:09 by roramos           #+#    #+#             */
/*   Updated: 2023/01/20 15:14:24 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_executables(t_statement *node, t_data *data)
{
	if (builtin_with_fork(node, data))
		return ;
	cmd_binaries(node, data);
	exit(EXIT_SUCCESS);
}
