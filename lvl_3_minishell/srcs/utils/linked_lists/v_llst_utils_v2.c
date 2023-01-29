/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_llst_utils_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:12:42 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/29 19:05:40 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vlst	*v_lstlast(t_vlst *node)
{
	while (node)
	{
		if (!node->next)
			break ;
		node = node->next;
	}
	return (node);
}

char	*get_fromvlst(char *var_name, t_vlst **head)
{
	t_vlst	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
			return (temp->var_value);
		temp = temp->next;
	}
	return (NULL);
}

t_vlst	*v_new_node(char *var_name, char *var_value, bool is_exported)
{
	t_vlst	*new_node;

	new_node = malloc(sizeof(t_vlst));
	new_node->var_name = var_name;
	new_node->var_value = var_value;
	new_node->is_exported = is_exported;
	new_node->next = NULL;
	return (new_node);
}

void	v_lstadd_back(t_vlst **head, t_vlst *new)
{
	t_vlst	*temp;

	if (head)
	{
		if (!*head)
			*head = new;
		else
		{
			temp = v_lstlast(*(head));
			temp->next = new;
		}
	}
}
