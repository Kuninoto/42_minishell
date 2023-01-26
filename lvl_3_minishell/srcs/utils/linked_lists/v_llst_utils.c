/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_llst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:21:50 by roramos           #+#    #+#             */
/*   Updated: 2023/01/26 19:06:38 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	v_lstclear(t_vlst **head)
{
	t_vlst	*temp;
	t_vlst	*next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free(temp->var_name);
		free(temp->var_value);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
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

t_vlst	*init_envp_lst(char **envp)
{
	t_vlst	*head;
	char	**line;
	size_t	i;
	t_vlst	*temp;

	line = ft_split(envp[0], '=');
head = v_new_node(line[0], line[1], true);
	free(line[2]);
	i = 1;
	temp = head;
	while (envp[i])
	{
		line = ft_split(envp[i], '=');
		temp->next = v_new_node(line[0], line[1], true);
		free(line[2]);
		temp = temp->next;
		i += 1;
	}
	return (head);
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

void	save_user_vars(char *statement, t_vlst **head, bool is_exported)
{
	char	**line;
	
	line = ft_split(statement, '=');
	cmd_unset(line[0], head);
	v_lstadd_back(head, v_new_node(line[0], line[1], is_exported));
	free(line[2]);
}