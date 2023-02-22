/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_llst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:21:50 by roramos           #+#    #+#             */
/*   Updated: 2023/02/22 16:59:18 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	v_lstsize_exported(t_vlst **head)
{
	t_vlst	*temp;
	size_t	count;

	temp = *head;
	count = 0;
	while (temp != NULL)
	{
		if (temp->is_exported)
			count += 1;
		temp = temp->next;
	}
	return (count);
}

bool	get_exported_state(char *var_name, t_vlst **head)
{
	t_vlst	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
			return (temp->is_exported);
		temp = temp->next;
	}
	return (false);
}

char	**split_envp(char *env)
{
	char	**splitted;
	size_t	indexof_equal;

	splitted = malloc(3 * sizeof(char *));
	indexof_equal = ft_strchr(env, '=') - env;
	splitted[0] = ft_substr(env, 0, indexof_equal);
	splitted[1] = ft_substr(env, indexof_equal + 1,
			ft_strlen(&env[indexof_equal]));
	splitted[2] = NULL;
	return (splitted);
}

int	save_user_vars(char *statement, t_vlst **head, bool to_export)
{
	char	**line;

	line = split_envp(statement);
	if (get_exported_state(line[0], head) && !to_export)
		to_export = true;
	unset_var(line[0], head);
	v_lstadd_back(head, v_new_node(line[0], line[1], to_export));
	free(line);
	return (EXIT_SUCCESS);
}
