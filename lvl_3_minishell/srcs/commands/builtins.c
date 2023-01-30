/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:24:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/30 22:17:31 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	call_cmd_exit(t_statement *statement, t_data *data)
{
	if (statement->argc == 2)
	{
		if (is_all_digits(statement->argv[1]))
			cmd_exit(statement, ft_atoi(statement->argv[1]), data);
		else
			cmd_exit(statement, 2, data);
	}
	else if (statement->argc > 2)
		cmd_exit(statement, EXIT_FAILURE, data);
	else
		cmd_exit(statement, EXIT_SUCCESS, data);
}

bool	builtin_without_fork(t_statement *statement, t_data *data)
{
	if (streq(statement->argv[0], "exit"))
		call_cmd_exit(statement, data);
	else if (streq(statement->argv[0], "unset"))
		cmd_unset(statement->argv[1], &data->envp_lst);
	else if (streq(statement->argv[0], "export"))
	{
		if (statement->argc == 1)
			only_export(data);
		else
			cmd_export(statement->argv[1], data);
	}
	else if (streq(statement->argv[0], "cd"))
	{
		if (statement->argc > 2)
			put_error("cd", "too many arguments");
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
	g_exit_status = 0;
	return (true);
}
