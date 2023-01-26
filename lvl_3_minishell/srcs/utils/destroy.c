/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:09:59 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/26 18:08:29 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy(t_data *data)
{
	rl_clear_history();
	free_matrix(data->paths);
	v_lstclear(&data->envp_lst);
}
