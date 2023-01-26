/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:24:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/26 19:03:35 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_without_fork(t_statement *statement, t_data *data)
{
	if (streq(statement->argv[0], "exit"))
	{
		if (statement->argc > 1)
		{
			if (is_all_digits(statement->argv[1]))
				cmd_exit(&statement, ft_atoi(statement->argv[1]), data);
			else
				cmd_exit(&statement, 2, data);
		}
		else
			cmd_exit(&statement, EXIT_SUCCESS, data);
	}
	else if (streq(statement->argv[0], "unset"))
		cmd_unset(statement->argv[1], &data->envp_lst);
	else if (streq(statement->argv[0], "export"))
		cmd_export(statement->argv[1], data);
	else if (streq(statement->argv[0], "cd"))
	{
		if (statement->argc > 2)
			ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		else
			cmd_cd(statement->argv[1]);
	}
	else if (ft_strchr(statement->argv[0], '='))
		save_user_vars(statement->argv[0], &data->envp_lst, false);
	else if (streq(statement->argv[0], "echo"))
		cmd_echo(statement);
	else if (streq(statement->argv[0], "pwd"))
		cmd_pwd();
	else if (streq(statement->argv[0], "env"))
		cmd_env(data);
	else
		return (false);
	return (true);
}

