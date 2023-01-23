/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:23:01 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/22 21:17:31 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	//	printf("tupai\n");
		free_matrix(temp->argv);
	//	printf("tumae2\n");
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

size_t	lstsize(t_statement *head)
{
	t_statement	*temp;
	size_t		size;

	temp = head;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

t_statement	*new_node(int argc)
{
	t_statement	*new_node;

	new_node = malloc(sizeof(t_statement));
	new_node->argc = argc;
	new_node->argv = malloc((argc + 1) * sizeof(char *));
	new_node->operator = NONE;
	new_node->next = NULL;
	return (new_node);
}
