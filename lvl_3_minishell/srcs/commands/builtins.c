/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:24:53 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/22 03:04:02 by nnuno-ca         ###   ########.fr       */
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
	else if (streq(statement->argv[0], "unset")
		&& is_onvec(statement->argv[1], &data->envp_vec))
		vec_pop_at(statement->argv[1], &data->envp_vec);
	else if (streq(statement->argv[0], "export"))
		cmd_export(data, statement->argv[1]);
	else if (streq(statement->argv[0], "cd"))
		cmd_cd(statement->argv[1]);
	else if (ft_strchr(statement->argv[0], '='))
		save_user_vars(statement->argv[0], &data->var_vec);
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
