/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:03:10 by roramos           #+#    #+#             */
/*   Updated: 2023/01/30 22:09:55 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	only_export(t_data *data)
{
	t_vlst	*temp;

	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (temp->is_exported)
			printf("declare -x %s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
}

void	cmd_export(char *var_name, t_data *data)
{
	t_vlst	*temp;

	if (is_onstr(var_name, '='))
	{
		save_user_vars(var_name, &data->envp_lst, true);
		return ;
	}
	if (is_digit(var_name[0]))
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(var_name, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
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
