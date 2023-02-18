/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roramos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:24:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/02/18 15:44:26 by roramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	call_cmd_exit(t_statement *statement, t_data *data)
{
	if (statement->argc == 2)
	{
		if (is_all_digits(statement->argv[1]))
			cmd_exit(ft_atoi(statement->argv[1]), data);
		else
			cmd_exit(2, data);
	}
	else if (statement->argc > 2)
		cmd_exit(EXIT_FAILURE, data);
	else
		cmd_exit(EXIT_SUCCESS, data);
}

bool	builtin(t_statement *statement, t_data *data)
{
	if (streq(statement->argv[0], "exit"))
		call_cmd_exit(statement, data);
	else if (streq(statement->argv[0], "unset"))
		g_exit_status = cmd_unset(statement->argv[1], &data->envp_lst);
	else if (streq(statement->argv[0], "export"))
		g_exit_status = cmd_export(statement, data);
	else if (streq(statement->argv[0], "cd"))
	{
		if (statement->argc > 2)
			g_exit_status = cd_too_many_args();
		else
			g_exit_status = cmd_cd(statement->argv[1]);
	}
	else if (ft_strchr(statement->argv[0], '='))
		g_exit_status = save_user_vars(statement->argv[0],
				&data->envp_lst, false);
	else if (streq(statement->argv[0], "echo"))
		g_exit_status = cmd_echo(statement);
	else if (streq(statement->argv[0], "pwd"))
		g_exit_status = cmd_pwd();
	else if (streq(statement->argv[0], "env"))
		g_exit_status = cmd_env(data);
	else
		return (false);
	return (true);
}
