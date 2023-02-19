/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:03:10 by roramos           #+#    #+#             */
/*   Updated: 2023/02/19 22:27:21 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_onid(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == c)
			return (true);
		i += 1;
	}
	return (false);
}

static int	single_export(t_data *data)
{
	t_vlst	*temp;

	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (temp->is_exported)
			printf("declare -x %s=\"%s\"\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

static int	export_bad_identifier(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static void	loop_and_export(char *var_name, t_data *data)
{
	t_vlst	*temp;

	temp = data->envp_lst;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
		{
			temp->is_exported = true;
			break ;
		}
		temp = temp->next;
	}
}

int	cmd_export(t_statement *statement, t_data *data)
{
	int		exit_status;
	size_t	i;

	if (statement->argc == 1)
		return (single_export(data));
	exit_status = EXIT_SUCCESS;
	i = 0;
	while (statement->argv[++i])
	{	
		if (!is_valid_id(statement->argv[i]))
			exit_status = export_bad_identifier(statement->argv[i]);
		else if (is_onstr(statement->argv[i], '='))
		{
			save_user_vars(statement->argv[i], &data->envp_lst, true);
			continue ;
		}
		else
			loop_and_export(statement->argv[i], data);
	}
	return (exit_status);
}
