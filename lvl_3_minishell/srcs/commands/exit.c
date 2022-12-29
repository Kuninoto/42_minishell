/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <roramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:17:34 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 17:49:55 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_exit(bool newline, t_vector *var_vec, t_vector *envp_vec)
{
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	rl_clear_history();
	free_vec(var_vec);
	free_vec(envp_vec);
	exit(EXIT_SUCCESS);
}
