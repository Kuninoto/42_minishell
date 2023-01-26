/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:03:10 by roramos           #+#    #+#             */
/*   Updated: 2023/01/26 19:04:14 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(char *var_name, t_data *data)
{
	t_vlst *temp;

	if (is_onstr(var_name, '='))
	{
		save_user_vars(var_name, &data->envp_lst, true);
		return ;
	}
	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
		{
			temp->is_exported = true;
			return ;
		}
		temp = temp->next;
	}
}
