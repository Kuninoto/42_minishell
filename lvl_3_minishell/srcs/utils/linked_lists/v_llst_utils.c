/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_llst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:21:50 by roramos           #+#    #+#             */
/*   Updated: 2023/02/08 14:47:49 by roramos          ###   ########.fr       */
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

char	**split_envp(char *env)
{
	char	**splitted;
	size_t	indexof_equal;

	splitted = malloc(2 * sizeof(char *));
	indexof_equal = ft_strchr(env, '=') - env;
	splitted[0] = ft_substr(env, 0, indexof_equal);
	splitted[1] = ft_substr(env, indexof_equal + 1,
			ft_strlen(&env[indexof_equal]));
	return (splitted);
}

t_vlst	*init_envp_lst(char **envp)
{
	t_vlst	*head;
	t_vlst	*temp;
	char	**line;
	size_t	i;

	line = split_envp(envp[0]);
	head = v_new_node(line[0], line[1], true);
	free(line);
	i = 1;
	temp = head;
	while (envp[i])
	{
		line = split_envp(envp[i]);
		temp->next = v_new_node(line[0], line[1], true);
		free(line);
		temp = temp->next;
		i += 1;
	}
	return (head);
}

void	save_user_vars(char *statement, t_vlst **head, bool is_exported)
{
	char	**line;

	line = split_envp(statement);
	if (!*line[0] || !*line[1])
	{
		free(line);
		return ;
	}
	cmd_unset(line[0], head);
	v_lstadd_back(head, v_new_node(line[0], line[1], is_exported));
	free(line);
}
