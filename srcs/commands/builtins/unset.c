/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:29:09 by roramos           #+#    #+#             */
/*   Updated: 2023/02/20 16:14:53 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	invalid_identifer(char *var_name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(var_name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}

int	unset_var(char *var_name, t_vlst **head)
{
	t_vlst	*temp;
	t_vlst	*next_node;

	temp = *head;
	if (ft_strchr(var_name, '='))
	{
		invalid_identifer(var_name);
		return (EXIT_FAILURE);
	}
	while (temp && temp->next != NULL)
	{
		if (streq(var_name, temp->next->var_name))
		{
			next_node = temp->next->next;
			free(temp->next->var_name);
			free(temp->next->var_value);
			free(temp->next);
			temp->next = next_node;
			break ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	cmd_unset(t_statement *s, t_vlst **head)
{
	int	i;

	i = 1;
	while (i < s->argc)
	{
		unset_var(s->argv[i], head);
		i += 1;
	}
	return (EXIT_SUCCESS);
}
