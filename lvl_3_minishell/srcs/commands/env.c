/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:29:50 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/19 15:29:16 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
	i = -1;
	while (data->envp_vec.storage[++i])
		printf("%s\n", data->envp_vec.storage[i]);
}
