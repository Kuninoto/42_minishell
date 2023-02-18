/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:03:10 by roramos           #+#    #+#             */
/*   Updated: 2023/02/18 16:28:48 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_export(t_data *data)
{
	t_vlst	*temp;

	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (temp->is_exported)
			printf("declare -x %s=\"%s\"\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	cmd_export(t_statement *statement, t_data *data)
{
	t_vlst	*temp;
	size_t	i;

	if (statement->argc == 1)
		return (single_export(data));
	i = 0;
	while (statement->argv[++i])
	{	
		if (is_onstr(statement->argv[i], '='))
		{
			save_user_vars(statement->argv[i], &data->envp_lst, true);
			continue ;
		}
		temp = data->envp_lst;
		while (temp != NULL)
		{
			if (streq(statement->argv[i], temp->var_name))
			{
				temp->is_exported = true;
				break ;
			}
			temp = temp->next;
		}
	}
	return (EXIT_SUCCESS);
}
