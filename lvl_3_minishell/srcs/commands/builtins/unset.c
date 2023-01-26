/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:29:09 by roramos           #+#    #+#             */
/*   Updated: 2023/01/26 19:09:16 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_unset(char *var_name, t_vlst **head)
{
	t_vlst	*temp;
	t_vlst	*next_node;

	temp = *head;
	while (temp && temp->next != NULL)
	{
		if (streq(var_name, temp->next->var_name))
		{
			next_node = temp->next->next;
			free(temp->next->var_name);
			free(temp->next->var_value);
			free(temp->next);
			temp->next = next_node;
		}
		temp = temp->next;
	}
}
