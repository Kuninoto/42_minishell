/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:17:34 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/06 20:17:38 by nnuno-ca         ###   ########.fr       */
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
