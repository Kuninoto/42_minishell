/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:09:59 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/23 01:11:09 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy(t_data *data)
{
	rl_clear_history();
	free_matrix(data->paths);
	free_vec(&data->var_vec);
	free_vec(&data->envp_vec);
}
