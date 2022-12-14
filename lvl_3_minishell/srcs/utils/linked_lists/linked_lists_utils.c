/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:23:01 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/14 18:25:10 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	lstclear(t_statement **head)
{
	t_statement	*temp;
	t_statement	*next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free(temp->cmd);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

int	lstsize(t_statement *lst)
{
	t_statement	*temp;
	size_t	size;

	temp = lst;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

t_statement *new_node(size_t nr_statements)
{
	t_statement *new_node;

	new_node = malloc(sizeof(t_statement));
	new_node->cmd = NULL;
	new_node->args = malloc((nr_statements + 1) * sizeof(char *));
	new_node->operator = NONE;
	new_node->next = NULL;
	return (new_node);
}