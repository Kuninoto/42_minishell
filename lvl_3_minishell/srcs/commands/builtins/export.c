/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:03:10 by roramos           #+#    #+#             */
/*   Updated: 2023/02/10 02:06:30 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(char *var_name, t_data *data)
{
	t_vlst	*temp;

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
