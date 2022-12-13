/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:23:01 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/13 18:28:47 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_statement	*lstlast(t_statement *head)
{
	if (head)
	{
		while (head->next != NULL)
			head = head->next;
		return (head);
	}
	return (NULL);
}

void	lstadd_back(t_statement **head, t_statement *new_node)
{
	t_statement	*tail;

	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tail = lstlast(*head);
	tail->next = new_node;
}

t_statement *new_node(size_t nr_statements)
{
	t_statement *new_node;

	new_node = malloc(sizeof(t_statement));
	new_node->command = NULL;
	new_node->arguments = malloc(nr_statements * sizeof(char *));
	new_node->operator = o_none;
	new_node->next = NULL;
	return (new_node);
}