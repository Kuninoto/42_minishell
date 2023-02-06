/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:29:09 by roramos           #+#    #+#             */
/*   Updated: 2023/01/30 22:14:31 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_unset(char *var_name, t_vlst **head)
{
	t_vlst	*temp;
	t_vlst	*next_node;

	temp = *head;
	if (is_digit(var_name[0]) || ft_strchr(var_name, '='))
	{
		ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(var_name, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return ;
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
		}
		temp = temp->next;
	}
}
