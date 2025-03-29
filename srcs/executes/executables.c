/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:02:09 by roramos           #+#    #+#             */
/*   Updated: 2023/02/19 22:53:33 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

void	exec_executables(t_statement *node, t_data *data)
{
	if (builtin(node, data))
		return ;
	cmd_binaries(node, data);
}
