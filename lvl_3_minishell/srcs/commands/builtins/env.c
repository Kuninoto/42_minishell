/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:29:50 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/26 18:21:35 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(t_data *data)
{
	t_vlst	*temp;

	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (temp->is_exported)
			printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
}
